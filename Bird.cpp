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

Bird::Bird(const Content& content, float groundHeight)
: speed(0.0f), ground(groundHeight), dead(false), started(false) {
	texture = content.load<Texture2D>("bird.png", GL_NEAREST);
	
	Window* window = Game::instance()->window;
	float x = window->getWidth() / 5.0f;
	float y = window->getHeight() / 2.0f;
	
	bounds.width = 2.5f * texture->width;
	bounds.height = 2.5f * texture->height;
	bounds.x = x - bounds.width / 2.0f;
	bounds.y = y - bounds.height / 2.0f;
	
	startingPos = bounds.topLeft();
}

Bird::~Bird() {
	delete texture;
}

void Bird::update(double deltaTime) {
	// TODO: add death animation
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
	// TODO: add animation
	float rotation = 0.0f;
	if(started) {
		if(speed < maxSpeed * 0.15f)
			rotation = -M_PI / 10.0f;
		else
			rotation = speed*speed / (maxSpeed*maxSpeed) * M_PI_2;
	}
	
	texture->draw(bounds, rotation);
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
	dead = false;
	started = false;
}

bool Bird::isDead() const {
	return dead;
}

const Rectangle& Bird::getBounds() const {
	return bounds;
}

