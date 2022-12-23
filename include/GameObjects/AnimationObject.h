#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data/Enums.h"
#include "ObjectAbstract.h"
#include <memory.h>
#include "Animation/Animation.h"

class Player;
class BrokenStick;

using std::vector;
using std::unique_ptr;

//this class is absract of move object in the game
class AnimationObject : public ObjectAbstract
{
public:
	AnimationObject(const sf::Vector2f loc , const AnimationData& animation, Skin skin);//constractor
	virtual ~AnimationObject() = default;//distractor
	void updateDir(Skin skin);//update dir = skin
	virtual void move(const float deltaTime, SideToMove side, sf::Time time);//move object 
	
protected:
	Animation m_animation;//animation of the object
	SideToMove m_side;//side of the object
	sf::Vector2f m_directionLoc;//side of the sprite
};