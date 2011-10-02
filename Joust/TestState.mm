//
//  TestState.m
//  Joust
//
//  Created by Marc Schweikert on 3/20/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "TestState.h"
#import "SpinningHead.h"
#import "Utilities.h"
#import "Knight.h"
#import "Cart.h"

#include <sys/time.h>
#include <time.h>

@implementation TestState

- (id) init {
	if(self = [super init]) {
		mWorld = [[GameObject alloc] init];
		mCamera = [[CameraObject alloc] init];
		mCamera->mTransform->loc->x = -20;
		mCamera->mTransform->loc->z = 2;
		sio2TransformBindMatrix(mCamera->mTransform);

		zCalibration = -10;
//		mMonkeyHead = [[ModelObject alloc] init: mWorld model:@"Suzanne"];

		/*
		for(int y=-30; y<=30; y += 10) {
			for (int x=-30; x<=30; x += 10) {
				if(!(fabs(x) < 10 && fabs(y) < 10)) {
					GameObject* bar = [[SpinningHead alloc] init: mWorld];
					bar->mTransform->loc->x = x;
					bar->mTransform->loc->y = y;
					sio2TransformBindMatrix(bar->mTransform);
				}
			}
		}
		*/
		
		mStad  = [[ModelObject alloc] init: mWorld model:@"stad_ob"];
		mRail0 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mRail1 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
//		mRail2 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
//		mRail3 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mRail4 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
//		mRail5 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
//		mRail6 = [[ModelObject alloc] init: mWorld model:@"rail_ob"];
		mStad->mTransform->loc->z += -3.4;
		sio2TransformBindMatrix(mStad->mTransform);
		mRail0->mTransform->loc->z += -1.0;
		mRail1->mTransform->loc->z += -1.0;
//		mRail2->mTransform->loc->z += -1.0;
//		mRail3->mTransform->loc->z += -1.0;
		mRail4->mTransform->loc->z += -1.0;
//		mRail5->mTransform->loc->z += -1.0;
//		mRail6->mTransform->loc->z += -1.0;
		mRail1->mTransform->loc->x += 20;
//		mRail2->mTransform->loc->x += 40;
//		mRail3->mTransform->loc->x += 60;
		mRail4->mTransform->loc->x -= 20;
//		mRail5->mTransform->loc->x -= 40;
//		mRail6->mTransform->loc->x -= 60;
		sio2TransformBindMatrix(mRail0->mTransform);
		sio2TransformBindMatrix(mRail1->mTransform);
//		sio2TransformBindMatrix(mRail2->mTransform);
//		sio2TransformBindMatrix(mRail3->mTransform);
		sio2TransformBindMatrix(mRail4->mTransform);
//		sio2TransformBindMatrix(mRail5->mTransform);
//		sio2TransformBindMatrix(mRail6->mTransform);

		mKnight1 = [[Knight alloc] init:mWorld type:@"light"];
		mCart1 = [[Cart alloc] init:mWorld type:@"light"];
		mCart1->mCartAcceleration = 3.0;
//		[mCart1 setVelocity:5.0];
		[mCart1 attachKnight:mKnight1];
		mCart1->mTransform->loc->y -= 0.75;
		mCart1->mTransform->loc->x -= 40.0;
		sio2TransformBindMatrix(mCart1->mTransform);
		
		mKnight2 = [[Knight alloc] init:mWorld type:@"light"];
		mCart2 = [[Cart alloc] init:mWorld type:@"dark"];
		mCart2->mCartAcceleration = 3.0;
		//		[mCart2 setVelocity:5.0];
		[mCart2 attachKnight:mKnight2];
		mCart2->mTransform->loc->y += 0.75;
		mCart2->mTransform->loc->x += 40.0;
		mCart2->mTransform->rot->z += 180;
		sio2TransformBindMatrix(mCart2->mTransform);
		
		
		[mCamera setGameObjectParent:mKnight1->mHead];
		mCamera->mTransform->loc->x = -10.0;
		mCamera->mTransform->loc->z = 0.2;
		mCamera->mTransform->loc->x = 0.5;
		mCamera->mTransform->loc->z = 0.0;
//		mCamera->mTransform->rot->z = 180;
		sio2TransformBindMatrix(mCamera->mTransform);
		
//		ModelObject* foo = [[ModelObject alloc] init: mMonkeyHead model:@"Suzanne"];
//		foo->mTransform->loc->z = 3.0;
//		sio2TransformBindMatrix(foo->mTransform);
		mLastTime = getTimeNow();
		
		mPlayer1 = [[KnightPlayer alloc] initHealth:0.1 Knight:mKnight1 Cart:mCart1 World:mWorld];
		mPlayer2 = [[KnightPlayer alloc] initHealth:0.1 Knight:mKnight2 Cart:mCart2 World:mWorld];	
		
		[mPlayer1 addOpponent:mPlayer2];
		[mPlayer2 addOpponent:mPlayer1];
		
	}
	return self;
}

- (void) dealloc {
	[mWorld goAway];
	[mCamera goAway];
	[super dealloc];
}

- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY {
//	NSLog([NSString stringWithFormat:@"%f", deltaX]);

//	mCamera->mTransform->rot->z += deltaX/10;
//	mCamera->mTransform->rot->y += deltaY/10;
//	sio2TransformBindMatrix(mCamera->mTransform);

	
//	sio2Rotate3D(mCamera->mTransform->rot, deltaX, 0, 0, mCamera->mTransform->rot);

	[mPlayer1 processTouchMoveX:deltaX Y:deltaY];
	[mPlayer2 processTouchMoveX:deltaX Y:deltaY];
	
	
	
}

- (void) processTouchX:(float) x Y:(float) y {

	x = 2 * x / 480 - 1.0;
	y = 2 * y / 320 - 1.0;

	[mPlayer1 processTouchX:x Y:y];
	[mPlayer2 processTouchX:x Y:y];

	
	[mKnight1 setLanceZAxis:(x-0.7)*4 YAxis:y*2];
	[mKnight2 setLanceZAxis:x YAxis:y];
//	[mKnight1 setLean:-x];
	
//	if(y > 0.9) {
//		[mCart2 detachKnight];
//	}
}


- (void) processAccelX:(float) x Y:(float) y Z:(float) z {
	[mPlayer1 processAccelX:x Y:y Z:z];
	[mPlayer2 processAccelX:x Y:y Z:z];
//	printf("%f\n", z);
	[mKnight1 setLean:y*3 Forward: 0];
}


- (void) update {
	float now = getTimeNow();
	float delta = now - mLastTime;

	[mPlayer1 update:delta];
	[mPlayer2 update:delta];
	[mWorld updateAll:delta];
	mLastTime = now;
}

- (void) render {
	[self update];
	[mCamera applyCamera];
	[mWorld renderAll];
}

@end
