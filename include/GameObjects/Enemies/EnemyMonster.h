#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data/Enums.h"
#include "Animation/Animation.h"
#include "GameObjects/AnimationObject.h"

/*
* enemy monster no move , in board
*/

class EnemyMonster : public AnimationObject
{
public:
	EnemyMonster(const sf::Vector2f loc);//constractor
	virtual ~EnemyMonster() = default;//distractor
};