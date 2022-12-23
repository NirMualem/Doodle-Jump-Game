#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Spring.h"
#include "GameObjects/AnimationObject.h"
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include "Data/ConstForGame.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

//this class represents spring in the game.
Spring::Spring(const sf::Vector2f loc) 
	: AnimationObject(loc, ImageAndAudio::instance().animationData(ObjectsAnimation::Springs), Skin::Up)
{
}

//----------------------------------------------------------------------------------
//move spring
void Spring::move(const float deltaTime, SideToMove side, sf::Time time)
{
	AnimationObject::move(deltaTime, side , time);
	if (m_sprite.getPosition().y + IMAGE_SIZE_HEIGHT > WINDOW_GAME_HEIGHT)
		m_delete = true;
}
