//
//  ViewController.m
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import "ViewController.h"
#import <UIKit/UIPanGestureRecognizer.h>
#import <UIKit/UITapGestureRecognizer.h>
#import <CoreGraphics/CGImage.h>

#import "Camera.h"
#import "LiveViewOptions.h"
#import "LiveViewOptionsViewController.h"
#import "ViewController+RenderMode.h"
#import "ViewController_RenderMode.h"
#import "ContentGenerator.h"
#import "RenderManager.h"
#import "Shader.h"
#import "ShaderProgram.h"
#import "ShaderProgram+External.h"
#import "OpenGLRenderer.h"
#import "OpenGLRenderUnit.h"

#include "Trackball.h"
#include "BasicTypesImpl.h"
#include "Box.h"
#include "ShaderRenderingModes.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Attribute index.
enum
{
    ATTRIB_VERTEX,
    ATTRIB_NORMAL,
    NUM_ATTRIBUTES
};

GLfloat trackBallVertexData[24] = {
    0.2,0.2,-0.5, 1,0,0,
    0.2,0.8,-0.5, 0,1,0,
    0.8,0.8,-0.5, 0,1,0,
    0.8,0.2,-0.5, 0,0,1,
};

static GLfloat DEFAULT_FOV_IN_DEGREES = 65.0f;
static GLfloat DEFAULT_NEAR_PLANE = 0.1;
static GLfloat DEFAULT_FAR_PLANE = 100;

using namespace Framework;

@interface ViewController () {
    RenderManager * m_renderManager;
    
    GLuint _program;
    
    // Model matrix, camera matrix, projection matrix
    GLKMatrix4 _modelViewProjectionMatrix;
    
    // Model matrix
    GLKMatrix4 _modelMatrix;
    
    // Transform normal vectors
    GLKMatrix3 _normalMatrix;
    
    float _rotation;
    
    //GLuint _vertexArray;
    //GLuint _vertexBuffer;
    
    //GLuint _indexArray;
    //GLuint _indexBuffer;
    
    GLuint _tbVertexArray;
    GLuint _tbVertexBuffer;
    
    GLuint m_textures[4];
    
    NSData *m_TextureData;
    
    GLKTextureInfo *m_TextureInfo;
    
    Math::Trackball m_trackBall;
    
    NSDate *m_camPinchLastTime;
    
    /**
     * Rectangle that can be drawn on screen to show where
     * the trackball boundary is.
     */
    CGPathRef m_trackBallRect;
    
    ShaderProgram * m_shaderProgram;
    
    Framework::Box * m_box;
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;
@property (strong, nonatomic) Camera *camera;


- (void)setupGL;
- (void)tearDownGL;
- (BOOL)loadShaders;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    if (!m_renderManager) {
        m_renderManager = [RenderManager instance];
    }
    
    if (!m_box) {
        m_box = new Box();
        m_box->createGeo();
        
        //OpenGLRenderUnit * ru = [[OpenGLRenderUnit alloc] initWithShader:Nil polygonMesh:m_box->getPolygonMesh()];
        //[[m_renderManager getOpenGLRenderer] addRenderUnit:ru];
    }
    
    if (!m_TextureData) {
        Color c0(1,0,0,1);
        Color c1(0,0,1,1);
        
        m_TextureData = [ContentGenerator genCheckerTexture:c0 color1:c1 width:32 height:32 widthTileSize:8 heightTileSize:8];
        
        //Color c2(1,0,1,1);
        //Color c3(0,1,1,1);
        //m_TextureData[1] = [ContentGenerator genCheckerTexture:c2 color1:c3 width:16 height:16 widthTileSize:2 heightTileSize:2];
    }
    
    /*
     * Use the global instance which is shared with LiveViewOptionsViewController
     */
    m_liveViewOptions = [LiveViewOptions instance];
    
    m_trackBall.setRadius(0.9);
    m_trackBall.reset();
    
    if (!m_liveViewOptions.trackBall.isZero()) {
        m_trackBall.init(m_liveViewOptions.trackBall);
    }
    
    if (m_liveViewOptions.camera) {
        self.camera = m_liveViewOptions.camera;
    } else {
        /*
         Camera (0,0,10) looking at 0,0,0
         Sphere at (0,0,0) radius 5.
         
         Light at (0,0,10)
         */
        PointF camPos(0,0,5);
        VectorF camDir(0,0,-1);
        Ray r(camPos, camDir);
        VectorF up(0,1,0);
        
        float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
        
        self.camera = [[Camera alloc] initWithRay:r upV:up Fov:DEFAULT_FOV_IN_DEGREES AspectRatio:aspect nearPlane:DEFAULT_NEAR_PLANE farPlane:DEFAULT_FAR_PLANE];
        self.camera.focalPoint = PointF(0,0,0);
        self.camera.name = @"LiveViewCamera";
        self->m_liveViewOptions.camera = self.camera;
    }
    
