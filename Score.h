//
//  Score.h
//  FlappingBird
//
//  Created by C0deH4cker on 2/8/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_SCORE_H_
#define _FB_SCORE_H_

#include <sge.h>

using namespace sge;

class Score {
public:
	Score(const Texture2D* sprites=NULL);
	
	Score& operator=(int points);
	Score& operator++();
	
	void draw() const;
	
private:
	const static float spacing, scale;
	int value;
	Sprite digits[10];
};


#endif /* _FB_SCORE_H_ */
