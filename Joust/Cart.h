//
//  Cart.h
//  template
//
//  Created by Andrew Putman on 4/1/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ModelObject.h"
#import "Horse.h"
#import "Knight.h"

@interface Cart : ModelObject {
	//ModelObject* mBase; the base is the self
	ModelObject* mRFWheel;
	ModelObject* mLFWheel;
	ModelObject* mRBWheel;
	ModelObject* mLBWheel;
	
	Horse* mHorse;
	@public Knight* mKnight;
	
	@public float mCartVelocity;
	@public float mCartAcceleration;

}

- (id) init:(GameObject*) parent type:(NSString*) horseType;//constructor, give parent
- (bool) update:(float) timestep;
- (void) setVelocity:(float) velocity;
- (void) attachKnight: (Knight*) knight;
- (void) detachKnight;
@end
