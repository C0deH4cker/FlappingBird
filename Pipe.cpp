//
//  Pipe.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Pipe.h"
#include <sge.h>
#include "FlappingBird.h"

using namespace sge;


Pipe::Pipe(const Vector2& pos, const Sprite* topImage, const Sprite* bottomImage)
: top(topImage), bottom(bottomImage), scored(false) {
	topRect    = Rectangle(pos.x,
						   pos.y - 3.0f * top->getHeight() - Level::pipeSpread,
						   3.0f * top->getWidth(),
						   3.0f * top->getHeight());
	
	bottomRect = Rectangle(topRect.x,
						   pos.y + Level::pipeSpread,
						   3.0f * bottom->getWidth(),
						   3.0f * bottom->getHeight());
}

void Pipe::scroll(float x) {
	topRect.x -= x;
	bottomRect.x = topRect.x;
}

void Pipe::draw() {
	top->draw(topRect);
	bottom->draw(bottomRect);
}

bool Pipe::collides(const Bird* bird) const {
	const Rectangle& rect(bird->getBounds());
	
	return rect.intersects(topRect) || rect.intersects(bottomRect);
}

bool Pipe::didScore(const Bird* bird) {
	if(scored) return false;
	
	bool inside = bird->getBounds().left() >= topRect.x;
	if(inside)
		scored = true;
	
	return inside;
}

bool Pipe::offScreen() const {
	return topRect.right() <= 0.0f;
}

