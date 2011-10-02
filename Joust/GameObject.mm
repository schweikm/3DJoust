#import "GameObject.h"
#include <math.h>

void printMatrix(float matrix[]) {
	printf("[%f\t%f\t%f\t%f]\n", matrix[0], matrix[4], matrix[8], matrix[12]); 
	printf("[%f\t%f\t%f\t%f]\n", matrix[1], matrix[5], matrix[9], matrix[13]); 
	printf("[%f\t%f\t%f\t%f]\n", matrix[2], matrix[6], matrix[10], matrix[14]); 
	printf("[%f\t%f\t%f\t%f]\n", matrix[3], matrix[7], matrix[11], matrix[15]); 
	
}

void getPositionVectorFromMatrix(float matrix[], vec3* vec) {
	vec->x = matrix[12];
	vec->y = matrix[13];
	vec->z = matrix[14];
}

void getInverseRTMatrix(float mIn[], float* mOut) {
	// rotatation matrix transverse
	mOut[0] = mIn[0];
	mOut[5] = mIn[5];
	mOut[10] = mIn[10];
	mOut[1] = mIn[4];
	mOut[2] = mIn[8];
	mOut[6] = mIn[9];
	mOut[4] = mIn[1];
	mOut[8] = mIn[2];
	mOut[9] = mIn[6];

	// negate and rotate translation

	float x = -mIn[12];
	float y = -mIn[13];
	float z = -mIn[14];

	mOut[12] = x * mOut[0] + y * mOut[4] + z * mOut[8];
	mOut[13] = x * mOut[1] + y * mOut[5] + z * mOut[9];
	mOut[14] = x * mOut[2] + y * mOut[6] + z * mOut[10];
	
	mOut[3] = mIn[3];
	mOut[7] = mIn[7];
	mOut[11] = mIn[11];
	mOut[15] = mIn[15];
}

void getTransformFromMatrix(float matrix[], SIO2transform* t) {
#define R11 matrix[0]
#define R21 matrix[1]
#define R31 matrix[2]
#define R12 matrix[4]
#define R22 matrix[5]
#define R32 matrix[6]
#define R13 matrix[8]
#define R23 matrix[9]
#define R33 matrix[10]
#define PI_OVER_2 1.57079632679489661923f
	float r31abs = fabs(R31);
	float theta, omega, phi;
	if(r31abs < 0.999999) {
		theta = -asin(R31);
		float cosTheta = cos(theta);
		omega = atan2(R32/cosTheta, R33/cosTheta);
		phi = atan2(R21/cosTheta, R11/cosTheta);
	} else {
		phi = 0;
		float d = atan2(R12, R13);
		if(R31<= -0.999999) {
			theta = PI_OVER_2;
			omega = phi + d;
		} else {
			theta = -PI_OVER_2;
			omega = -phi + d;
		}
	}
	t->rot->x = omega * SIO2_RAD_TO_DEG;
	t->rot->y = theta * SIO2_RAD_TO_DEG;
	t->rot->z = phi * SIO2_RAD_TO_DEG;
	t->loc->x = matrix[12];
	t->loc->y = matrix[13];
	t->loc->z = matrix[14];
}

void rotateVec(vec3* vec, vec3* rot) {
	float x = vec->x;
	float y = vec->y;
	float z = vec->z;
	
	float xRot = rot->x * SIO2_DEG_TO_RAD;
	float yRot = rot->y * SIO2_DEG_TO_RAD;
	float zRot = rot->z * SIO2_DEG_TO_RAD;
	
	// rotate x axis
	float xPrime = x;
	float yPrime = y * cos(xRot) - z * sin(xRot);
	float zPrime = y * sin(xRot) + z * cos(xRot);
	
	// rotate y axis
	x = zPrime * sin(yRot) + xPrime * cos(yRot);
	y = yPrime;
	z = zPrime * cos(yRot) - xPrime * sin(yRot);
	
	// rotate z axis
	xPrime = x * cos(zRot) - y * sin(zRot);
	yPrime = x * sin(zRot) + y * cos(zRot);
	zPrime = z;
	
	
	vec->x = xPrime;
	vec->y = yPrime;
	vec->z = zPrime;
}

void moveWithOrientation(SIO2transform* transform, vec3* vec) {
	vec3 delta;
	delta.x = vec->x;
	delta.y = vec->y;
	delta.z = vec->z;

	rotateVec(&delta, transform->rot);
	
	transform->loc->x += delta.x;
	transform->loc->y += delta.y;
	transform->loc->z += delta.z;	
}

