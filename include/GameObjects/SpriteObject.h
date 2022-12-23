#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data/Enums.h"
#include "ObjectAbstract.h"
#include <memory.h>
class Player;
class BrokenStick;

//this class is absract of move object in the game
using std::vector;
using std::unique_ptr;

class SpriteObject : public ObjectAbstract
{
public:
	SpriteObject(const sf::Vector2f loc, const sf::Texture& texture);//constractor
	virtual ~SpriteObject() = default;
};