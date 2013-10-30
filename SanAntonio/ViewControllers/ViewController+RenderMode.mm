//
//  ViewController+RenderMode.m
//  Renderer
//
//  Created by Benjamin Gregorski on 10/23/13.
//
//

#import "ViewController+RenderMode.h"
#import "ViewController_RenderMode.h"
#import "LiveViewOptions.h"

@implementation ViewController (RenderMode)

- (void)showRenderModeView {
    if (!m_renderModeView) {
        // UI to show picker with rendering modes
        CGRect rect;
        rect.origin.x = 10;
        rect.origin.y = self.view.bounds.size.height - 150;
        rect.size.width = self.view.bounds.size.width - 20;
        rect.size.height = 150;

        m_renderModeView = [[UIView alloc] initWithFrame:rect];

        //Set the customView properties
        m_renderModeView.alpha = 0.0;
        m_renderModeView.opaque = YES;
        m_renderModeView.backgroundColor = [UIColor grayColor];
        m_renderModeView.layer.cornerRadius = 5;
        m_renderModeView.layer.borderWidth = 1.5f;
        m_renderModeView.layer.masksToBounds = YES;
        
        // Intercept panning events so that they are not sent to the trackball.
        UIPanGestureRecognizer * panGestureRecognizer = [[UIPanGestureRecognizer alloc]
                                                         initWithTarget:self action: @selector(emptyPanGestureRecognizer:)];
        m_renderModeView.gestureRecognizers = @[panGestureRecognizer];
        
        
        CGRect buttonRect = CGRectMake(5, 5, 60,30);
        UIButton *closeButton = [[UIButton alloc] initWithFrame:buttonRect];
        [closeButton setTitle:@"Close" forState:UIControlStateNormal];
        [closeButton addTarget:self action:@selector(hideRenderModeView:) forControlEvents:UIControlEventTouchUpInside];
        closeButton.alpha = 0.5f;
        closeButton.opaque = YES;
        closeButton.backgroundColor = [UIColor blackColor];
        closeButton.layer.cornerRadius = 5;
        closeButton.layer.borderWidth = 1.5f;

        [m_renderModeView addSubview:closeButton];

        CGRect pickerRect = CGRectMake(70, 0, rect.size.width - 70, rect.size.height);
        m_renderModePicker = [[UIPickerView alloc] initWithFrame:pickerRect];
        m_renderModePicker.exclusiveTouch = YES;
        m_renderModePicker.dataSource = [LiveViewOptions instance];
        m_renderModePicker.delegate = self;

        // Add the customView to the current view
        [m_renderModeView addSubview:m_renderModePicker];
        [self.view addSubview:m_renderModeView];
    }
    
    [m_renderModePicker selectRow:m_liveViewOptions.renderingMode inComponent:0 animated:NO];
    
    // Disable before adding subview
    m_renderModeView.hidden = false;
    m_renderModeView.multipleTouchEnabled = YES;
    m_renderModeView.exclusiveTouch = YES;
    m_renderModeView.userInteractionEnabled = YES;
    
    [UIView animateWithDuration:0.25 animations:^{
       [m_renderModeView setAlpha:1.0];
    } completion:^(BOOL finished) {}];
}

- (IBAction) hideRenderModeView:(id)sender {
    //Display the customView with animation
    [UIView animateWithDuration:0.25 animations:^{
        [m_renderModeView setAlpha:0.0];
    } completion:^(BOOL finished) {
        m_renderModeView.hidden = YES;
        m_renderModeView.multipleTouchEnabled = NO;
        m_renderModeView.exclusiveTouch = NO;
        m_renderModeView.userInteractionEnabled = NO;
    }];
}

- (IBAction)emptyPanGestureRecognizer:(UIPanGestureRecognizer *)recognizer {}

/**
 * Methods for UIPickerViewDelegate
 */
- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component {
    return 20.0;
}

-(UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view {
    UILabel *label = [[UILabel alloc] init];
    [label setText:[LiveViewOptions getDescriptionForRenderingMode:row]];
    label.textAlignment = NSTextAlignmentCenter;
    return label;
}

-(NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    return [LiveViewOptions getDescriptionForRenderingMode:row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    m_liveViewOptions.renderingMode = (RenderingMode)row;
}

@end
