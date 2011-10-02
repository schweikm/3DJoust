//
//  Player.h
//  template
//
//  Created by Marc Schweikert on 4/12/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CollidableSphere.h"

@interface Player : NSObject {
	@public float mHealth;
	@public vec2 mTouch;
	@public vec3 mAccel;
	NSMutableArray* mOpponents;
}
- (id) initHealth:(float) health;
- (void) dealloc;
- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY;
- (void) processTouchX:(float) x Y:(float) y;
- (void) processAccelX:(float) x Y:(float) y Z:(float) z;
-(CollidableSphere*) checkForCollision:(vec3*) pos;
-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse;
-(void) die:(Player*) attacker;
-(void) update:(float) timestep;
-(void) addOpponent:(Player*) opponent;
-(vec3) getTargetPosition;
@end
