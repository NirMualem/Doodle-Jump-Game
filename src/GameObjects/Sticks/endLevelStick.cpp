#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Sticks/endLevelStick.h"
#include "GameObjects/SpriteObject.h"
#include "GameObjects/Player.h"
#include "Menu.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

/*
* class represent end of level
*/

//----------------------------------------------------------------------------------
//constructor.
EndLevelStick::EndLevelStick(const sf::Vector2f loc) 
	: AnimationObject(loc, ImageAndAudio::instance().animationData(ObjectsAnimation::EndStick), static_cast<Skin>(Menu::m_currHighlightLevel))
{
}

//----------------------------------------------------------------------------------
//draw.
void EndLevelStick::draw(sf::RenderTarget& target) const
{
	target.draw(m_sprite);
}

