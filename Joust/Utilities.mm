//
//  Utilities.mm
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "Utilities.h"
#include <sys/time.h>
#include <time.h>

struct timeval gStartTime;

float getTimeNow(void) {
	static int runOnce = 0;
	if(!runOnce) {
		gettimeofday(&gStartTime, 0);
		runOnce = 1;
	}

	struct timeval newtime;
	gettimeofday(&newtime,0);
	
	newtime.tv_sec -= gStartTime.tv_sec;

	float now = newtime.tv_sec;
	now += newtime.tv_usec / 1000000.0;
	now -= gStartTime.tv_usec / 1000000.0;
	
	return now;
}

// Get the URL to the sound file to play
static CFURLRef headshotSoundFileURLRef =	CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("headshot"), CFSTR ("wav"), NULL);
static CFURLRef noSoundFileURLRef =			CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("playerno"), CFSTR ("wav"), NULL);
static CFURLRef scratchSoundFileURLRef =	CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("scratch"), CFSTR ("wav"), NULL);
static CFURLRef snapSoundFileURLRef =		CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("snap"), CFSTR ("wav"), NULL);
static CFURLRef trotSoundFileURLRef =		CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("trot"), CFSTR ("wav"), NULL);
static CFURLRef whoopSoundFileURLRef =		CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("whoop"), CFSTR ("wav"), NULL);
static CFURLRef woundSoundFileURLRef =		CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("wound"), CFSTR ("wav"), NULL);
static CFURLRef yeaSoundFileURLRef =		CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR ("yea"), CFSTR ("wav"), NULL);

static SystemSoundID headshotSound;
static SystemSoundID noSound;
static SystemSoundID scratchSound;
static SystemSoundID snapSound;
static SystemSoundID trotSound;
static SystemSoundID whoopSound;
static SystemSoundID woundSound;
static SystemSoundID yeaSound;

@implementation Utilities

- (id) init {
	if(self = [super init]) {
		// Create a system sound object representing the sound file
		static Boolean initialized = NO;
		if(!initialized) {
			AudioServicesCreateSystemSoundID(headshotSoundFileURLRef, &headshotSound);
			AudioServicesCreateSystemSoundID(noSoundFileURLRef, &noSound);
			AudioServicesCreateSystemSoundID(scratchSoundFileURLRef, &scratchSound);
			AudioServicesCreateSystemSoundID(snapSoundFileURLRef, &snapSound);
			AudioServicesCreateSystemSoundID(trotSoundFileURLRef, &trotSound);
			AudioServicesCreateSystemSoundID(whoopSoundFileURLRef, &whoopSound);
			AudioServicesCreateSystemSoundID(woundSoundFileURLRef, &woundSound);
			AudioServicesCreateSystemSoundID(yeaSoundFileURLRef, &yeaSound);
			initialized = YES;
		}
	}
	return self;
}

- (void) playSound:(NSString*) soundID {
	if([soundID isEqualToString:@"headshot"]) {
		AudioServicesPlaySystemSound(headshotSound);
	}
	else if([soundID isEqualToString:@"no"]) {
		AudioServicesPlaySystemSound(noSound);
	}
	else if([soundID isEqualToString:@"scratch"]) {
		AudioServicesPlaySystemSound(scratchSound);
	}
	else if([soundID isEqualToString:@"snap"]) {
		AudioServicesPlaySystemSound(snapSound);
	}
	else if([soundID isEqualToString:@"trot"]) {
		AudioServicesPlaySystemSound(trotSound);
	}
	else if([soundID isEqualToString:@"whoop"]) {
		AudioServicesPlaySystemSound(whoopSound);
	}
	else if([soundID isEqualToString:@"wound"]) {
		AudioServicesPlaySystemSound(woundSound);
	}
	else if([soundID isEqualToString:@"yea"]) {
		AudioServicesPlaySystemSound(yeaSound);
	}
}

@end
