#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/AnimationObject.h"
#include "Animation/Animation.h"
#include <memory.h>

//this class is end object class in the board of the game when choose level. 

class EndLevelStick : public AnimationObject
{
public:
	EndLevelStick(const sf::Vector2f loc);//constructor.
	virtual ~EndLevelStick() = default;//distructor.

private:
	void draw(sf::RenderTarget& target) const;//draw.
};