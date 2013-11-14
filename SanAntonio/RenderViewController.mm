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

- (void)dealloc {
    CGColorSpaceRelease(m_colorSpace);
}

- (IBAction)renderScene:(id)sender {
    NSDictionary *options = @{
        @"saveFile" : @"Documents/image.png"
    };
    Renderer *renderer = [[RenderManager instance] getActiveRenderer];
    [renderer render:options];
    
    NSDictionary *fbOptions = @{
        @"ARGB": [NSNumber numberWithBool:YES],
        @"topRowFirst" : [NSNumber numberWithBool:YES]
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
    
    /*if([[UIDevice currentDevice]userInterfaceIdiom]==UIUserInterfaceIdiomPhone) {
        if ([[UIScreen mainScreen] bounds].size.height == 640) {
            CGRect rect = self.imageViewContainer.bounds;
            rect.size.height = 600;
            [self.imageViewContainer setBounds:rect];
        }
        else {
            //iphone 3.5 inch screen
            CGRect rect = self.imageViewContainer.bounds;
            rect.size.height = 400;
            [self.imageViewContainer setBounds:rect];
        }
    }*/
    
    CGRect imageViewBounds = self.imageViewContainer.bounds;
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
    
    // Figure out origin point
    drawRect.origin.x = ((imageViewBounds.size.width - drawRect.size.width) / 2);
    drawRect.origin.y = ((imageViewBounds.size.height - drawRect.size.height) / 2);
    
    self.imageView.contentMode = UIViewContentModeRedraw;
    self.imageView.frame = drawRect;
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
