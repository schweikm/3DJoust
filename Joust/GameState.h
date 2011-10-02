//
//  GameState.h
//  Joust
//
//  Created by Marc Schweikert on 3/20/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface GameState : NSObject {
@public bool mDone;
}

- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY;
- (void) processTouchX:(float) x Y:(float) y;
- (void) processAccelX:(float) x Y:(float) y Z:(float) z;
- (void) update;
- (void) render;

@end
