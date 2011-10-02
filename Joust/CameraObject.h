//
//  CameraObject.h
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameObject.h"


@interface CameraObject : GameObject {
//	@public SIO2camera* mSIO2camera;
	@public GameObject* mUpObject;
	@public GameObject* mForwardObject;
	
}

- (void) applyCamera;

@end
