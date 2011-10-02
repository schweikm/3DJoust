//
//  CollidableSphere.h
//  template
//
//  Created by Andrew Putman on 4/10/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameObject.h"

@interface CollidableSphere : GameObject {
	@public float mRadius2;
	@public float mDurability;
}

- (id) init:(GameObject*) parent radius:(float) radius durability:(float) durability;
- (bool) checkIntersection:(vec3*) point;
@end
