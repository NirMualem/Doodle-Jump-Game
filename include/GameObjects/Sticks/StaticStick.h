#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include <memory.h>

//this class is static object class in the board of the game.

class StaticStick : public SpriteObject
{
public:
	StaticStick(const sf::Vector2f loc);//constructor
	virtual ~StaticStick() = default;//distructor
};