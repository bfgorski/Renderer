//
//  ViewController+RenderMode.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/23/13.
//
//

#import "ViewController.h"

@interface ViewController (RenderMode)

/**
 * Display a view with UIPickerView to select the RenderingMode.
 */
- (void)showRenderModeView;

/**
 * Hide the UI overlayed on top of the main rendering view.
 */
- (IBAction)hideRenderModeView:(id)sender;

@end
