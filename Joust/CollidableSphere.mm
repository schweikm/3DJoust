//
//  CollidableSphere.mm
//  template
//
//  Created by Andrew Putman on 4/10/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "CollidableSphere.h"


@implementation CollidableSphere
- (id) init:(GameObject*) parent radius:(float) radius durability:(float) durability {
	if(self = [super init:parent]) {
		mRadius2 = radius * radius;
		mDurability = durability;
	}
	return self;
}

- (bool) checkIntersection:(vec3*) point {
	vec3 ourPos;
	[self calculatePosition];
	getPositionVectorFromMatrix(mPositionMatrix, &ourPos);
	ourPos.x -= point->x;
	ourPos.y -= point->y;
	ourPos.z -= point->z;
	float distance2 = ourPos.x*ourPos.x + ourPos.y*ourPos.y +ourPos.z*ourPos.z;
	return distance2 < mRadius2;
}

@end
