//
//  ViewController.h
//  SanAntonio
//
//  Created by Benjamin Gregorski on 9/7/13.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@class Camera;

@interface ViewController : GLKViewController <UIPickerViewDelegate>

@property (weak, nonatomic) IBOutlet UIButton *renderViewButton;
@property (weak, nonatomic) IBOutlet UIButton *optionsButton;
@property (weak, nonatomic) IBOutlet UIButton *renderModeButton;

- (IBAction)renderViewButtonPressed:(id)sender;
- (IBAction)optionsButtonPressed:(UIButton *)sender;
- (IBAction)renderModeButtonPressed:(UIButton *)sender forEvent:(UIEvent *)event;

@end
