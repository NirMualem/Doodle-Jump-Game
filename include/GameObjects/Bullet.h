#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include <memory.h>

//this class is static object class in the board of the game.

class Bullet : public SpriteObject
{
public:
	Bullet(const sf::Vector2f loc, sf::Vector2f mouse_loc);
	virtual ~Bullet()=default;
	virtual void move(const float deltaTime, SideToMove side, sf::Time time);//move bullet

private:
	sf::Vector2f m_direction;//direction of the bullet
};