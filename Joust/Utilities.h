//
//  Utilities.h
//  template
//
//  Created by Marc Schweikert on 3/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>

float getTimeNow(void);


@interface Utilities : NSObject {

}

- (void) playSound:(NSString*) soundID;

@end
