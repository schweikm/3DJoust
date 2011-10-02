//
//  Horse.h
//  template
//
//  Created by Andrew Putman on 4/5/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ModelObject.h"

@interface Horse : ModelObject {
	@public vec3 mSpringPos;
	@public vec3 mSpringVel;
	
}

-(id) init:(GameObject*) parent type:(NSString*) horseType;
-(bool) update:(float) timestep;
-(void) applyHorseImpulse:(vec3*) impulse;
@end
