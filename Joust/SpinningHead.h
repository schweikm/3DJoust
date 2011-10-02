//
//  SpinningHead.h
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ModelObject.h"

@interface SpinningHead : ModelObject {

}
- (id) init:(GameObject*) parent;
- (bool) update:(float) timestep;
@end
