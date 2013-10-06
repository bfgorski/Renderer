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
#import "Camera.h"
#import "LiveViewOptions.h"
#include "Trackball.h"
#include "BasicTypesImpl.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Uniform index.
enum
{
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    UNIFORM_NORMAL_MATRIX,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

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

GLfloat gCubeVertexData[216] = 
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    
    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
    
    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
    
    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
};

static GLfloat DEFAULT_FOV_IN_DEGREES = 65.0f;
static GLfloat DEFAULT_NEAR_PLANE = 0.1;
static GLfloat DEFAULT_FAR_PLANE = 100;

using namespace Framework;

@interface ViewController () {
    GLuint _program;
    
    GLKMatrix4 _modelViewProjectionMatrix;
    GLKMatrix3 _normalMatrix;
    float _rotation;
    
    GLuint _vertexArray;
    GLuint _vertexBuffer;
    
    GLuint _tbVertexArray;
    GLuint _tbVertexBuffer;
    
    Math::Trackball m_trackBall;
    
    NSDate *m_camPinchLastTime;
    
    /**
     * Rectangle that can be drawn on screen to show where
     * the trackball boundary is.
     */
    CGPathRef m_trackBallRect;
    
    /**
     * Rendering options for the realtime view.
     */
    LiveViewOptions * m_liveViewOptions;
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;
@property (strong, nonatomic) Camera *camera;

- (void)setupGL;
- (void)tearDownGL;

- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    m_liveViewOptions = [LiveViewOptions instance];
    
    m_trackBall.setRadius(0.9);
    m_trackBall.reset();
    
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

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    CGPathRelease(m_trackBallRect);
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
    
    glGenVertexArraysOES(1, &_vertexArray);
    glBindVertexArrayOES(_vertexArray);
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gCubeVertexData), gCubeVertexData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
    
    glBindVertexArrayOES(_vertexArray);
    
    glGenVertexArraysOES(1, &_tbVertexArray);
    glBindVertexArrayOES(_tbVertexArray);
    
    glGenBuffers(1, &_tbVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _tbVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trackBallVertexData), trackBallVertexData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
    //glDisableVertexAttribArray(GLKVertexAttribNormal);
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
    
    glBindVertexArrayOES(_tbVertexArray);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    glDeleteBuffers(1, &_tbVertexBuffer);
    glDeleteVertexArraysOES(1, &_tbVertexArray);
    
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArraysOES(1, &_vertexArray);
    
    self.effect = nil;
    
    if (_program) {
        glDeleteProgram(_program);
        _program = 0;
    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    float aspect = self.camera.aspectRatio; // fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
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
        
        // rotate the camera by the trackball's rotation.
        lookAt = GLKMatrix4Multiply(lookAt, trackBallMatrix);
    }
    
    projectionMatrix =  GLKMatrix4Multiply(projectionMatrix, lookAt);
    //self.effect.transform.projectionMatrix = projectionMatrix;
   
    GLKMatrix4 baseModelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0.0f);
    //baseModelViewMatrix = GLKMatrix4Rotate(baseModelViewMatrix, _rotation, 0.0f, 1.0f, 0.0f);
    
    // Compute the model view matrix for the object rendered with GLKit
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0.0f);
    //modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    //modelViewMatrix = GLKMatrix4Multiply(modelViewMatrix, trackBallMatrix);
    
    //self.effect.transform.modelviewMatrix = modelViewMatrix;
    
    // Compute the model view matrix for the object rendered with ES2
    modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 0.0f);
    //modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    //modelViewMatrix = GLKMatrix4Multiply(modelViewMatrix, trackBallMatrix);
    
    _normalMatrix = GLKMatrix3InvertAndTranspose(GLKMatrix4GetMatrix3(modelViewMatrix), NULL);
    
    _modelViewProjectionMatrix = GLKMatrix4Multiply(projectionMatrix, modelViewMatrix);
    
    //_rotation += self.timeSinceLastUpdate * 0.5f;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_liveViewOptions.showTrackballBounds) {
        self.effect.transform.projectionMatrix = GLKMatrix4MakeOrtho(0, 1, 0, 1, 1, -1);
        self.effect.transform.modelviewMatrix = GLKMatrix4Identity;
        
        glBindVertexArrayOES(_tbVertexArray);
        
        [self.effect prepareToDraw];
        glLineWidth(3);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    
    glBindVertexArrayOES(_vertexArray);
    // Render the object again with ES2
    glUseProgram(_program);
    
    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, _modelViewProjectionMatrix.m);
    glUniformMatrix3fv(uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, _normalMatrix.m);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

#pragma mark -  OpenGL ES 2 shader compilation

- (BOOL)loadShaders
{
    GLuint vertShader, fragShader;
    NSString *vertShaderPathname, *fragShaderPathname;
    
    // Create shader program.
    _program = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
    if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname]) {
        NSLog(@"Failed to compile vertex shader");
        return NO;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
    if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname]) {
        NSLog(@"Failed to compile fragment shader");
        return NO;
    }
    
    // Attach vertex shader to program.
    glAttachShader(_program, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(_program, fragShader);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(_program, GLKVertexAttribPosition, "position");
    glBindAttribLocation(_program, GLKVertexAttribNormal, "normal");
    
    // Link program.
    if (![self linkProgram:_program]) {
        NSLog(@"Failed to link program: %d", _program);
        
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (_program) {
            glDeleteProgram(_program);
            _program = 0;
        }
        
        return NO;
    }
    
    // Get uniform locations.
    uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(_program, "modelViewProjectionMatrix");
    uniforms[UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(_program, "normalMatrix");
    
    // Release vertex and fragment shaders.
    if (vertShader) {
        glDetachShader(_program, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(_program, fragShader);
        glDeleteShader(fragShader);
    }
    
    return YES;
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        NSLog(@"Failed to load vertex shader");
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    
    return YES;
}

- (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (BOOL)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (IBAction)renderViewButtonPressed:(id)sender {}

- (IBAction)optionsButtonPressed:(UIButton *)sender {
    // after 5 seconds hide the button
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
    /*CGPoint t = [recognizer translationInView:self.view];
    CGPoint v = [recognizer velocityInView:self.view];*/
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

@end
