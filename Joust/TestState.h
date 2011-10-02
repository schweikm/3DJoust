//
//  TestState.h
//  Joust
//
//  Created by Marc Schweikert on 3/20/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "GameState.h"
#import "GameObject.h"
#import "CameraObject.h"
#import "Knight.h"
#import "Cart.h"
#import "KnightPlayer.h"

@interface TestState : GameState {
	@private GameObject* mWorld;
	@private CameraObject* mCamera;
	@private GameObject* mMonkeyHead;
	@private Knight* mKnight1;
	@private Knight* mKnight2;
	@private Knight* mBKnight;
	@private GameObject* mStad;
	@private GameObject* mRail0;
	@private GameObject* mRail1;
	@private GameObject* mRail2;
    @private GameObject* mRail3;
    @private GameObject* mRail4;
    @private GameObject* mRail5;
	@private GameObject* mRail6;

	@private Cart* mCart1;
	@private Cart* mCart2;
	
	Player* mPlayer1;
	Player* mPlayer2;
	
	float mLastTime;
	float zCalibration;
}

- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY;
- (void) processTouchX:(float) x Y:(float) y;
- (void) processAccelX:(float) x Y:(float) y Z:(float) z;
- (void) update;
- (void) render;

@end
