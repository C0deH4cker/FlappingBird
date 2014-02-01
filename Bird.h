//
//  Bird.h
//  FlappyBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_BIRD_H_
#define _FB_BIRD_H_

#include <Rectangle.h>
#include <Content.h>
#include <Texture2D.h>

using namespace sge;

class Bird {
public:
	Bird(const Content& content, float groundHeight);
	~Bird();
	
	void update(double deltaTime);
	void draw(double deltaTime);
	
	void flap();
	void die();
	void reset();
	
	bool isDead() const;
	
	const Rectangle& getBounds() const;
	
private:
	const static float flapSpeed, maxSpeed, gravity;
	bool dead;
	Vector2 startingPos;
	Rectangle bounds;
	float ground;
	float speed;
	Texture2D* texture;
};


#endif /* _FB_BIRD_H_ */
