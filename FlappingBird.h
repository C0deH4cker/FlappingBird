//
//  FlappingBird.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_FlappingBird_H_
#define _FB_FlappingBird_H_

#include <Game.h>
#include "Bird.h"
#include "Level.h"

using namespace sge;

class FlappingBird: public virtual Game {
public:
	Content content;
	
	FlappingBird();
	~FlappingBird();
	
	void initialize();
	void update(double deltaTime);
	void draw(double deltaTime);
	
	void charTyped(unsigned uc);
	
private:
	Level* level;
};


#endif /* _FB_FlappingBird_H_ */
