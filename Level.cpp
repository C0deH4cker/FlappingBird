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
#include <OpenGL/gl.h>
#include <math.h>
#include <time.h>
#include <Timer.h>
#include "Pipe.h"
#include "FlappingBird.h"

using namespace sge;


const int Level::scrollSpeed = 230;
const float Level::pipeDistance = 240.0f;
const float Level::pipeSpread = 65.0f;

Level::Level(const Content& content)
: distance(0.0f), rng((unsigned)time(NULL)), paused(true), score(0),
distribution(0.1f, 0.7f) {
	background = content.load<Texture2D>("background.png", GL_NEAREST);
	 
	pipeTop = content.load<Texture2D>("pipe_top.png", GL_NEAREST);
	pipeTop->width *= 3;
	pipeTop->height *= 3;
	
	pipeBottom = content.load<Texture2D>("pipe_bottom.png", GL_NEAREST);
	pipeBottom->width *= 3;
	pipeBottom->height *= 3;
	
	ground = content.load<Texture2D>("ground.png", GL_NEAREST);
	ground->width *= 4;
	ground->height *= 2;
	
	Rectangle viewport = Game::instance()->window->getBounds();
	groundRect = Rectangle(0.0f, viewport.bottom() - ground->height,
						   ground->width, ground->height);
	
	bird = new Bird(content,
					Game::instance()->window->getHeight() - ground->height);
}

Level::~Level() {
	delete background;
	delete pipeTop;
	delete pipeBottom;
	delete ground;
}

void Level::update(double deltaTime) {
	if(paused) return;
	
	float dx = scrollSpeed * deltaTime;
	bird->update(deltaTime);
	
	if(bird->isDead()) return;
	
	groundRect.x -= dx;
	float overlap = Game::instance()->window->getWidth() - groundRect.right();
	if(overlap > 0.0f)
		groundRect.x = fmodf(groundRect.x, 28.0f);
	
	auto it = pipes.begin();
	while(it != pipes.end()) {
		(*it)->scroll(dx);
		
		if((*it)->didScore(bird)) {
			score++;
			std::cout << "Score: " << score << std::endl;
		}
		
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
	Rectangle viewport = Game::instance()->window->getBounds();
	background->draw(viewport);
	
	for(auto it = pipes.begin(); it != pipes.end(); ++it) {
		(*it)->draw();
	}
	
	bird->draw(paused ? deltaTime : 0.0);
	
	ground->draw(groundRect);
}

void Level::charTyped(unsigned char uc) {
	switch(uc) {
		case ' ':
			if(paused)
				resume();
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
	paused = true;
}

void Level::addPipe(float scrolled) {
	float x, y;
	
	Window* window = Game::instance()->window;
	float screenHeight = window->getHeight();
	
	x = window->getWidth() - scrolled;
	
	/* arcsin(2x-1)/pi+0.5 */
	y = screenHeight * (asinf(2.0f * distribution(rng) - 1.0f) / M_PI + 0.5f);
	
	Pipe* pipe = new Pipe(Vector2(x, y), pipeTop, pipeBottom);
	pipes.push_back(pipe);
}

void Level::showScore() {
	// TODO: implement score
}

