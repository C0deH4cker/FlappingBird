//
//  Bird.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Bird.h"
#include <OpenGL/gl.h>
#include <Game.h>
#include <Texture2D.h>
#include <helpers.h>
#include "FlappingBird.h"

using namespace sge;


const float Bird::flapSpeed = -500.0f;
const float Bird::maxSpeed = 680.0f;
const float Bird::gravity = 2000.0f;

const float w = 17.0f, h = 12.0f;

Bird::Bird(const Texture2D* sprites, float groundHeight)
: speed(0.0f), ground(groundHeight), dead(false), started(false), elapsed(0.0),
flaptime(0.0),
frames{
	{sprites, {223.0f, 124.0f, w, h}}, // wing down
	{sprites, {264.0f,  90.0f, w, h}}, // wing center
	{sprites, {264.0f,  64.0f, w, h}}  // wing top
} {
	Window* window = Game::instance()->window;
	float x = window->getWidth() / 5.0f;
	float y = window->getHeight() / 2.0f;
	
	bounds.width = 2.5f * w;
	bounds.height = 2.5f * h;
	bounds.x = x - bounds.width / 2.0f;
	bounds.y = y - bounds.height / 2.0f;
	
	startingPos = bounds.topLeft();
}

void Bird::update(double deltaTime) {
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed)
		speed = maxSpeed;
	bounds.y += speed * deltaTime;
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed)
		speed = maxSpeed;
	
	if(bounds.midY() + bounds.width / 2.0f >= ground) {
		die();
		bounds.y = ground + 2.5f - (bounds.width + bounds.height) / 2.0f;
	}
}

void Bird::draw(double deltaTime) {
	int i;
	
	if(started) {
		float rotation;
		if(speed < maxSpeed * 0.15f)
			rotation = -M_PI / 10.0f;
		else
			rotation = speed*speed / (maxSpeed*maxSpeed) * M_PI_2;
		
		frames[1].draw(bounds, rotation);
	}
	else {
		elapsed += deltaTime;
		flaptime += deltaTime;
		
		Rectangle frame(bounds);
		frame.y += 6.0f * sinf(8.0f * elapsed);
		
		if(dead) {
			frames[1].draw(frame);
		}
		else {
			if(flaptime > 0.5) {
				flaptime = fmod(flaptime, 0.5);
			}
			
			// 100 flaps in 46 seconds, so about 1/6 seconds for each frame
			// Yes, I actually used a stopwatch and counted. Get over it.
			i = (int)(flaptime * 6);
			frames[i].draw(frame);
		}
	}
}

void Bird::flap() {
	if(dead) return;
	started = true;
	if(bounds.top() < 0.0f) return;
	speed = flapSpeed;
}

void Bird::die() {
	dead = true;
}

void Bird::reset() {
	bounds.x = startingPos.x;
	bounds.y = startingPos.y;
	speed = 0.0f;
	elapsed = 0.0;
	dead = false;
	started = false;
}

bool Bird::isDead() const {
	return dead;
}

const Rectangle& Bird::getBounds() const {
	return bounds;
}

