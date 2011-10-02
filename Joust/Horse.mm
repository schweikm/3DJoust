//
//  Horse.mm
//  template
//
//  Created by Andrew Putman on 4/5/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "Horse.h"


@implementation Horse

#define SPRING_CONSTANT_X 10000.0
#define SPRING_CONSTANT_Y 2000.0
#define SPRING_CONSTANT_Z 2000.0
#define SPRING_DAMP_X 0.9
#define SPRING_DAMP_Y 0.1
#define SPRING_DAMP_Z 0.1

#define HORSE_MASS 200


-(id) init: (GameObject*) parent type:(NSString*) horseType{
	//if(self = [super init: parent model:@"dark_horse_ob"]) {
	if( self = [super init: parent model:[NSString stringWithFormat:@"%@_horse_ob", horseType]]) {
		mSpringPos.x = mSpringPos.x = mSpringPos.z = 0.0;
		mSpringVel.x = mSpringVel.x = mSpringVel.z = 0.0;
	}
	return self;
}

-(bool) update:(float) timestep {
	vec3 springDeltaVelocity;
	springDeltaVelocity.x = -SPRING_CONSTANT_X * mSpringPos.x * timestep / HORSE_MASS - SPRING_DAMP_X * mSpringVel.x * timestep;
	springDeltaVelocity.y = -SPRING_CONSTANT_Y * mSpringPos.y * timestep / HORSE_MASS - SPRING_DAMP_Y * mSpringVel.y * timestep;
	springDeltaVelocity.z = -SPRING_CONSTANT_Z * mSpringPos.z * timestep / HORSE_MASS - SPRING_DAMP_Z * mSpringVel.z * timestep;
	sio2Vec3Add(&springDeltaVelocity, &mSpringVel, &mSpringVel);

	mSpringPos.x += mSpringVel.x * timestep;
	mSpringPos.y += mSpringVel.y * timestep;
	mSpringPos.z += mSpringVel.z * timestep;
	
	mTransform->rot->x = mSpringPos.x * SIO2_RAD_TO_DEG;
	mTransform->rot->y = mSpringPos.y * SIO2_RAD_TO_DEG;
	mTransform->rot->z = mSpringPos.z * SIO2_RAD_TO_DEG;
	sio2TransformBindMatrix(mTransform);
	return true;
}

-(void) applyHorseImpulse:(vec3*) impulse {
	vec3 springDeltaVelocity;
	springDeltaVelocity.x = impulse->y / HORSE_MASS;
	springDeltaVelocity.y = -impulse->x / HORSE_MASS;
	springDeltaVelocity.z = 0.0;
	sio2Vec3Add(&springDeltaVelocity, &mSpringVel, &mSpringVel);
}

@end
