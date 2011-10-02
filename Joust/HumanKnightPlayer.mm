//
//  HumanKnightPlayer.mm
//  template
//
//  Created by Andrew Putman on 4/15/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "HumanKnightPlayer.h"
#import "Utilities.h"

@implementation HumanKnightPlayer
- (id) initHealth:(float) health Knight:(Knight*) knight Cart:(Cart*) cart World:(GameObject*) world {
	if( self = [super initHealth:health Knight:knight Cart:cart World:world]) {
		mLanceX = 0.0;
		mLanceY = 0.0;
		mClopTimer = 1.0;
	}
	return self;
}

-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse {
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
	[super applyDamage:damageAmount Attacker:attacker Sphere:sphere Impulse:impulse];
}
-(void) doLogic:(float) timestep {
	[mKnight setLanceZAxis:(mTouch.x-0.7)*4 YAxis:mTouch.y*2];
	[mKnight setLean:mAccel.y*3 Forward: 0];

	mClopTimer -= timestep * mCart->mCartVelocity/3;

	if(mClopTimer < 0) {
		mClopTimer += 1.0;
		Utilities* util = [[Utilities alloc] init];
		[util playSound:@"trot"];
		[util release];
		
	}
	if(mKnight->mHitGround) {
		mKnight->mHitGround = false;
		AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
	}
	
}

-(void) die:(Player*) attacker {
	Utilities* util = [[Utilities alloc] init];
	[util playSound:@"no"];
	[util release];
	[super die:attacker];
}


@end
