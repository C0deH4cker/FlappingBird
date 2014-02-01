//
//  Pipe.cpp
//  FlappyBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Pipe.h"
#include <Content.h>
#include "FlappyBird.h"

using namespace sge;


Pipe::Pipe(const Vector2& pos, Texture2D* topImage, Texture2D* bottomImage)
: top(topImage), bottom(bottomImage), scored(false) {
	topRect    = Rectangle(pos.x,
						   pos.y - top->height - Level::pipeSpread,
						   top->width,
						   top->height);
	
	bottomRect = Rectangle(topRect.x,
						   pos.y + Level::pipeSpread,
						   bottom->width,
						   bottom->height);
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

