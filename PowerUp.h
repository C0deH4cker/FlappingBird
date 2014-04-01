#ifndef _FB_PUP_H_
#define _FB_PUP_H_

#include <sge.h>
#include "Bird.h"

using namespace sge;

class PowerUp {
public:
	PowerUp(const Vector2& pos, const Sprite* image);
	
	void scroll(float x);
	void draw();
	bool collides(const Bird* bird) const;
	bool offScreen() const;
	void eat();
	bool isEaten();
	
private:
	const Sprite* pupImage;
	Rectangle pupRect;
	bool eaten;
};


#endif /* _FB_PUP_H_ */
