//
//  Knight.mm
//  template
//
//  Created by Andrew Putman on 3/30/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "Knight.h"
#import "Cart.h"

#define HEADZ 1.087
#define	BODYZ 0.903
#define R_ARMZ 0.800
#define R_ARMY -0.390
#define L_ARMZ 0.800
#define L_ARMY 0.390
#define R_LEGZ 0.362
#define R_LEGY -0.291
#define L_LEGZ 0.362
#define L_LEGY 0.291
#define LANCEHANDLEX 0.7
#define LANCEHANDLEZ -0.3

ModelObject* allocateModelHelper(GameObject* parent, NSString* type, NSString* model) {
	return [[ModelObject alloc] init:parent model: [NSString stringWithFormat:@"%@_%@", type, model]];
}


@implementation Knight
- (id) init:(GameObject*) parent type:(NSString*) knightType {
	if(self = [super init:parent model:[NSString stringWithFormat:@"%@_body_ob",knightType]]){//@"body_ob"]) {
	//if(self = [super init:parent model:@"dark_body_ob"]){//[NSString stringWithFormat:@"%@_body_ob",knightType]]){//@"body_ob"]) {
		mHorse = nil;
		mLanceBroken = false;
		mBodySphere = [[CollidableSphere alloc] init:self radius: 0.3 durability:0.8];
		mBodySphere->mTransform->loc->z = -0.27;
		sio2TransformBindMatrix(mBodySphere->mTransform);
		
	    mHead = allocateModelHelper(self, knightType, @"head_ob");
		mHead->mTransform->loc->z = (HEADZ-BODYZ);
		sio2TransformBindMatrix(mHead->mTransform);
		
		mHeadSphere = [[CollidableSphere alloc] init:mHead radius: 0.25 durability:0.3];
		sio2TransformBindMatrix(mHeadSphere->mTransform);
		
		mLeftArm = allocateModelHelper(self, knightType, @"l_arm_ob");
		mLeftArm->mTransform->loc->y = L_ARMY;
		mLeftArm->mTransform->loc->z = (L_ARMZ-BODYZ);
		sio2TransformBindMatrix(mLeftArm->mTransform);

		mLArmSphere = [[CollidableSphere alloc] init:mLeftArm radius: 0.15 durability:0.9];
		sio2TransformBindMatrix(mLArmSphere->mTransform);		
		
		mRightArm = allocateModelHelper(self, knightType, @"r_arm_ob");
		mRightArm->mTransform->loc->y = R_ARMY;
		mRightArm->mTransform->loc->z = (R_ARMZ-BODYZ);
		sio2TransformBindMatrix(mRightArm->mTransform);

		mRArmSphere = [[CollidableSphere alloc] init:mRightArm radius: 0.15 durability:0.6];
		sio2TransformBindMatrix(mRArmSphere->mTransform);		

		
		mLeftLeg = allocateModelHelper(self, knightType, @"l_leg_ob");
		mLeftLeg->mTransform->loc->y = L_LEGY;
		mLeftLeg->mTransform->loc->z = (L_LEGZ-BODYZ);
		sio2TransformBindMatrix(mLeftLeg->mTransform);
		
		mLLegSphere = [[CollidableSphere alloc] init:mLeftLeg radius: 0.15 durability:0.9];
		mLLegSphere->mTransform->loc->x = 0.08;
		mLLegSphere->mTransform->loc->y = 0.17;
		mLLegSphere->mTransform->loc->z = - 0.25;
		sio2TransformBindMatrix(mLLegSphere->mTransform);	
		
		mRightLeg = allocateModelHelper(self, knightType, @"r_leg_ob");
		mRightLeg->mTransform->loc->y = R_LEGY;
		mRightLeg->mTransform->loc->z = (R_LEGZ-BODYZ);
		sio2TransformBindMatrix(mRightLeg->mTransform);

		mRLegSphere = [[CollidableSphere alloc] init:mRightLeg radius: 0.15 durability:0.9];
		mRLegSphere->mTransform->loc->x = 0.08;
		mRLegSphere->mTransform->loc->y = -0.17;
		mRLegSphere->mTransform->loc->z = - 0.25;
		sio2TransformBindMatrix(mRLegSphere->mTransform);	

		
		mLanceHandle = allocateModelHelper(mRightArm, knightType, @"jav_han_ob");
		mLanceHandle->mTransform->loc->x = LANCEHANDLEX;
		mLanceHandle->mTransform->loc->z = LANCEHANDLEZ;
		sio2TransformBindMatrix(mLanceHandle->mTransform);
		mLanceTip    = [[ModelObject alloc] init:mLanceHandle model:@"jav_tip_ob"];
		sio2TransformBindMatrix(mLanceTip->mTransform);
//		mLanceTippyTip = [[GameObject alloc] init:mLanceTip];
		mLanceTippyTip = [[CollidableSphere alloc] init:mLanceTip radius:0.1 durability:1.0];
		mLanceTippyTip->mTransform->loc->x = 5.7;
		sio2TransformBindMatrix(mLanceTippyTip->mTransform);
		mLastLanceZ = 0;
		mLastLanceY = 0;
		mLean = 0;
		mDropCounter = 0.0;

		mBoundingRadius = 0.5;

	}
	return self;
}


