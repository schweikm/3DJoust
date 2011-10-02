//
//  KnightPlayer.mm
//  template
//
//  Created by Marc Schweikert on 4/12/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "KnightPlayer.h"
#import "Utilities.h"

@implementation KnightPlayer

- (id) initHealth:(float) health Knight:(Knight*) knight Cart:(Cart*) cart World:(GameObject*) world {
	if( self = [super initHealth:health]) {
		mKnight = knight;
		mCart = cart;
		mWorld = world;
	}
	return self;
}
-(CollidableSphere*) checkForCollision:(vec3*) pos {
	CollidableSphere* collision = [mKnight checkForCollision:pos];
	return collision;
}
-(void) die:(Player*) attacker {
	mHealth = 0.0;
	[mCart detachKnight];
}

-(void) update:(float) timestep {
	[self doLogic:timestep];
	if(mKnight->mLanceBroken == false) {
		vec3 tip = [mKnight getLanceTip];
		NSEnumerator* i = [mOpponents objectEnumerator];
		Player* opponent;
		while(opponent = [i nextObject]) {
			CollidableSphere* collision = [opponent checkForCollision:&tip];

//			printf("%p\n", collision);
			if(collision != nil) {
				// we have a collision with an opponent
//				float damageMultiplier = mCart->mCartVelocity / 4.0;
				vec3 impulse;
				impulse.x = mCart->mCartVelocity * timestep * mKnight->mMass * 50;
				impulse.y = 0;
				impulse.z = rand()%3000 * timestep;
				Utilities* util = [[Utilities alloc] init];
				[util playSound:@"snap"];
				[util release];
				rotateVec(&impulse, mCart->mTransform->rot);
				mKnight->mLanceBroken = true;

				if(rand()%3 == 0) {
					[mKnight->mLanceTip setGameObjectParent:collision];
				} else if (rand()%2 == 0) {
					[mKnight->mLanceTip setGameObjectParent:mWorld];
					mKnight->mLanceTip->mAcceleration.z = -9.8;
					mKnight->mLanceTip->mPhysicsOn = true;
				}
//				[opponent applyDamage:damageMultiplier * (1.0 - collision->mDurability) Attacker:self Sphere:collision Impulse:impulse];
				[opponent applyDamage:(1.0 - collision->mDurability) Attacker:self Sphere:collision Impulse:impulse];
			}
		}
	}
}
-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse {
	mHealth -= damageAmount;
	if(mHealth <= 0) {
		[self die:attacker];
	}
	if(sphere == mKnight->mLArmSphere) {
		[mKnight->mLeftArm setGameObjectParent:mWorld];
		[mKnight->mLeftArm applyImpulse: &impulse];
		mKnight->mLeftArm->mPhysicsOn = true;
		Utilities* util = [[Utilities alloc] init];
		[util playSound:@"wound"];
		[util release];
		
	}
	if(sphere == mKnight->mRArmSphere) {
		[mKnight->mRightArm setGameObjectParent:mWorld];
		[mKnight->mRightArm applyImpulse: &impulse];
		mKnight->mRightArm->mPhysicsOn = true;
		Utilities* util = [[Utilities alloc] init];
		[util playSound:@"scratch"];
		[util release];
	}

	if(sphere == mKnight->mHeadSphere) {
		[mKnight->mHead setGameObjectParent:mWorld];
//		[mKnight->mHead setGameObjectParent:mKnight->mLanceTippyTip];
		[mKnight->mHead applyImpulse: &impulse];
		mKnight->mHead->mPhysicsOn = true;
		Utilities* util = [[Utilities alloc] init];
		[util playSound:@"headshot"];
		[util release];
		
	
	}
	
	
	mKnight->mRotationalVelocity.y = rand()%10 * -0.5;
	mKnight->mRotationalVelocity.x = rand()%10 * 0.1;
	mKnight->mRotationalVelocity.z = rand()%10 * -0.1;
	[mKnight applyImpulse:&impulse];
}
-(void) doLogic:(float) timestep {
	
}
-(vec3) getTargetPosition {
	[mKnight calculatePosition];
	vec3 pos;
	getPositionVectorFromMatrix(mKnight->mPositionMatrix, &pos);
	return pos;
}
@end
