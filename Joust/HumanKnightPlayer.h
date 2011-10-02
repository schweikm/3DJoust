//
//  HumanKnightPlayer.h
//  template
//
//  Created by Andrew Putman on 4/15/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KnightPlayer.h"

@interface HumanKnightPlayer : KnightPlayer {
	float mLanceX;
	float mLanceY;
	float mClopTimer;
	
}
- (id) initHealth:(float) health Knight:(Knight*) knight Cart:(Cart*) cart World:(GameObject*) world;
-(void) doLogic:(float) timestep;
-(void) die:(Player*) attacker;
-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse;

@end
