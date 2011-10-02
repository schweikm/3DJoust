//
//  Player.mm
//  template
//
//  Created by Marc Schweikert on 4/12/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "Player.h"


@implementation Player

- (id) initHealth:(float) health {
	if( self = [super init]) {
		mOpponents = [[NSMutableArray alloc] init];
		mHealth = health;
	}
	return self;
}

- (void) dealloc {
	// these should be empty due to reference counting
	[mOpponents release];
	[super dealloc];
}

- (void) processTouchMoveX:(float) deltaX Y:(float) deltaY {
	
}
- (void) processTouchX:(float) x Y:(float) y {
	mTouch.x = x;
	mTouch.y = y;
}
- (void) processAccelX:(float) x Y:(float) y Z:(float) z {
	mAccel.x = x;
	mAccel.y = y;
	mAccel.z = z;
}
-(CollidableSphere*) checkForCollision:(vec3*) pos {
	return nil;
}
-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse {
	mHealth -= damageAmount;
	if(mHealth <= 0) {
		[self die:attacker];
	}
}

-(void) die:(Player*) attacker {
}

-(void) update:(float) timestep {
	
}

-(void) addOpponent:(Player*) opponent {
	[mOpponents addObject:opponent];
}
-(vec3) getTargetPosition {
	vec3 pos;
	return pos;
}


@end
