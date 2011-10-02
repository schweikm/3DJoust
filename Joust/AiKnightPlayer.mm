//
//  AiKnightPlayer.mm
//  template
//
//  Created by Andrew Putman on 4/15/09.
//  Copyright 2009 University of Michigan. All rights reserved.
//

#import "AiKnightPlayer.h"
#import "Utilities.h"

@implementation AiKnightPlayer
- (id) initHealth:(float) health Knight:(Knight*) knight Cart:(Cart*) cart World:(GameObject*) world {
	if( self = [super initHealth:health Knight:knight Cart:cart World:world]) {
		mLanceX = 0.0;
		mLanceY = 0.0;
	}
	return self;
}
-(void) doLogic:(float) timestep {
	NSEnumerator* i = [mOpponents objectEnumerator];
	Player* opponent;
	opponent = [i nextObject];
	vec3 target = [opponent getTargetPosition];
	
	vec3 ourPos;
	getPositionVectorFromMatrix(mKnight->mLanceTippyTip->mPositionMatrix, &ourPos);

	float xerror = target.y - ourPos.y;
	float yerror = target.z - ourPos.z - 0.06;

	if(xerror > 0) mLanceX += 0.08*timestep;
	if(xerror < 0) mLanceX -= 0.08*timestep;
	if(yerror > 0) mLanceY += 0.08*timestep;
	
	if(yerror < 0) mLanceY -= 0.08*timestep;
	if(mLanceX < -1) mLanceX = -1;
	if(mLanceX > 1) mLanceX = 1;
	if(mLanceY < -1) mLanceX = -1;
	if(mLanceY > 1) mLanceX = 1;
	
	[mKnight setLanceZAxis:mLanceX YAxis:mLanceY];

//	printf("lance: %f %f\n", xerror, yerror);
		
}

-(void) die:(Player*) attacker {
	Utilities* util = [[Utilities alloc] init];
	[util playSound:@"yea"];
	[util release];
	[super die:attacker];
}


@end