    // Pinch to zoom in and out
    UIPinchGestureRecognizer *pinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinchGestureRecognizer:)];
    
    // Rotate gesture to change the roll of the camera
    UIRotationGestureRecognizer *rotate = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(rotateGestureRecognizer:)];
    
    // Single Tap to stop/start rotation
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapGestureRecognizer:)];
    singleTap.numberOfTapsRequired = 1;
    singleTap.numberOfTouchesRequired = 1;
    
    // Double tap to display options
    UITapGestureRecognizer *doubleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTapGestureRecognizer:)];
    doubleTap.numberOfTapsRequired = 2;
    doubleTap.numberOfTouchesRequired = 1;
    
    // Single finger pan operates the trackball to rotate the camera
    UIPanGestureRecognizer * panGestureRecognizer = [[UIPanGestureRecognizer alloc]
                                                     initWithTarget:self action: @selector(panGestureRecognizer:)];
    panGestureRecognizer.minimumNumberOfTouches  = 1;
    panGestureRecognizer.maximumNumberOfTouches = 2;
    
    [self.view addGestureRecognizer:rotate];
    [self.view addGestureRecognizer:pinch];
    [self.view addGestureRecognizer:singleTap];
    [self.view addGestureRecognizer:doubleTap];
    [self.view addGestureRecognizer:panGestureRecognizer];
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    
    /**
     * Set a rectangle to draw screen space bounds for the rectangle
     * that indicates where trackball movements are arbitrary rotations
     * or rotations about the z-axis.
     */
    NSUInteger width = self.view.bounds.size.width;
    NSUInteger height = self.view.bounds.size.height;
    
    CGRect trackBallRect;
    trackBallRect.size.height = height*m_trackBall.getRadius();
    trackBallRect.size.width = width*m_trackBall.getRadius();
    trackBallRect.origin.x = (width - trackBallRect.size.width)*0.5;
    trackBallRect.origin.y = (height - trackBallRect.size.height)*0.5;
    m_trackBallRect = CGPathCreateWithRect(trackBallRect, NULL);
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(orientationChanged:)
                                                 name:UIDeviceOrientationDidChangeNotification
                                               object:nil];
    
    [self setupGL];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    [self saveLiveViewOptions];
}

- (void) viewDidUnload {
    [self saveLiveViewOptions];
}

