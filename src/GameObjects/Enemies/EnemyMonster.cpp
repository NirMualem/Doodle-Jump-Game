#include <SFML/Graphics.hpp>
#include "GameObjects/Enemies/EnemyMonster.h"
#include "Menu.h"
#include "Data/ImageAndAudio.h"

/*
* enemy monster no move , in board
*/

//----------------------------------------------------------------------------------
//constructor.
EnemyMonster::EnemyMonster(const sf::Vector2f loc)
	: AnimationObject(loc, ImageAndAudio::instance().animationData(ObjectsAnimation::Monster), static_cast<Skin>(Menu::m_currHighlightLevel))
{
}