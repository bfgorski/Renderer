//
//  LiveViewOptionsViewController.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/4/13.
//
//

#import "LiveViewOptionsViewController.h"

@interface LiveViewOptionsViewController ()

@end

@implementation LiveViewOptionsViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    if (self) {
        _renderModePicker.delegate = self;
        _renderModePicker.dataSource = [self getOptions];
        _renderModePicker.showsSelectionIndicator = YES;
        [_renderModePicker selectRow:0 inComponent:0 animated:NO];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view.
    
    LiveViewOptions * l = [self getOptions];
    self.showTrackballBoundsSwitch.on = l.showTrackballBounds;
    self.drawWireframeSwitch.on = l.wireframe;
    self.lightFalloffSlider.value = l.lightingFalloff;
    self.renderModePicker.dataSource = [self getOptions];
    
    [self.renderModePicker selectRow:l.renderingMode inComponent:0 animated:NO];
    [self.lightFalloffLabel setText:[NSString stringWithFormat:@"Falloff %.2f", l.lightingFalloff]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    // Dispose of any resources that can be recreated.
    self.liveViewOptions = nil;
}

-(LiveViewOptions*) getOptions {
    return (self.liveViewOptions ? self.liveViewOptions : [LiveViewOptions instance]);
}

- (IBAction)showTrackballBounds:(UISwitch*)sender forEvent:(UIEvent *)event {
    LiveViewOptions * l = (self.liveViewOptions ? self.liveViewOptions : [LiveViewOptions instance]);
    l.showTrackballBounds = sender.on;
}

- (IBAction)drawWireframe:(UISwitch *)sender forEvent:(UIEvent *)event {
    LiveViewOptions *l = [self getOptions];
    l.wireframe = sender.on;
}

- (IBAction)updateLightFalloff:(UISlider *)sender forEvent:(UIEvent *)event {
    LiveViewOptions *l = [self getOptions];
    l.lightingFalloff = sender.value;
    
    [self.lightFalloffLabel setText:[NSString stringWithFormat:@"Falloff %.2f", l.lightingFalloff]];
}

/**
 * PickerView Delegate methods for UIPickerViewDelegate
 */
- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component {
    if (self.renderModePicker == pickerView && (0 == component)) {
        return 40.0;
    }
    return 0.0;
}

-(UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view {
    if (self.renderModePicker == pickerView && (0 == component)) {
        UILabel *label = [[UILabel alloc] init];
        [label setText:[LiveViewOptions getDescriptionForRenderingMode:row]];
        label.font = [UIFont systemFontOfSize:20.0];
        label.textAlignment = NSTextAlignmentCenter;
        return label;
    }
    return nil;
}

-(NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    if (self.renderModePicker == pickerView && (0 == component)) {
        return [LiveViewOptions getDescriptionForRenderingMode:row];
    }
    return @"";
}

- (NSAttributedString *)pickerView:(UIPickerView *)pickerView attributedTitleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return nil;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    if (self.renderModePicker == pickerView) {
        LiveViewOptions *l = [self getOptions];
        l.renderingMode = (RenderingMode)row;
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSLog(@"Preparing for Seque %@ %@\n", [segue description], [sender description]);
}















@end
