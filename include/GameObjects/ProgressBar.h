#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include <memory.h>

/*
* class that represent the progress in levels
*/

class ProgressBar : public SpriteObject
{
public:
	ProgressBar(const sf::Vector2f loc, float levelHight);//constructor
	virtual ~ProgressBar() = default;//distructor
	void draw(sf::RenderWindow& window) const;//draw the progress bar
	virtual void move(const float deltaTime, SideToMove side, sf::Time time);//move the mark
private:
	float m_levelHightFactor;//factor to calculate move
	sf::Sprite m_pogressMark;//mark of the pogress
};