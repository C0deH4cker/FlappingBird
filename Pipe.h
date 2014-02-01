//
//  Pipe.h
//  FlappyBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_PIPE_H_
#define _FB_PIPE_H_

#include <Vector2.h>
#include <Texture2D.h>
#include <Rectangle.h>
#include "Bird.h"

using namespace sge;

class Pipe {
public:
	Pipe(const Vector2& pos, Texture2D* topImage, Texture2D* bottomImage);
	
	void scroll(float x);
	void draw();
	bool collides(const Bird* bird) const;
	bool didScore(const Bird* bird);
	bool offScreen() const;
	
private:
	bool scored;
	Texture2D* top;
	Rectangle topRect;
	Texture2D* bottom;
	Rectangle bottomRect;
};


#endif /* _FB_PIPE_H_ */