- (void) viewWillDisappear {
    [self saveLiveViewOptions];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    CGPathRelease(m_trackBallRect);
    
    delete m_box;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    [self loadShaders];
    
    self.effect = [[GLKBaseEffect alloc] init];
    self.effect.light0.enabled = GL_FALSE;
    self.effect.light0.diffuseColor = GLKVector4Make(1.0f, 0.4f, 0.4f, 1.0f);
    
    GLKVector4 c;
    c.r = 1; c.g = c.g = 0; c.a = 1;
    self.effect.constantColor = c;
    
    glEnable(GL_DEPTH_TEST);
    
    if (m_box) {
        OpenGLRenderUnit * ru = [[OpenGLRenderUnit alloc] initWithShader:Nil polygonMesh:m_box->getPolygonMesh()];
        [[m_renderManager getOpenGLRenderer] addRenderUnit:ru];
    }

    /*glGenVertexArraysOES(1, &_vertexArray);
    glBindVertexArrayOES(_vertexArray);
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    
    glBufferData(GL_ARRAY_BUFFER, m_box->getPolygonMesh()->vertSize(), m_box->getPolygonMesh()->getRawVerts(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
    
    glBindVertexArrayOES(_vertexArray);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_box->getPolygonMesh()->triMemSize(), m_box->getPolygonMesh()->getTris(), GL_STATIC_DRAW);
    */
    
    // TODO Create OpenGLRenderUnit object for this
    
    glGenVertexArraysOES(1, &_tbVertexArray);
    glBindVertexArrayOES(_tbVertexArray);
    
    glGenBuffers(1, &_tbVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _tbVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trackBallVertexData), trackBallVertexData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
    //glDisableVertexAttribArray(GLKVertexAttribNormal);
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
    
    glBindVertexArrayOES(_tbVertexArray);
    
    glGenTextures(1, m_textures);
    
    /*
     void glTexImage2D(	GLenum target,
     GLint level,
     GLint internalFormat,
     GLsizei width,
     GLsizei height,
     GLint border,
     GLenum format,
     GLenum type,
     const GLvoid * data);
     */
   
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, [m_TextureData bytes]);
   
    /*
     NSDictionary *fbData = [renderer getFrameBufferPixels:fbOptions];
     NSData *data = fbData[@"data"];
     NSUInteger width = [fbData[@"width"] integerValue];
     NSUInteger height = [fbData[@"height"] integerValue];
     NSUInteger bytesPerRow = [fbData[@"rowSize"] integerValue];
     
     CGSize size;
     size.width = width;
     size.height = height;
     
     CIImage *ciImage = [CIImage imageWithBitmapData:data bytesPerRow:bytesPerRow size:size format:kCIFormatARGB8 colorSpace:m_colorSpace];
     UIImage *uiImage = [UIImage imageWithCIImage:ciImage];
    */
    /*
     size_t width,
     size_t height,
     size_t bitsPerComponent,
     size_t bitsPerPixel,
     size_t bytesPerRow,
     CGColorSpaceRef colorspace,
     CGBitmapInfo bitmapInfo,
     CGDataProviderRef provider,
     const CGFloat decode[],
     bool shouldInterpolate,
     CGColorRenderingIntent intent
    */
    /*CGDataProviderRef dataProvider = CGDataProviderCreateWithData(NULL, [m_TextureData bytes], [m_TextureData length], NULL);
    CGImageRef textureImage = CGImageCreate(32,32,8,32,32*4,
                                            CGColorSpaceCreateDeviceRGB(),
                                            kCGBitmapByteOrderDefault,
                                            dataProvider,
                                            NULL,
                                            YES,
                                            kCGRenderingIntentDefault
    );
    
    UIImage *uiImage = [UIImage imageWithCGImage:textureImage];
    
    NSError *textureError;
    NSDictionary *options = @{GLKTextureLoaderOriginBottomLeft : [NSNumber numberWithBool:YES]};
    m_TextureInfo = [GLKTextureLoader textureWithCGImage:uiImage.CGImage options:options error:&textureError];
    
    
    if (textureError) {
        NSLog(@"%@\n", [textureError description]);
    } else {
        //glBindTexture(m_TextureInfo.target, m_TextureInfo.name);
        //glEnable(m_TextureInfo.target);
    }*/
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    glDeleteBuffers(1, &_tbVertexBuffer);
    glDeleteVertexArraysOES(1, &_tbVertexArray);
    
    //glDeleteBuffers(1, &_vertexBuffer);
    //glDeleteVertexArraysOES(1, &_vertexArray);
    
    self.effect = nil;
    
    //if (_program) {
      //  glDeleteProgram(_program);
        //_program = 0;
    //}
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    float aspect = self.camera.aspectRatio;
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(
        GLKMathDegreesToRadians(self.camera.fov), aspect, self.camera.nearPlane, self.camera.farPlane
    );
    
    // eye, center, up
    PointF pos = [self.camera getPos];
    PointF focalPoint = self.camera.focalPoint;
    VectorF up = self.camera.up;
    GLKMatrix4 lookAt = GLKMatrix4MakeLookAt(
        pos.x(), pos.y(), pos.z(),
        focalPoint.x(), focalPoint.y(), focalPoint.z(),
        up.x(), up.y(), up.z()
    );
    
    GLKMatrix4 trackBallMatrix = GLKMatrix4Identity;
  
    // quat rotation comes first
    Framework::Math::Quat q = m_trackBall.getCurrentRotation();
    if (q.length() > 0) {
        GLKQuaternion quaternion;
        
        quaternion.s = q.s();
        quaternion.v.x = q.x();
        quaternion.v.y = q.y();
        quaternion.v.z = q.z();
        
        trackBallMatrix = GLKMatrix4MakeWithQuaternion(quaternion);
        
        // matrix to rotate
        lookAt = GLKMatrix4Multiply(lookAt, trackBallMatrix);
    }
    
    projectionMatrix = GLKMatrix4Multiply(projectionMatrix, lookAt);
   
    GLKMatrix4 baseModelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0.0f);
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    
    _normalMatrix = GLKMatrix3InvertAndTranspose(GLKMatrix4GetMatrix3(modelViewMatrix), NULL);
    _modelMatrix = modelViewMatrix;
    _modelViewProjectionMatrix = GLKMatrix4Multiply(projectionMatrix, modelViewMatrix);
    
    //_rotation += self.timeSinceLastUpdate * 0.5f;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_liveViewOptions.showTrackballBounds) {
        //glDisable(GL_TEXTURE_2D);
        self.effect.transform.projectionMatrix = GLKMatrix4MakeOrtho(0, 1, 0, 1, 1, -1);
        self.effect.transform.modelviewMatrix = GLKMatrix4Identity;
        
        glBindVertexArrayOES(_tbVertexArray);
        
        [self.effect prepareToDraw];
        glLineWidth(3);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    
    //glBindVertexArrayOES(_vertexArray);
    
    GLfloat lightingModel[4] = {m_liveViewOptions.lightingFalloff, 0, 0, 0};
    
    [ShaderProgram setRenderingMode:m_liveViewOptions.renderingMode];
    [ShaderProgram setModelViewProjectionMatrix:&_modelViewProjectionMatrix];
    
    [m_shaderProgram enable];
    [m_shaderProgram setLightingModel:lightingModel immediately:YES];
    [m_shaderProgram setNormalMatrix:&_normalMatrix immediately:YES];
    [m_shaderProgram setModelMatrix:&_modelMatrix immediately:YES];
    
    TextureSetupParams p;
    p.m_params[0].m_pname = GL_TEXTURE_MIN_FILTER;
    p.m_params[0].m_type = TEXTURE_PARAM_TYPE_INT;
    p.m_params[0].iVal = GL_LINEAR;
    
    p.m_params[1].m_pname = GL_TEXTURE_MAG_FILTER;
    p.m_params[1].m_type = TEXTURE_PARAM_TYPE_INT;
    p.m_params[1].iVal = GL_LINEAR;
    
    p.m_params[2].m_pname = GL_TEXTURE_WRAP_S;
    p.m_params[2].m_type = TEXTURE_PARAM_TYPE_INT;
    p.m_params[2].iVal = GL_REPEAT;
    
    p.m_params[3].m_pname = GL_TEXTURE_WRAP_T;
    p.m_params[3].m_type = TEXTURE_PARAM_TYPE_INT;
    p.m_params[3].iVal = GL_REPEAT;
    
    p.m_numParams = 4;
    
    [m_shaderProgram setupTexture2D:UNIFORM_DIFFUSE_TEXTURE textureResource:m_textures[0] samplerNumber:0 params:&p];
    
    
    [[m_renderManager getOpenGLRenderer] render];
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    //glDrawElements(GL_TRIANGLES, m_box->getPolygonMesh()->numTris()*3, GL_UNSIGNED_INT, (void*)0);
}

