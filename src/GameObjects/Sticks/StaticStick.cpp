#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Sticks/StaticStick.h"
#include "GameObjects/SpriteObject.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

/*
* static stick to player jump on
*/

//----------------------------------------------------------------------------------
//constructor.
StaticStick::StaticStick(const sf::Vector2f loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getStick(Sticks::NORMAL))
{
}
