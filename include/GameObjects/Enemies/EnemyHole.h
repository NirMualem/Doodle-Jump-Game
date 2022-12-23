#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation/Animation.h"
#include "GameObjects/AnimationObject.h"
#include "Data/Enums.h"

/*
* enemy class that player cant shoot
*/

class EnemyHole : public AnimationObject
{
public:
	EnemyHole(const sf::Vector2f loc);//constractor
	virtual ~EnemyHole() = default;//distractor
};