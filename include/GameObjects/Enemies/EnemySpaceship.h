#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include "Data/Enums.h"

/*
* enemy class that move sideway
*/

class EnemySpaceship : public SpriteObject
{
public:
	EnemySpaceship(const sf::Vector2f loc);//constractor
	virtual ~EnemySpaceship() = default;//distractor
	void move(const float deltaTime, SideToMove side, sf::Time time);//move spaceship
	
};