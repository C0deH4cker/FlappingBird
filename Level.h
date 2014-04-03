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
#include <sge.h>
#include "Pipe.h"
#include "Score.h"
#include "PowerUp.h"

using namespace sge;

class Level {
public:
	const static int scrollSpeed;
	static float pipeSpread;
	static float pipeDistance;
	
	Level(const Content& content, Rectangle bounds);
	~Level();
	
	void update(double deltaTime);
	void draw(double deltaTime);
	void charTyped(unsigned char uc);
	
	void pause();
	void resume();
	bool isPaused() const;
	void restart();
	void decreaseSpread();
	void increaseSpread();
	void decreaseDistance();
	void increaseDistance();
	float getSpread();

	
private:
	Bird* bird;
	bool paused;
	bool started;
	
	
	Rectangle viewport;
	Texture2D* sprites;
	Score score;
	Sprite background;
	Sprite pipeTop;
	Sprite pipeBottom;
	Sprite ground;
	Sprite feather;
	Rectangle groundRect;
	
	float distance;
	std::list<Pipe*> pipes;
	std::list<PowerUp*> pups;
	std::mt19937 rng;
	std::uniform_real_distribution<float> distribution;
	
	void addPipe(float scrolled);
	void addPowerUp(float scrolled);
	void showScore();
};


#endif /* _FB_LEVEL_H_ */
