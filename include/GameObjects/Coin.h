#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include <memory.h>

//this class is coin class in the game.

class Coin : public SpriteObject
{
public:
	Coin(const sf::Vector2f loc);//constractor
	virtual ~Coin() = default;
};