void updatePhysics(float timestep, GameObject* go) {
	go->mVelocity.x += go->mAcceleration.x * timestep;
	go->mVelocity.y += go->mAcceleration.y * timestep;
	go->mVelocity.z += go->mAcceleration.z * timestep;

	go->mTransform->loc->x += go->mVelocity.x * timestep;
	go->mTransform->loc->y += go->mVelocity.y * timestep;
	go->mTransform->loc->z += go->mVelocity.z * timestep;

	if(go->mTransform->loc->z - go->mBoundingRadius < 0) {
		go->mTransform->loc->z = go->mBoundingRadius;
		go->mVelocity.x *= go->mElasticity;
		go->mVelocity.y *= go->mElasticity;
		go->mVelocity.z = go->mElasticity * -go->mVelocity.z;
		if(fabs(go->mVelocity.z) > 0.5) {
			go->mHitGround = true;
		}
		go->mRotationalVelocity.x *= go->mElasticity;
		go->mRotationalVelocity.y *= go->mElasticity;
		go->mRotationalVelocity.z *= go->mElasticity;
	}
	
	go->mTransform->rot->x += go->mRotationalVelocity.x * SIO2_RAD_TO_DEG * timestep;
	go->mTransform->rot->y += go->mRotationalVelocity.y * SIO2_RAD_TO_DEG * timestep;
	go->mTransform->rot->z += go->mRotationalVelocity.z * SIO2_RAD_TO_DEG * timestep;
	sio2TransformBindMatrix(go->mTransform);
}


@implementation GameObject

- (id) init {
    if (self = [super init]) {
		mGameObjectChildren = [[NSMutableArray alloc] init];
		mGameObjectKillList = [[NSMutableArray alloc] init];

		mGameObjectParent = nil;
		mTransform = sio2TransformInit();
		sio2TransformBindMatrix(mTransform);
		[self setGameObjectParent:nil];
	}
	mHitGround = false;
	mBoundingRadius = 0.0;
	mElasticity = 0.2;
	mMass = 100;
	mTransform->loc->x = 
	mTransform->loc->y = 
	mTransform->loc->z = 
	mTransform->rot->x = 
	mTransform->rot->y = 
	mTransform->rot->z = 0;

	mPhysicsOn = false;
	mVelocity.x = mVelocity.y = mVelocity.z = 0;
	mRotationalVelocity.x = mRotationalVelocity.y = mRotationalVelocity.z = 0;
	mAcceleration.x = mAcceleration.y = mAcceleration.z = 0;
	
	mAcceleration.z = -9.8;
	return self;
}

- (id) init:(GameObject*) parent {
    if (self = [self init]) {
		[self setGameObjectParent:parent];
		mTransform->loc->x = 
		mTransform->loc->y = 
		mTransform->loc->z = 
		mTransform->rot->x = 
		mTransform->rot->y = 
		mTransform->rot->z = 0;		
	}
	return self;
}

- (void) dealloc {
	// these should be empty due to reference counting
	[mGameObjectChildren release];
	[mGameObjectKillList release];

	// this should be impossible due to reference counting
	if(mGameObjectParent) {
		[mGameObjectParent release];
	}
	sio2TransformFree(mTransform);
	[super dealloc];
}

- (void) calculatePosition {
	// The absolute position is calculated by using OpenGL to apply the parent's transform
	// And then our own local transform.
//	return;
	glPushMatrix();
	{	
		glLoadIdentity();
		if(mGameObjectParent) {
			// render our parent's position from the identity
			glMultMatrixf(mGameObjectParent->mPositionMatrix);
		}
		// render our position
//		sio2TransformApply(mTransform);
		glMultMatrixf( &mTransform->mat[ 0 ] );
		// extract our position in the world
		glGetFloatv( GL_MODELVIEW_MATRIX, &mPositionMatrix[0] );
		// TODO figure out what information we need and extract it from mPositionMatrix
	}
	glPopMatrix();
	
/*	NSEnumerator* i = [mGameObjectChildren objectEnumerator];
	GameObject* obj;
	while(obj = [i nextObject]) {
		[obj calculatePosition];
	}
*/
}

