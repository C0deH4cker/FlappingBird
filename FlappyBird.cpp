//
//  FlappyBird.cpp
//  FlappyBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "FlappyBird.h"
#include <Color.h>
#include <random>

using namespace sge;

FlappyBird::FlappyBird() {
	window->setTitle("FlappyBird");
	window->setSize(480, 640);
	window->hideCursor(true);
}

FlappyBird::~FlappyBird() {
	delete level;
}

void FlappyBird::initialize() {
	level = new Level(content);
}

void FlappyBird::update(double deltaTime) {
	level->update(deltaTime);
}

void FlappyBird::draw(double deltaTime) {
	level->draw(deltaTime);
}

void FlappyBird::charTyped(unsigned int uc) {
	level->charTyped(uc);
}

