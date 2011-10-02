//
//  KnightPlayer.h
//  template
//
//  Created by Marc Schweikert on 4/12/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Player.h"
#import "Knight.h"
#import "Cart.h"

@interface KnightPlayer : Player {
@public Knight* mKnight;
@public Cart* mCart;
@public GameObject* mWorld;
}
- (id) initHealth:(float) health Knight:(Knight*) knight Cart:(Cart*) cart World:(GameObject*) world;
-(CollidableSphere*) checkForCollision:(vec3*) pos;
-(void) die:(Player*) attacker;
-(void) update:(float) timestep;
-(void) applyDamage:(float) damageAmount Attacker:(Player*) attacker Sphere:(CollidableSphere*) sphere Impulse:(vec3) impulse;
-(void) doLogic:(float) timestep;
-(vec3) getTargetPosition;
@end
