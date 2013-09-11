//
//  RenderViewController.m
//  Renderer
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import "RenderViewController.h"
#import "RenderManager.h"

@interface RenderViewController ()
{
    CGColorSpaceRef m_colorSpace;
}

@end

@implementation RenderViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        m_colorSpace = CGColorSpaceCreateDeviceRGB();
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)renderScene:(id)sender {
    NSDictionary *options = @{
        @"saveFile" : @"Documents/image.png"
    };
    Renderer *renderer = [[RenderManager instance] getActiveRenderer];
    [renderer render:options];
    
    NSDictionary *fbOptions = @{
        @"ARGB": [NSNumber numberWithBool:YES]
    };
    
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
    
    /*UIImageWriteToSavedPhotosAlbum(uiImage,
                                   self,
                                   @selector(saveImageHandler:didFinishSavingWithError:contextInfo:),
                                   NULL
                                   );*/
    
    CGRect imageViewBounds = self.imageView.bounds;
    float imageViewAspectRatio = (float)imageViewBounds.size.width /(float)imageViewBounds.size.height;
    
    // create CGRect in center of imageView with the image's aspect ratio
    float uiImageAspectRatio = (float)width/(float)height;
    
    CGRect drawRect;
    drawRect.origin = imageViewBounds.origin;
    
    if (imageViewAspectRatio > uiImageAspectRatio) {
        // If necessary image height shrinks to fit UIImageView
        if (height > imageViewBounds.size.height) {
            drawRect.size.height = imageViewBounds.size.height;
            drawRect.size.width = drawRect.size.height*uiImageAspectRatio;
        } else {
            drawRect.size.height = height;
            drawRect.size.width = width;
        }
    } else {
        // If necessary image width shrinks to fit UIImageView
        if (width > imageViewBounds.size.width) {
            drawRect.size.width = imageViewBounds.size.width;
            drawRect.size.height = drawRect.size.width/uiImageAspectRatio;
        } else {
            drawRect.size.height = height;
            drawRect.size.width = width;
        }
    }
    
    self.imageView.image = uiImage;
}

- (void)saveImageHandler:(UIImage *) image
didFinishSavingWithError: (NSError *)error
             contextInfo: (void *) contextInfo {
    
    if (error) {
        return;
    }
    
}

@end
