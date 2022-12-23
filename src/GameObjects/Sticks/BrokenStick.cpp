#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Sticks/BrokenStick.h"
#include "GameObjects/SpriteObject.h"
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include "Data/ImageAndAudio.h"
/*
* class represnt broke stick that player cant jump on
*/

//----------------------------------------------------------------------------------
//constructor.
BrokenStick::BrokenStick(const sf::Vector2f loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getStick(Sticks::BROKE))
{
}

