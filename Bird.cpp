//
//  Bird.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Bird.h"
#include <sge.h>
#include <helpers.h>
#include "FlappingBird.h"

using namespace sge;


const float Bird::flapSpeed = -530.0f;
const float Bird::maxSpeed = 680.0f;
const float Bird::gravity = 2000.0f;
const double Bird::defaultFps = 2.0;

const float w = 17.0f, h = 12.0f;
const int POSCOUNT = 10;

Bird::Bird(const Texture2D* sprites, float groundHeight)
: speed(0.0f), ground(groundHeight), dead(false), started(false), paused(false),
curFrame(0), fps(POSCOUNT * defaultFps), extra(0.0), onGround(false),
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
	if(onGround) return;
	
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed)
		speed = maxSpeed;
	bounds.y += speed * deltaTime;
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed)
		speed = maxSpeed;
	
	if(bounds.midY() + bounds.width / 2.0f >= ground) {
		die();
		onGround = true;
		bounds.y = ground + 2.5f - (bounds.width + bounds.height) / 2.0f;
	}
}

void Bird::draw(double deltaTime) {
	const double maxFps = 3.5;
	const double endtime = 1.2;
	const double coef = maxFps / (endtime*endtime);
	const double offset = 0.0 * endtime;
	
	int i;
	double elapsed = timer.elapsed();
	
	if(started) {
		double val = elapsed - offset;
		double freq = CLAMP(maxFps - coef * val*val, 0.0f, maxFps);
		
		setFlapsPerSec(freq);
		
		i = getFrame();
		frames[i].draw(bounds, getRotation());
	}
	else {
		Rectangle frame(bounds);
		frame.y += 6.0f * sinf(8.0f * elapsed);
		
		// Dead bird always drawn using middle frame
		i = dead ? 1 : getFrame();
		frames[i].draw(frame);
	}
}

void Bird::flap() {
	if(dead) return;
	started = true;
	timer.reset();
	wingTimer.reset();
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
	timer.reset();
	wingTimer.reset();
	setFlapsPerSec(defaultFps);
	dead = false;
	started = false;
	paused = false;
	onGround = false;
}

void Bird::pause() {
	timer.pause();
	wingTimer.pause();
	paused = true;
}

void Bird::resume() {
	timer.resume();
	wingTimer.resume();
	paused = false;
}

bool Bird::isDead() const {
	return dead;
}

const Rectangle& Bird::getBounds() const {
	return bounds;
}

Rectangle Bird::getBBox() const {
	// Bounding box is a square of dimensions width X width.
	// Makes it easier to work with in terms of rotation, and
	// still quite accurate.
	float diff = bounds.width - bounds.height;
	return Rectangle(bounds.x + diff / 2, bounds.y,
	                 bounds.height, bounds.height);
}


float Bird::getRotation() const {
	const float maxrot = M_PI / 10.0f;
	const float minrot = -M_PI_2;
	const float endtime = 0.4f;
	const float offset = 0.5f * endtime;
	const float coef = (maxrot - minrot) / (endtime*endtime);
	
	if(onGround)
		return minrot;
	
	float val = MAX(timer.elapsed() - offset, 0.0f);
	
	return CLAMP(maxrot - coef * val*val, minrot, maxrot);
}

void Bird::setFlapsPerSec(double flaps) {
	fps = POSCOUNT * flaps;
}

const int positions[POSCOUNT] = {1,0,0,0,1,1,2,2,2,1};
int Bird::getFrame() {
	if(paused) return positions[curFrame % POSCOUNT];
	
	if(fps <= 0.0 || onGround)
		return positions[0];
	
	double elapsed = wingTimer.elapsed() + extra;
	double freq = 1.0 / fps;
	
	if(elapsed > freq) {
		curFrame = (int)(curFrame + elapsed / freq) % POSCOUNT;
		extra = fmod(elapsed, freq);
		wingTimer.reset();
	}
	
	return positions[curFrame % POSCOUNT];
}

