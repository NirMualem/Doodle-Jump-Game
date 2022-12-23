#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include <memory.h>

//this class is stick object that dissapear after one jump , in the board of the game.

class DisappearStick : public SpriteObject
{
public:
	DisappearStick(const sf::Vector2f loc);//constructor.
	virtual ~DisappearStick() = default;//distructor.
};