#pragma mark -  OpenGL ES 2 shader compilation

- (BOOL)loadShaders
{
    if (!m_shaderProgram) {
        m_shaderProgram = [[ShaderProgram alloc] initWithName:@"Simple Shader" vertexShaderPath:@"Shader" fragmentShaderPath:@"Shader"];
    }
    
    return m_shaderProgram.valid;
}

- (IBAction)renderViewButtonPressed:(id)sender {}

- (IBAction)optionsButtonPressed:(UIButton *)sender {}

/**
 * Show UI for selecting rendering mode. 
 * See ViewController_RenderMode.h and ViewController+RenderMode.h
 */
- (IBAction)renderModeButtonPressed:(UIButton *)sender forEvent:(UIEvent *)event {
    [self showRenderModeView];
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (NSUInteger) supportedInterfaceOrientations {
    return (UIInterfaceOrientationMaskAll);
}

- (void)orientationChanged:(NSNotification*) notification {
}

-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    float aspect;
    if (UIInterfaceOrientationMaskLandscape | toInterfaceOrientation) {
        aspect = fabsf(self.view.bounds.size.height / self.view.bounds.size.width);
    } else {
        aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    }
    
    self.camera.aspectRatio = aspect;
}

-(void) willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    
}

- (IBAction)singleTapGestureRecognizer:(UITapGestureRecognizer*)recognizer {
   
    if (UIGestureRecognizerStateEnded == recognizer.state)
    {
         NSLog(@"Single Tap Gesture State Ended\n");
        // Single tap stops and starts trackball.
    } else {
        NSLog(@"Single Tap Gesture State %d\n", recognizer.state);
    }
}

