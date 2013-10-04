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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)showTrackballBounds:(id)sender forEvent:(UIEvent *)event {
}
@end
