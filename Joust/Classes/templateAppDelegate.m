//
//  templateAppDelegate.m
//  template
//
//  Created by SIO2 Interactive on 8/22/08.
//  Copyright SIO2 Interactive 2008. All rights reserved.
//

#import "templateAppDelegate.h"
#import "EAGLView.h"
#import "GameState.h"
#import "PlayState.h"
#import "Utilities.h"

extern GameState* gCurrentGameState;

@implementation templateAppDelegate

@synthesize window;
@synthesize glView;

- (void)applicationDidFinishLaunching:(UIApplication *)application {

	glView.animationInterval = 1.0 / 60.0;
	[glView startAnimation];

	[[UIApplication sharedApplication] setIdleTimerDisabled:NO];
		
	// Flip the simulator to the right
	[[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationLandscapeRight animated: NO];

    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:( 1.0f / 30.0f )];
    [[UIAccelerometer sharedAccelerometer] setDelegate:self];
	
	// initialize the sounds here
	Utilities* util = [[Utilities alloc] init];
	[util release];
}


- (void)applicationWillResignActive:(UIApplication *)application {
	glView.animationInterval = 1.0 / 5.0;
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
	glView.animationInterval = 1.0 / 60.0;
}

- (void)dealloc {
	[window release];
	[glView release];
	[super dealloc];
}


- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	sio2->_SIO2window->accel->x = acceleration.x * 0.1f + sio2->_SIO2window->accel->x * 0.9f;
	sio2->_SIO2window->accel->y = acceleration.y * 0.1f + sio2->_SIO2window->accel->y * 0.9f;
	sio2->_SIO2window->accel->z = acceleration.z * 0.1f + sio2->_SIO2window->accel->z * 0.9f;	

	sio2ResourceDispatchEvents( sio2->_SIO2resource,
								sio2->_SIO2window,
								SIO2_WINDOW_ACCELEROMETER,
								SIO2_WINDOW_TAP_NONE );
}

- (IBAction) playGame {
	gCurrentGameState = [[PlayState alloc] init];
	menuImage.hidden = YES;
	playButton.hidden = YES;
}

@end