- (IBAction)doubleTapGestureRecognizer:(UITapGestureRecognizer*)recognizer {
  
    if (UIGestureRecognizerStateEnded == recognizer.state)
    {
        // Double tap stops trackball and shows button for options
        NSLog(@"Double Tap Gesture State Ended\n");
        
        //[self.view bringSubviewToFront:self.optionsButton];
        //self.optionsButton.hidden = !self.optionsButton.hidden;
    } else {
        NSLog(@"Double Tap Gesture State %d\n", recognizer.state);
    }
}

- (IBAction)longPressGestureRecognizer:(UILongPressGestureRecognizer*)recognizer {
     NSLog( @"%@\n", [recognizer description]);
}

- (IBAction)pinchGestureRecognizer:(UIPinchGestureRecognizer*)recognizer {
    if (UIGestureRecognizerStateBegan == recognizer.state) {
        m_camPinchLastTime = [NSDate date];
    } else if (UIGestureRecognizerStateChanged == recognizer.state) {
        if (0 == recognizer.velocity) {
            m_camPinchLastTime = [NSDate date];
            return;
        }
        
        NSTimeInterval pinchDelta = -[m_camPinchLastTime timeIntervalSinceNow];
        float scale = (pinchDelta*recognizer.velocity);
        
        /*NSLog(@"Pinch Scale(%.2f) Velocity(%.2f) Delta(%.2f) Scale(%.2f_\n",
              recognizer.scale, recognizer.velocity, pinchDelta, scale
        );*/
        
        PointF pos = [self.camera getPos];
        VectorF lookAt = [self.camera getDir];
        
        // velocity = (scale factor)/sec
        // scale = scale factor
        // time = seconds        p
        pos = Math::vec3AXPlusBY(pos, 1, lookAt, scale);
        self.camera.focalPoint = Math::vec3AXPlusBY(self.camera.focalPoint, 1, lookAt, scale);
        [self.camera setPos:pos];
        
        m_camPinchLastTime = [NSDate date];
    }
}

- (IBAction)rotateGestureRecognizer:(UIRotationGestureRecognizer*)sender {

    switch (sender.state) {
        case UIGestureRecognizerStateBegan:
            ;
            break;
        case UIGestureRecognizerStateChanged:
            ;
            break;
        case UIGestureRecognizerStateEnded:
        case UIGestureRecognizerStateCancelled:
            ;
            break;
        default:
            break;
    }
    
    NSLog(@"State %d %f %f\n", sender.state, [sender rotation], sender.velocity);
}

- (IBAction)panGestureRecognizer:(UIPanGestureRecognizer *)recognizer {
    NSUInteger width = self.view.bounds.size.width;
    NSUInteger height = self.view.bounds.size.height;
    CGPoint l = [recognizer locationInView:self.view];
   
    // Translate pan location to [-1,1]
    // and create a point on a sphere for rotations
    if (UIGestureRecognizerStateBegan == recognizer.state) {
        // On pan start get initial position for trackball rotation
        float x = (2*l.x / (width) - 1);
        float y = -(2*l.y / (height) - 1);
        m_trackBall.initialize(x,y);
    }
    else if (UIGestureRecognizerStateChanged == recognizer.state) {
        // On pan start get initial position for trackball rotation
        //state = @"Changed";
        
        // get location in [-1,1];
        /*
           iOS screen layout:
         
            [0,0] .... [1,0]
         
            [0,1] .... [1,1]
         
           Maps to 
            [-1,1]  .. [1,1]
         
            [-1,-1] .. [1,-1]
         */
        float x = (2*l.x / (width) - 1);
        float y = -(2*l.y / (height) - 1);
        
        //Framework::PointF p = m_trackBall.projectToSphere(x, y);
        
        m_trackBall.updateRotation(x,y);
        
        // Rotate Camera b trackball;
        
        //Framework::Math::Quat q = m_trackBall.getCurrentRotation();
        
        //float angle;
        //Framework::VectorF vector;
        
        //q.extractAngleAndVector(angle, vector);
        //angle = (angle*180/M_PI);
        
        //NSLog(@"TB (%.2f,%.2f) -> (%.2f,%.2f,%.2f) (%.2f,%.2f,%.2f,%.2f)\n",
        //      x, y, p.v[0], p.v[1], p.v[2], angle, vector.v[0], vector.v[1], vector.v[2]);
    }
    else if (UIGestureRecognizerStateEnded == recognizer.state ||
               UIGestureRecognizerStateChanged == recognizer.state) {
        m_trackBall.disable();
    }
}

- (void) saveLiveViewOptions {
    // Save rendering parameters to LiveViewOptions
    m_liveViewOptions.trackBall = m_trackBall.getCurrentRotation();
}

@end
