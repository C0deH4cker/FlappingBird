//
//  FlappingBird.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "FlappingBird.h"
#include <Color.h>
#include <random>

using namespace sge;

FlappingBird::FlappingBird() {
	window->setTitle("FlappingBird");
	window->setSize(480, 640);
	window->hideCursor(true);
}

FlappingBird::~FlappingBird() {
	delete level;
}

void FlappingBird::initialize() {
	level = new Level(content);
}

void FlappingBird::update(double deltaTime) {
	level->update(deltaTime);
}

void FlappingBird::draw(double deltaTime) {
	level->draw(deltaTime);
}

void FlappingBird::charTyped(unsigned int uc) {
	level->charTyped(uc);
}

