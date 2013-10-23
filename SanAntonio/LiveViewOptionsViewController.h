//
//  LiveViewOptionsViewController.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import <UIKit/UIKit.h>
#import "LiveViewOptions.h"

@interface LiveViewOptionsViewController : UIViewController<UIPickerViewDataSource, UIPickerViewDelegate>

@property (strong, nonatomic) LiveViewOptions *liveViewOptions;

@property (weak, nonatomic) IBOutlet UISwitch *showTrackballBoundsSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *drawWireframeSwitch;

@property (weak, nonatomic) IBOutlet UIPickerView *renderModePicker;

@property (weak, nonatomic) IBOutlet UISlider *lightFalloffSlider;

- (IBAction)showTrackballBounds:(UISwitch*)sender forEvent:(UIEvent *)event;
- (IBAction)drawWireframe:(UISwitch *)sender forEvent:(UIEvent *)event;

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView;
- (IBAction)updateLightFalloff:(UISlider *)sender forEvent:(UIEvent *)event;

@end
