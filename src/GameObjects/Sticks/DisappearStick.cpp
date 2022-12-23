#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Sticks/DisapperStick.h"
#include "GameObjects/SpriteObject.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

/*
* class represent stick that dissapear after on jump
*/

//----------------------------------------------------------------------------------
//constructor.
DisappearStick::DisappearStick(const sf::Vector2f loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getStick(Sticks::DISSAPEAR))
{
}
