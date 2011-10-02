//
//  Knight.h
//  template
//
//  Created by Andrew Putman on 3/30/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ModelObject.h"
#import "Horse.h"
#import "CollidableSphere.h"

@interface Knight : ModelObject {
	@public ModelObject* mHead;
	ModelObject* mLeftArm;
	ModelObject* mRightArm;
	ModelObject* mLeftLeg;
	ModelObject* mRightLeg;
	ModelObject* mLanceHandle;
	ModelObject* mLanceTip;
	GameObject* mLanceTippyTip;

	
	CollidableSphere* mHeadSphere;
	CollidableSphere* mBodySphere;
	@public CollidableSphere* mLArmSphere;
	@public CollidableSphere* mRArmSphere;
	@public CollidableSphere* mLLegSphere;
	@public CollidableSphere* mRLegSphere;
	
	float mLastLanceZ;
	float mLastLanceY;
	float mLean;
	float mForwardLean;
	float mDropCounter;
	
	@public Horse* mHorse;
	@public bool mLanceBroken;	
}
- (id) init:(GameObject*) parent type:(NSString*) knightType;//constructor, give it parent node
- (bool) update:(float) timestep;
- (void) setLanceZAxis:(float) z YAxis:(float) y; 
- (void) setLean:(float) amount Forward:(float) forwardAmount;
- (void) attachHorse:(Horse*) horse;
- (void) dismount;
- (vec3) getLanceTip;
-(CollidableSphere*) checkForCollision:(vec3*) pos;
-(void) resetForMatch;

@end
