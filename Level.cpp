//
//  Level.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Level.h"
#include <random>
#include <iostream>
#include <math.h>
#include <time.h>
#include <sge.h>
#include "Pipe.h"
#include "FlappingBird.h"

using namespace sge;


const int Level::scrollSpeed = 230;
const float Level::pipeDistance = 240.0f;
const float Level::pipeSpread = 65.0f;

Level::Level(const Content& content, Rectangle bounds)
: distance(0.0f), rng((unsigned)time(NULL)), paused(false), started(false),
distribution(0.1f, 0.7f), viewport(bounds),
sprites(content.load<Texture2D>("spritesheet.png", GL_NEAREST)),
score(sprites),
background(sprites, {0.0f, 0.0f, 144.0f, 256.0f}),
pipeTop(sprites, {302.0f, 0.0f, 26.0f, 135.0f}),
pipeBottom(sprites, {330.0f, 0.0f, 26.0f, 121.0f}),
ground(sprites, {146.0f, 0.0f, 156.0f, 54.0f}),
groundRect(0.0f, viewport.height - 2.0f * ground.getHeight(),
		   4.0f * ground.getWidth(), 2.0f * ground.getHeight()) {
	bird = new Bird(sprites, viewport.height - 2.0f * ground.getHeight());
}

Level::~Level() {
	delete sprites;
}

void Level::update(double deltaTime) {
	if(paused) return;
	
	float dx = scrollSpeed * deltaTime;
	
	if(!bird->isDead()) {
		groundRect.x -= dx;
		float overlap = viewport.width - groundRect.right();
		if(overlap > 0.0f)
			groundRect.x = fmodf(groundRect.x, 28.0f);
	}
	
	if(!started) return;
	
	bird->update(deltaTime);
	
	if(bird->isDead()) return;
	
	auto it = pipes.begin();
	while(it != pipes.end()) {
		(*it)->scroll(dx);
		
		if((*it)->didScore(bird))
			++score;
		
		if((*it)->collides(bird)) {
			bird->die();
			showScore();
		}
		
		if((*it)->offScreen()) {
			delete *it;
			it = pipes.erase(it);
		}
		else ++it;
	}
	
	float fromEdge = fmodf(distance, pipeDistance) + dx - pipeDistance;
	
	// Should only execute once at max unless FPS < 1
	while(fromEdge > 0.0f) {
		addPipe(fromEdge);
		fromEdge -= pipeDistance;
	}
	
	distance += dx;
}

void Level::draw(double deltaTime) {
	background.draw(viewport);
	
	for(auto it = pipes.begin(); it != pipes.end(); ++it) {
		(*it)->draw();
	}
	
	bird->draw(paused ? 0.0 : deltaTime);
	
	ground.draw(groundRect);
	
	score.draw();
}

void Level::charTyped(unsigned char uc) {
	switch(uc) {
		case ' ':
			if(paused)
				resume();
			if(!started)
				started = true;
			bird->flap();
			break;
		
		case 'p':
			paused = !paused;
			break;
		
		case 'r':
			restart();
			break;
		
		default:
			break;
	}
}

void Level::pause() {
	paused = true;
}

void Level::resume() {
	paused = false;
}

bool Level::isPaused() const {
	return paused;
}

void Level::restart() {
	bird->reset();
	
	distance = 0.0f;
	pipes.clear();
	score = 0;
	paused = false;
	started = false;
}

void Level::addPipe(float scrolled) {
	float x, y;
	
	x = viewport.width - scrolled;
	
	/* arcsin(2x-1)/pi+0.5 */
	y = viewport.height * (asinf(2.0f * distribution(rng) - 1.0f) / M_PI + 0.5f);
	
	Pipe* pipe = new Pipe(Vector2(x, y), &pipeTop, &pipeBottom);
	pipes.push_back(pipe);
}

void Level::showScore() {
	// TODO: implement final score display
}

