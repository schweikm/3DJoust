//
//  SpinningHead.mm
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "SpinningHead.h"


@implementation SpinningHead

- (id) init:(GameObject*) parent {
	if(self = [super init:parent model:@"Suzanne"]) {

	}
	return self;
}

- (bool) update:(float) timestep {
	mTransform->rot->z += 3.14159 * 2 * timestep;
	sio2TransformBindMatrix(mTransform);
	return true;
}

@end
