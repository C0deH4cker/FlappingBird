//
//  PowerUp.cpp
//  FlappingBird
//
//  Created by Sam Coulter on March 31, 2014
//

#include "PowerUp.h"
#include <sge.h>
#include "FlappingBird.h"

using namespace sge;


PowerUp::PowerUp(const Vector2& pos, const Sprite* image)
: pupImage(image),
  eaten(false) {
	pupRect    = Rectangle(pos.x, pos.y, image->getWidth()*2, image->getHeight()*2);
}

void PowerUp::scroll(float x) {
	pupRect.x -= x;
}

void PowerUp::draw() {
	if (!eaten)	pupImage->draw(pupRect);
}

bool PowerUp::collides(const Bird* bird) const {
	const Rectangle& rect(bird->getBBox());
	
	// Perform bounding box collision detection
	if(rect.intersects(pupRect)) {
		// Do more accurate circle-box collision detection
		Vector2 center = rect.center();
		Vector2 pupCenter = pupRect.center();

		float radius = rect.width / 2.0f;
		float r2 = radius*radius;
		
		float pradius = pupRect.width / 2.0f;
		float pr2 = pradius*pradius;
		
		if(center.sqrdistance(pupRect.center()) < r2 + pr2) {
			return true;
		}
	}
	
	return false;
}

bool PowerUp::offScreen() const {
	return pupRect.right() <= 0.0f;
}

void PowerUp::eat() {
	eaten = true;
}

bool PowerUp::isEaten() {
	return eaten;
}

