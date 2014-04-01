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
float Level::pipeDistance = 240.0f;
float Level::pipeSpread = 65.0f;
Level::Level(const Content& content, Rectangle bounds)
: distance(0.0f), rng((unsigned)time(NULL)), paused(false), started(false),
distribution(0.1f, 0.7f), viewport(bounds),
sprites(content.load<Texture2D>("spritesheet.png", GL_NEAREST)),
score(sprites),
background(sprites, {0.0f, 0.0f, 144.0f, 256.0f}),
pipeTop(sprites, {302.0f, 0.0f, 26.0f, 135.0f}),
pipeBottom(sprites, {330.0f, 0.0f, 26.0f, 121.0f}),
ground(sprites, {146.0f, 0.0f, 154.0f, 54.0f}),
feather(sprites, {302.0f, 201.0f, 18.0f, 17.0f}),
groundRect(0.0f, viewport.height - 2.0f * ground.getHeight(),
		   4.0f * ground.getWidth(), 3.0f * ground.getHeight()) {
	bird = new Bird(sprites, viewport.height - 2.0f * ground.getHeight());
}

Level::~Level() {
	delete sprites;
}

void Level::update(double deltaTime) {
	if(paused) return;

	if (bird->isSlowed()) {
		deltaTime *= 0.25;
	}
	
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

	auto pupIt = pups.begin();
	while(pupIt != pups.end()) {
		(*pupIt)->scroll(dx);

		if((*pupIt)->collides(bird)) {
			if (!(*pupIt)->isEaten()) {
				bird->addSlowedTime(3.5);
			}
			(*pupIt)->eat();
		}

		if((*it)->offScreen()) {
			delete *pupIt;
			pupIt = pups.erase(pupIt);
		}
		else ++pupIt;
	}
	
	float fromEdge = fmodf(distance, pipeDistance) + dx - pipeDistance;
	float pupFromEdge = fmodf(distance-0.5*pipeDistance, pipeDistance) + dx - pipeDistance;
	
	// Should only execute once at max unless FPS < 1
	while(fromEdge > 0.0f) {
		addPipe(fromEdge);
		fromEdge -= pipeDistance;
	}

	while (pupFromEdge > 0.0f) {
		addPowerUp(pupFromEdge);
		pupFromEdge -= pipeDistance;
	}


	
	distance += dx;
}

void Level::draw(double deltaTime) {
	background.draw(viewport);
	
	for(auto it = pipes.begin(); it != pipes.end(); ++it) {
		(*it)->draw();
	}

	for(auto it = pups.begin(); it != pups.end(); ++it) {
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
			if(paused)
				resume();
			else
				pause();
			break;
		
		case 'r':
			restart();
			break;

		case 'u':
			bird->addSlowedTime(2.5);
			break;
		case 'w':
			decreaseSpread();
			break;		
		case 's':
			increaseSpread();
			break;	
		case 'a':
			decreaseDistance();
			break;	
		case 'd':
			increaseDistance();
			break;	
		default:
			break;
	}
}

void Level::pause() {
	paused = true;
	bird->pause();
}

void Level::resume() {
	paused = false;
	bird->resume();
}

bool Level::isPaused() const {
	return paused;
}

void Level::decreaseSpread() {
	if(pipeSpread>40.0)
		pipeSpread-=30.0f;
}

void Level::increaseSpread() {
	if(pipeSpread<160)
		pipeSpread+=30.0f;
}

void Level::decreaseDistance() {
	if(pipeDistance>120)
		pipeDistance-=80.0f;
}

void Level::increaseDistance() {
	if(pipeDistance<360)
		pipeDistance+=80.0f;
}

void Level::restart() {
	bird->reset();
	
	distance = 0.0f;
	pipes.clear();
	pups.clear();
	score = 0;
	paused = false;
	started = false;
	pipeSpread = 65.0f;
}

void Level::addPipe(float scrolled) {
	float x, y;
	
	x = viewport.width - scrolled;
	
	/* arcsin(2x-1)/pi+0.5 */
	y = viewport.height * (asinf(2.0f * distribution(rng) - 1.0f) / M_PI + 0.5f);
	
	Pipe* pipe = new Pipe(Vector2(x, y), &pipeTop, &pipeBottom, pipeSpread);
	pipes.push_back(pipe);
}

void Level::addPowerUp(float scrolled) {
	if (distribution(rng) > ((0.7f/4)*3)) {
		float x, y;

		x = viewport.width - scrolled;

		y = viewport.height * (asinf(2.0f * distribution(rng) - 1.0f) / M_PI + 0.5f);
		
		PowerUp* pup = new PowerUp(Vector2(x,y), &feather);
		pups.push_back(pup);
	}

}

void Level::showScore() {
	// TODO: implement final score display
}

