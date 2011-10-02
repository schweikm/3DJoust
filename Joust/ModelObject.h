//
//  ModelObject.h
//  Joust
//
//  Created by Marc Schweikert on 3/20/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "GameObject.h"


@interface ModelObject : GameObject {
	@public SIO2object* mObject;
}

- (id) init:(GameObject*) parent model:(NSString*) name;
- (void) render;

@end
