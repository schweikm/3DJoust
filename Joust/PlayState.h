//
//  PlayState.h
//  template
//
//  Created by Andrew Putman on 4/13/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameState.h"
#import "GameObject.h"
#import "CameraObject.h"
#import "Knight.h"
#import "Cart.h"
#import "KnightPlayer.h"


@interface PlayState : GameState {
@private GameObject* mWorld;
	CameraObject* mCurrentCamera;
@private CameraObject* mPlayerCamera;
@private CameraObject* mFieldCamera;
@private Knight* mPlayerKnight;
@private Knight* mOpponentKnight;
@private GameObject* mStadium;
@private GameObject* mRail0;
@private GameObject* mRail1;
@private GameObject* mRail2;
	
@private Cart* mPlayerCart;
@private Cart* mOpponentCart;
	
Player* mHumanPlayer;
Player* mComputerPlayer;
float mLastTime;
}
- (id) init;
- (void) dealloc;
- (void) resetForMatch;
- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY;
- (void) processTouchX:(float) x Y:(float) y;
- (void) processAccelX:(float) x Y:(float) y Z:(float) z;
- (void) update;
- (void) render;
@end
