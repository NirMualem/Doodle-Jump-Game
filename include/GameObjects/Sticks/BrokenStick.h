#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"

class Player;
class StaticStick;

//this class is broken stick object player cant jump on ,in the board of the game.

class BrokenStick :public SpriteObject
{
public:
	BrokenStick(const sf::Vector2f loc);//constructor.
	virtual ~BrokenStick() = default;//distructor.
};