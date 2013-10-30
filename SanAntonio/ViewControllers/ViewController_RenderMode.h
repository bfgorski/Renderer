//
//  ViewController_RenderModeView.h
//  Renderer
//
//  Created by Benjamin Gregorski on 10/23/13.
//
//

#import "ViewController.h"

@class LiveViewOptions;

@interface ViewController ()
{
    /**
     * Rendering options for the realtime view.
     */
    LiveViewOptions * m_liveViewOptions;
    
    /**
     * Custom View for selecting the rendering mode.
     */
    UIView * m_renderModeView;
    
    /**
     * UIPickerView for selecting rendering mode.
     */
    UIPickerView *m_renderModePicker;
}

@end