- (void) setGameObjectParent:(GameObject*) parent {
	[self calculatePosition];
	if(mGameObjectParent) {
		[mGameObjectParent _detatchGameObject:self];
		[mGameObjectParent release];
	}
//	printf("Self: %f, %f, %f\n", mPositionMatrix[12],mPositionMatrix[13],mPositionMatrix[14]); 

	mGameObjectParent = parent;
	if(mGameObjectParent) {
		[mGameObjectParent retain];
		[mGameObjectParent _attachGameObject:self];
		[mGameObjectParent calculatePosition];
		float inverseParentMatrix[16];
		getInverseRTMatrix(mGameObjectParent->mPositionMatrix, inverseParentMatrix);
//		printMatrix(mGameObjectParent->mPositionMatrix);
//		printMatrix(inverseParentMatrix);
		
		
//		printf("Parent: %f, %f, %f\n", mGameObjectParent->mPositionMatrix[12],mGameObjectParent->mPositionMatrix[13],mGameObjectParent->mPositionMatrix[14]); 
		glPushMatrix();
		{
			glLoadIdentity();
			glMultMatrixf(inverseParentMatrix);
			glMultMatrixf(mPositionMatrix);

			// extract our position from the parent
			glGetFloatv( GL_MODELVIEW_MATRIX, &mPositionMatrix[0] );
//			printf("delta: %f, %f, %f\n", mPositionMatrix[12],mPositionMatrix[13],mPositionMatrix[14]); 

		}
		glPopMatrix();
	}
	getTransformFromMatrix(mPositionMatrix, mTransform);
	sio2TransformBindMatrix(mTransform);

	[self calculatePosition];
}
- (GameObject*) getGameObjectParent {
	return mGameObjectParent;
}


// Objects should never call goAway on themselves. Objects should only call goAway on their children.
// Objects should NEVER EVER call goAway on their parent.
// If an object wants to delete itself, it should return false in the update function.
- (void) goAway {
	// The only way for the object to go away is to lose all its references. First, get rid of all the children. Then, detatch from the parent.
	// mGameObjectChildren should shrink as its children are deleted. Therefore, instead of enumerating, just keep getting rid of the front child until they are all gone.
	NSEnumerator* i = [mGameObjectChildren objectEnumerator];
	GameObject* obj;
	while(obj = [i nextObject]) {
		[obj goAway];
		
		// the iterator is invalidated when we modified the collection, 
		// so let's get a new one
		i = [mGameObjectChildren objectEnumerator];
	}

	[self setGameObjectParent:nil];
	[self release];
}


- (void) _attachGameObject: (GameObject*) child {
	[mGameObjectChildren addObject:child];
}

- (void) _detatchGameObject: (GameObject*) child {
	[mGameObjectChildren removeObject:child];
}

- (bool) updateAll:(float) timestep {
	bool ret = [self update:timestep];
	
	if(mPhysicsOn) {
		updatePhysics(timestep, self);
	}	
	
	[self calculatePosition];

	if(ret) {
		NSMutableArray* children = [mGameObjectChildren copy];
		
		NSEnumerator* i = [children objectEnumerator];
		GameObject* obj;
		// update all the children. If a child returns false, add it to a kill list. Kill the object after all the updates.
		while(obj = [i nextObject]) {
			if(![obj updateAll:timestep]) {
				[mGameObjectKillList addObject:obj];
			}
		}
	
		// get rid of any finished objects
		if([mGameObjectKillList count] > 0) {
			NSEnumerator* j = [mGameObjectKillList objectEnumerator];
			GameObject* obj2;
			while(obj2 = [j nextObject]) {
				[obj2 goAway];
			}
			[mGameObjectKillList removeAllObjects];
		}
	}
	return ret;
}

- (bool) update:(float) timestep {
//	NSLog([NSString stringWithFormat:@"%f\n", timestep]);
	return true;
}

- (void) renderAll {
	glPushMatrix();
	{	
//		sio2TransformApply(mTransform);
		glMultMatrixf( &mTransform->mat[ 0 ] );
		[self render];
		NSEnumerator* i = [mGameObjectChildren objectEnumerator];
		GameObject* obj;
		while(obj = [i nextObject]) {
			[obj renderAll];
		}
	}
	glPopMatrix();
}

- (void)render {
//	printf("GameObject Rendered!\n");
}

- (void) applyImpulse:(vec3*) impulse {
	mVelocity.x += impulse->x / mMass;
	mVelocity.y += impulse->y / mMass;
	mVelocity.z += impulse->z / mMass;
}


@end
