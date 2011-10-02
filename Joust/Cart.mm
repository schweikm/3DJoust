//
//  Cart.mm
//  template
//
//  Created by Andrew Putman on 4/1/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "Cart.h"
#import "Utilities.h"

@implementation Cart
- (id) init: (GameObject*) parent type:(NSString*) horseType{
	if(self = [super init:parent model:@"cart_ob"]){
		mCartVelocity = 0.0;
		mCartAcceleration = 0.0;
		
		mRFWheel = [[ModelObject alloc] init:self model:@"wheel_ob"];
		mRFWheel->mTransform->loc->x += .83;
		mRFWheel->mTransform->loc->y += .6;
		//mRFWheel->mTransform->rot->z += 90;
		sio2TransformBindMatrix(mRFWheel->mTransform);
		mLFWheel = [[ModelObject alloc] init:self model:@"wheel_ob"];
		mLFWheel->mTransform->loc->x += -.83;
		mLFWheel->mTransform->loc->y += .6;
		//mLFWheel->mTransform->rot->z += 90;
		sio2TransformBindMatrix(mLFWheel->mTransform);
		mRBWheel = [[ModelObject alloc] init:self model:@"wheel_ob"];
		mRBWheel->mTransform->loc->x += .83;
		mRBWheel->mTransform->loc->y += -.6;
		//mRBWheel->mTransform->rot->z += 90;
		sio2TransformBindMatrix(mRBWheel->mTransform);
		mLBWheel = [[ModelObject alloc] init:self model:@"wheel_ob"];
		mLBWheel->mTransform->loc->x += -.83;
		mLBWheel->mTransform->loc->y += -.6;
		//mLBWheel->mTransform->rot->z += 90;
		sio2TransformBindMatrix(mLBWheel->mTransform);
		
		mHorse = [[Horse alloc] init:self type: horseType];
		mHorse->mTransform->loc->z += 1.0;
		
		vec3 impulse;
		impulse.x = 100;
		impulse.y = 0;
		impulse.z = 0;
		[mHorse applyImpulse:&impulse];
		
		mKnight = nil;
		sio2TransformBindMatrix(mHorse->mTransform);
	}
	return self;
}

- (bool) update:(float) timestep {
//	mTransform->rot->z -= 10*timestep;
	//mTransform->rot->y -= 1*timestep;
	
	vec3 delta;
	mCartVelocity += (mCartAcceleration - mCartVelocity/3) * timestep;
	delta.x = mCartVelocity * timestep;
	delta.y = delta.z = 0;
	moveWithOrientation(mTransform, &delta);
	sio2TransformBindMatrix(mTransform);

	
	if(mKnight != nil) {
		if(fabs(mHorse->mTransform->rot->x) > 60) {
			Utilities* obj = [[Utilities alloc] init];
			[obj playSound:@"whoop"];
			[obj release];
			[self detachKnight];
		}
	}
/*
	float angularDelta = mVelocity * 0.5 * timestep * SIO2_RAD_TO_DEG;
	
	mRFWheel->mTransform->rot->y += angularDelta;
	sio2TransformBindMatrix(mRFWheel->mTransform);
	mLFWheel->mTransform->rot->y += angularDelta;
	sio2TransformBindMatrix(mLFWheel->mTransform);
	mRBWheel->mTransform->rot->y += angularDelta;
	sio2TransformBindMatrix(mRBWheel->mTransform);
	mLBWheel->mTransform->rot->y += angularDelta;
	sio2TransformBindMatrix(mLBWheel->mTransform);
 */
	return true;
}

- (void) setVelocity:(float) velocity {
	mCartVelocity = velocity;
}

- (void) attachKnight: (Knight*) knight {
	assert(mKnight == nil);
	mKnight = knight;

	[self calculatePosition];
	[mKnight setGameObjectParent:mHorse];

	[mKnight attachHorse: mHorse];
	mKnight->mTransform->loc->x = 0;
	mKnight->mTransform->loc->y = 0;
	mKnight->mTransform->loc->z = 0.9;
	mKnight->mTransform->rot->x = 0;
	mKnight->mTransform->rot->y = 0;
	mKnight->mTransform->rot->z = 0;
	sio2TransformBindMatrix(mKnight->mTransform);
		
}

- (void) detachKnight {
	if(mKnight != nil) {
		[mKnight setGameObjectParent: mGameObjectParent];

		mKnight->mRotationalVelocity.x += mHorse->mSpringVel.x;
		mKnight->mRotationalVelocity.y += mHorse->mSpringVel.y;
		mKnight->mRotationalVelocity.z += mHorse->mSpringVel.z;
	
	
		vec3 deltaImpulse;
		deltaImpulse.x = mCartVelocity * mKnight->mMass;
		deltaImpulse.y = 0;
		deltaImpulse.z = 5 * mKnight->mMass;
		rotateVec(&deltaImpulse, mTransform->rot);
		rotateVec(&deltaImpulse, mHorse->mTransform->rot);
		[mKnight applyImpulse:&deltaImpulse];
		[mKnight dismount];
		mKnight = nil;
	}
}
@end
