#import <Foundation/Foundation.h>

#import "../src/sio2/sio2.h"

void getPositionVectorFromMatrix(float matrix[], vec3* vec);
void getTransformFromMatrix(float matrix[], SIO2transform* t);
void rotateVec(vec3* vec, vec3* rot);
void moveWithOrientation(SIO2transform* transform, vec3* vec);

@interface GameObject : NSObject
{
	NSMutableArray* mGameObjectChildren;
	NSMutableArray* mGameObjectKillList;
	GameObject* mGameObjectParent;
	@public SIO2transform* mTransform;
	@public float mPositionMatrix[16];
	
	@public bool mHitGround;
	@public vec3 mVelocity;
	@public vec3 mRotationalVelocity;
	@public vec3 mAcceleration;
	@public bool mPhysicsOn;
	@public float mBoundingRadius;
	@public float mElasticity;
	@public float mMass;
}
- (id) init:(GameObject*) parent;

- (void) setGameObjectParent:(GameObject*) parent;
- (GameObject*) getGameObjectParent;
- (void) _attachGameObject:(GameObject*) child;
- (void) _detatchGameObject:(GameObject*) child;
- (void) goAway;
- (bool) updateAll:(float) timestep;
- (bool) update:(float) timestep;
- (void) applyImpulse:(vec3*) impulse;
- (void) calculatePosition;
- (void) render;
- (void) renderAll;
@end

void updatePhysics(float timestep, GameObject* go);
