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


const float Bird::flapSpeed = -480.0f;
const float Bird::maxSpeed = 650.0f;
const float Bird::gravity = 1600.0f;

Bird::Bird(const Content& content, float groundHeight)
: speed(0.0f), ground(groundHeight) {
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
	
	if(bounds.top() < 0.0f)
		bounds.y = 0.0f;
	
	if(bounds.bottom() >= ground) {
		die();
		bounds.y = ground - bounds.height + 2.5f;
	}
}

void Bird::draw(double deltaTime) {
	// TODO: add animation
	texture->draw(bounds);
}

void Bird::flap() {
	if(dead) return;
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
}

bool Bird::isDead() const {
	return dead;
}

const Rectangle& Bird::getBounds() const {
	return bounds;
}

