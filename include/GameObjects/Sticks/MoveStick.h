#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include <memory.h>

//this class is move side stick in the board of the game.

class MoveStick : public SpriteObject
{
public:
	MoveStick(const sf::Vector2f loc);//constructor.
	virtual ~MoveStick() = default;//distructor.
	virtual void move(const float deltaTime, SideToMove side, sf::Time time);//move sticks left and right 
private:
	float m_speed;//speed the stick move
};