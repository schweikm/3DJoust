//
//  CameraObject.mm
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "CameraObject.h"
#include <OpenGLES/EAGL.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

@implementation CameraObject
- (id) init {
    if (self = [super init]) {
		mUpObject = [[GameObject alloc] init:self];
		mForwardObject = [[GameObject alloc] init:self];
		mUpObject->mTransform->loc->z += 1.0f;
		mForwardObject->mTransform->loc->x += 1.0f;
		sio2TransformBindMatrix(mUpObject->mTransform);
		sio2TransformBindMatrix(mForwardObject->mTransform);
	}
	return self;
}

- (void) applyCamera {
	vec3 pos;
	vec3 upPos;
	vec3 forwardPos;
	vec3 up;
	[self calculatePosition];
	[mUpObject calculatePosition];
	[mForwardObject calculatePosition];
	
	getPositionVectorFromMatrix(mPositionMatrix, &pos);
	getPositionVectorFromMatrix(mUpObject->mPositionMatrix, &upPos);
	getPositionVectorFromMatrix(mForwardObject->mPositionMatrix, &forwardPos);
	
	sio2Vec3Diff(&upPos, &pos, &up);
	sio2LookAt(&pos, &forwardPos, &up );
}

@end