-(void) resetForMatch {
	mLanceBroken = false;
	mLanceTip->mPhysicsOn = false;
	mPhysicsOn = false;
	
	mLanceTip->mVelocity.x = 0;
	mLanceTip->mVelocity.y = 0;
	mLanceTip->mVelocity.z = 0;
	
	
	[mLanceTip setGameObjectParent:mLanceHandle];
	mLanceTip->mTransform->loc->x = 0;
	mLanceTip->mTransform->loc->y = 0;
	mLanceTip->mTransform->loc->z = 0;
	mLanceTip->mTransform->rot->x = 0;
	mLanceTip->mTransform->rot->y = 0;
	mLanceTip->mTransform->rot->z = 0;
	sio2TransformBindMatrix(mLanceTip->mTransform);

	mVelocity.x = 0;
	mVelocity.y = 0;
	mVelocity.z = 0;

	mTransform->loc->x = 0;
	mTransform->loc->y = 0;
	mTransform->loc->z = 0.9;
	mTransform->rot->x = 0;
	mTransform->rot->y = 0;
	mTransform->rot->z = 0;
	sio2TransformBindMatrix(mTransform);
}


- (bool) update:(float) timestep {
	//mTransform->rot->z -= 10 * timestep;
	//sio2TransformBindMatrix(mTransform);
	
	//mHead->mTransform->rot->z += 10 * timestep;
	//sio2TransformBindMatrix(mHead->mTransform);

//	sio2TransformBindMatrix(mTransform);
//	getTransformFromMatrix(mTransform->mat, mTransform);
//	sio2TransformBindMatrix(mTransform);
	
	mDropCounter += timestep;
	/*
	if(mDropCounter > 2) {
		mDropCounter -= 2;
		[mHead calculatePosition];
		ModelObject* foo = [[ModelObject alloc] init:mLanceTippyTip model:@"dark_l_arm_ob"];
		foo->mTransform->loc->z = 0.0;
		sio2TransformBindMatrix(foo->mTransform);		
		[foo calculatePosition];
		GameObject* world = [self getGameObjectParent];
		GameObject* parent = [world getGameObjectParent];
		while(parent != nil) {
			world = parent;
			parent = [world getGameObjectParent];
		}
		[foo setGameObjectParent:world];
		foo->mPhysicsOn = true;
	}
	 */
	if(mHorse != nil) {
		vec3 impulse;
		impulse.x = -5 * mForwardLean * mMass * timestep;
		impulse.y =  -50 * mLean * mMass * timestep;
		[mHorse applyHorseImpulse: &impulse];
	}
	
	return true;
}

- (void) setLanceZAxis:(float) z YAxis:(float) y {
#define MAX_ANGLE_Y 20
#define MAX_ANGLE_Z 20
	
	float yDeg = -y * MAX_ANGLE_Y - 5;
	float zDeg = -z * MAX_ANGLE_Z + 20;
	
	mRightArm->mTransform->rot->y = yDeg;
	mRightArm->mTransform->rot->z = zDeg;
	sio2TransformBindMatrix(mRightArm->mTransform);
	
	vec3 impulse;
	impulse.y = -(z - mLastLanceZ) * 100;
	impulse.x =  -(y - mLastLanceY) * 50;
	if(mHorse != nil) {
		[mHorse applyHorseImpulse: &impulse];
	}

	mLastLanceZ = z;
	mLastLanceY = y;

}

- (void) attachHorse:(Horse*) horse {
	mHorse = horse;
}

- (void) dismount {
	mPhysicsOn = true;
	mHorse = nil;
}

- (void) setLean:(float) amount Forward:(float) forwardAmount{
	mLean = amount;
	mForwardLean = forwardAmount;
}

-(CollidableSphere*) checkForCollision:(vec3*) pos {
	if([mHeadSphere checkIntersection:pos])
		return mHeadSphere;

	if([mBodySphere checkIntersection:pos])
		return mBodySphere;

	if([mLArmSphere checkIntersection:pos])
		return mLArmSphere;
	
	if([mRArmSphere checkIntersection:pos])
		return mRArmSphere;

	if([mLLegSphere checkIntersection:pos])
		return mLLegSphere;

	if([mRLegSphere checkIntersection:pos])
		return mRLegSphere;
	
	return nil;
}

- (vec3) getLanceTip {
	vec3 tip;
	[mLanceTippyTip calculatePosition];
	getPositionVectorFromMatrix(mLanceTippyTip->mPositionMatrix, &tip);
	return tip;
}


@end
