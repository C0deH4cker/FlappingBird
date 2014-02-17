//
//  Bird.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_BIRD_H_
#define _FB_BIRD_H_

#include <sge.h>

using namespace sge;

class Bird {
public:
	Bird(const Texture2D* sprites, float groundHeight);
	
	void update(double deltaTime);
	void draw(double deltaTime);
	
	void flap();
	void die();
	void reset();
	void pause();
	void resume();
	
	bool isDead() const;
	
	const Rectangle& getBounds() const;
	
private:
	const static float flapSpeed, maxSpeed, gravity;
	const static double defaultFps;
	double fps, extra;
	bool dead, started, paused, onGround;
	Vector2 startingPos;
	Rectangle bounds;
	float ground;
	float speed;
	int curFrame;
	Timer timer, wingTimer;
	Sprite frames[3];
	
	float getRotation() const;
	void setFlapsPerSec(double fps);
	int getFrame();
};


#endif /* _FB_BIRD_H_ */
