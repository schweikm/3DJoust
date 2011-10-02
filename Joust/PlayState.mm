//
//  PlayState.mm
//  template
//
//  Created by Andrew Putman on 4/13/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "PlayState.h"
#import "AiKnightPlayer.h"
#import "HumanKnightPlayer.h"

#include <sys/time.h>
#include <time.h>
#import "Utilities.h"
@implementation PlayState
- (id) init {
	if(self = [super init]) {
		mDone = false;
		mWorld = [[GameObject alloc] init];
		mPlayerCamera = [[CameraObject alloc] init];
		mFieldCamera = [[CameraObject alloc] init];
		mStadium  = [[ModelObject alloc] init: mWorld model:@"stad_ob"];
		mStadium->mTransform->loc->z += -3.4;
		sio2TransformBindMatrix(mStadium->mTransform);

		mRail0 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mRail1 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mRail2 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mRail0->mTransform->loc->z = -1.0;
		mRail1->mTransform->loc->z = -1.0;	
		mRail2->mTransform->loc->z = -1.0;	
		mRail0->mTransform->loc->x = 20.0;	
		mRail2->mTransform->loc->x = -20.0;
		sio2TransformBindMatrix(mRail0->mTransform);
		sio2TransformBindMatrix(mRail1->mTransform);
		sio2TransformBindMatrix(mRail2->mTransform);
		
		mPlayerKnight = [[Knight alloc] init:mWorld type:@"light"];
		mPlayerCart = [[Cart alloc] init:mWorld type:@"light"];

		mOpponentKnight = [[Knight alloc] init:mWorld type:@"dark"];
		mOpponentCart = [[Cart alloc] init:mWorld type:@"dark"];

		[mPlayerCamera setGameObjectParent:mPlayerKnight->mHead];
		[mFieldCamera setGameObjectParent:mWorld];
		
		mPlayerCamera->mTransform->loc->x = 0.5;
		mPlayerCamera->mTransform->loc->z = 0.0;
		sio2TransformBindMatrix(mPlayerCamera->mTransform);

		mHumanPlayer = [[HumanKnightPlayer alloc] initHealth: 1.0 Knight:mPlayerKnight Cart:mPlayerCart World:mWorld];
		mComputerPlayer = [[AiKnightPlayer alloc] initHealth: 1.0 Knight:mOpponentKnight Cart:mOpponentCart World:mWorld];
		[mHumanPlayer addOpponent:mComputerPlayer];
		[mComputerPlayer addOpponent:mHumanPlayer];
		
		mLastTime = getTimeNow();
		
		[self resetForMatch];
	}
	return self;
}

- (void) dealloc {
	[mWorld goAway];
	[mPlayerCamera goAway];
	[mFieldCamera goAway];
	[mHumanPlayer release];
	[mComputerPlayer release];
	[super dealloc];
}

- (void) resetForMatch {	
	if(mPlayerCart->mKnight == nil) {
		[mPlayerCart attachKnight:mPlayerKnight];
	}
	if(mOpponentCart->mKnight == nil) {
		[mOpponentCart attachKnight:mOpponentKnight];
	}
	
	[mPlayerKnight resetForMatch];
	[mOpponentKnight resetForMatch];
	[mPlayerKnight resetForMatch];
	[mOpponentKnight resetForMatch];
	
	
	mPlayerCart->mTransform->loc->y = -0.75;
	mPlayerCart->mTransform->loc->x = -40.0;
	sio2TransformBindMatrix(mPlayerCart->mTransform);
	mOpponentCart->mTransform->loc->y = 0.75;
	mOpponentCart->mTransform->loc->x = 40.0;
	mOpponentCart->mTransform->rot->z = 180.0;
	sio2TransformBindMatrix(mOpponentCart->mTransform);
	
	mPlayerCart->mCartAcceleration = 3.0;
	mOpponentCart->mCartAcceleration = 3.0;
	mCurrentCamera = mPlayerCamera;
}

- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY {
	[mHumanPlayer processTouchMoveX:deltaX Y:deltaY];
	[mComputerPlayer processTouchMoveX:deltaX Y:deltaY];
}
- (void) processTouchX:(float) x Y:(float) y {
	x = 2 * x / 480 - 1.0;
	y = 2 * y / 320 - 1.0;
	
	[mHumanPlayer processTouchX:x Y:y];
	[mComputerPlayer processTouchX:x Y:y];
	
}
- (void) processAccelX:(float) x Y:(float) y Z:(float) z {
	[mHumanPlayer processAccelX:x Y:y Z:z];
	[mComputerPlayer processAccelX:x Y:y Z:z];
	//	printf("%f\n", z);
}
- (void) update {
	float now = getTimeNow();
	float delta = now - mLastTime;

	float distanceBetweenPlayers = fabs(mPlayerCart->mTransform->loc->x - mOpponentCart->mTransform->loc->x);

	if(distanceBetweenPlayers > 81) {
		if(mOpponentKnight->mHorse == nil || mPlayerKnight->mHorse == nil) {
			mDone = true;
		}
		[self resetForMatch];
	}
	
	float timeScaleFactor = (distanceBetweenPlayers-4) / 15;
	if(timeScaleFactor > 1) {
		timeScaleFactor = 1;
	}
	if(timeScaleFactor < 0.2) {
		timeScaleFactor = 0.2;
	}
	
	delta *= timeScaleFactor;
	
	[mHumanPlayer update:delta];
	[mComputerPlayer update:delta];
	[mWorld updateAll:delta];

	
	if(mCurrentCamera != mFieldCamera && distanceBetweenPlayers < 6) {
		mFieldCamera->mTransform->loc->x = mPlayerCart->mTransform->loc->x + 1;
		mFieldCamera->mTransform->loc->y = - 15;
		mFieldCamera->mTransform->loc->z = 4;
		mFieldCamera->mTransform->rot->z = 90;
		mFieldCamera->mTransform->rot->y = 10;
		sio2TransformBindMatrix(mFieldCamera->mTransform);
		mCurrentCamera = mFieldCamera;
		[mCurrentCamera calculatePosition];
	}
	
	
	
	mLastTime = now;	
}
- (void) render {
	[self update];
	[mCurrentCamera applyCamera];
	[mWorld renderAll];
}
@end
