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


Pipe::Pipe(const Vector2& pos, const Sprite* topImage, const Sprite* bottomImage, float pipeSpread)
: top(topImage), bottom(bottomImage), scored(false) {
	topRect    = Rectangle(pos.x,
						   pos.y - 3.0f * top->getHeight() - pipeSpread,
						   3.0f * top->getWidth(),
						   3.0f * top->getHeight());
	
	bottomRect = Rectangle(topRect.x,
						   pos.y + pipeSpread,
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
	const Rectangle& rect(bird->getBBox());
	
	// Perform bounding box collision detection
	if(rect.intersects(topRect) || rect.intersects(bottomRect)) {
		// Do more accurate circle-box collision detection
		Vector2 center = rect.center();
		
		// Hit the side of a pipe
		if(center.y >= topRect.bottom() || center.y <= bottomRect.top())
			return true;
		
		// X is between the pipes
		if(center.x >= topRect.left() && center.x <= topRect.right()) {
			if(rect.top() <= topRect.bottom() ||
			   rect.bottom() >= bottomRect.top()) {
				return true;
			}
		}
		
		float radius = rect.width / 2.0f;
		float r2 = radius*radius;
		
		if(center.sqrdistance(topRect.bottomLeft()) > r2 &&
		   center.sqrdistance(bottomRect.bottomLeft()) > r2 &&
		   center.sqrdistance(topRect.bottomLeft()) > r2 &&
		   center.sqrdistance(bottomRect.topRight()) > r2) {
			return true;
		}
	}
	
	return false;
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

