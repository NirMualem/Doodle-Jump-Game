#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include <memory.h>

//this class represents jetpack in the game.

class Jetpack : public SpriteObject
{
public:
	Jetpack(const sf::Vector2f loc);//constractor
	virtual ~Jetpack() = default;
};