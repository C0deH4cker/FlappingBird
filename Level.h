//
//  Level.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_LEVEL_H_
#define _FB_LEVEL_H_

#include <list>
#include <random>
#include <Content.h>
#include <Texture2D.h>
#include <Rectangle.h>
#include "Pipe.h"

using namespace sge;

class Level {
public:
	const static int scrollSpeed;
	const static float pipeDistance;
	const static float pipeSpread;
	
	Level(const Content& content);
	~Level();
	
	void update(double deltaTime);
	void draw(double deltaTime);
	void charTyped(unsigned char uc);
	
	void pause();
	void resume();
	bool isPaused() const;
	void restart();
	
private:
	Bird* bird;
	int score;
	bool paused;
	bool started;
	
	Texture2D* background;
	Texture2D* pipeTop;
	Texture2D* pipeBottom;
	Texture2D* ground;
	Rectangle groundRect;
	
	float distance;
	std::list<Pipe*> pipes;
	std::mt19937 rng;
	std::uniform_real_distribution<float> distribution;
	
	void addPipe(float scrolled);
	void showScore();
};


#endif /* _FB_LEVEL_H_ */
