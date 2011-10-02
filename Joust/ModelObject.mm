//
//  ModelObject.m
//  Joust
//
//  Created by Marc Schweikert on 3/20/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "ModelObject.h"


@implementation ModelObject

- (id) init:(GameObject*) parent model:(NSString*) name {
	if(self = [super init:parent]) {
		mObject = (SIO2object*)sio2ResourceGet(sio2->_SIO2resource,
											   SIO2_OBJECT, 
											   (char *) [[NSString stringWithFormat:@"object/%@", name] 
												          cStringUsingEncoding:NSASCIIStringEncoding]);
	}
	return self;
}

- (void) render {
//	NSLog(@"rendered!");
	
//	SIO2camera *_SIO2camera = (SIO2camera*)sio2ResourceGet(sio2->_SIO2resource,
//														   SIO2_CAMERA,
//														   "camera/Camera");
	sio2ObjectRender(mObject,
					 sio2->_SIO2window,
//					 _SIO2camera,
					 nil,
					 SIO2_RENDER_NO_MATERIAL,
					 !SIO2_RENDER_NO_MATRIX);
}

@end
