//
//  Score.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 2/8/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Score.h"
#include <string>
#include <sge.h>

using namespace sge;

const float Score::spacing = 1.0f;
const float Score::scale = 3.0f;

const float w = 7.0f, h = 10.0f;

Score::Score(const Texture2D* sprites)
: value(0), digits{
	{sprites, {288.0f, 100.0f, w, h}}, // 0
	{sprites, {289.0f, 118.0f, w, h}}, // 1
	{sprites, {289.0f, 134.0f, w, h}}, // 2
	{sprites, {289.0f, 150.0f, w, h}}, // 3
	{sprites, {287.0f, 173.0f, w, h}}, // 4
	{sprites, {287.0f, 185.0f, w, h}}, // 5
	{sprites, {165.0f, 245.0f, w, h}}, // 6
	{sprites, {175.0f, 245.0f, w, h}}, // 7
	{sprites, {185.0f, 245.0f, w, h}}, // 8
	{sprites, {195.0f, 245.0f, w, h}}  // 9
} {}

Score& Score::operator=(int points) {
	value = points;
	return *this;
}

Score& Score::operator++() {
	if(value >=2 && value <7)
	{
		value = value + 5;
	}else if(value >= 7){
		value = value +10;
	}else{
	value= value +1;
	}
	return *this;
}

void Score::draw() const {
	Rectangle viewport = Game::instance()->window->getBounds();
	float midX = viewport.width / 2.0f;
	
	std::string disp = std::to_string(value);
	
	float total = scale * (w * disp.size() + spacing * (disp.size() - 1));
	float left = midX - total / 2.0f;
	float step = scale * (spacing + w);
	
	for(unsigned i = 0; i < disp.size(); ++i) {
		int dig = disp[i] - '0';
		digits[dig].draw({left + i * step, viewport.height * 0.02f,
		                scale * w, scale * h});
	}
}

