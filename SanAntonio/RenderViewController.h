//
//  RenderViewController.h
//  Renderer
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import <UIKit/UIKit.h>
#include "Renderer.h"

@interface RenderViewController : UIViewController

@property (weak, nonatomic) Renderer* renderer;

@property (weak, nonatomic) IBOutlet UIButton *renderButton;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UIButton *liveViewButton;

@property (weak, nonatomic) IBOutlet UIView *imageViewContainer;
- (IBAction)renderScene:(id)sender;


@end
