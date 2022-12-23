#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AnimationObject.h"
#include <memory.h>

//this class represents spring in the game.

class Spring : public AnimationObject
{
public:
	Spring(const sf::Vector2f loc);//constractor
	virtual ~Spring()=default;
	void move(const float deltaTime, SideToMove side, sf::Time time);//move spring
};