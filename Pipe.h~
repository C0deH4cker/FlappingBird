//
//  Pipe.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_PIPE_H_
#define _FB_PIPE_H_

#include <sge.h>
#include "Bird.h"

using namespace sge;

class Pipe {
public:
	Pipe(const Vector2& pos, const Sprite* topImage, const Sprite* bottomImage);
	
	void scroll(float x);
	void draw();
	bool collides(const Bird* bird) const;
	bool didScore(const Bird* bird);
	bool offScreen() const;
	
private:
	bool scored;
	const Sprite* top;
	Rectangle topRect;
	const Sprite* bottom;
	Rectangle bottomRect;
};


#endif /* _FB_PIPE_H_ */
