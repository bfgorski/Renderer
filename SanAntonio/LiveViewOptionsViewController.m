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
        // Custom initialization
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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(LiveViewOptions*) getOptions {
    return (self.liveViewOptions ? self.liveViewOptions : [LiveViewOptions instance]);
}

- (IBAction)showTrackballBounds:(UISwitch*)sender forEvent:(UIEvent *)event {
    LiveViewOptions * l = (self.liveViewOptions ? self.liveViewOptions : [LiveViewOptions instance]);
    l.showTrackballBounds = sender.on;
}

- (IBAction)showWireframe:(UISwitch*)sender forEvent:(UIEvent *)event {
    LiveViewOptions *l = [self getOptions];
    l.wireframe = sender.on;
}

@end
