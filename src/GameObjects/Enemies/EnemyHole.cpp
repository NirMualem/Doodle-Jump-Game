#include <SFML/Graphics.hpp>
#include "GameObjects/Enemies/EnemyHole.h"
#include "Animation/Animation.h"
#include "Data/ImageAndAudio.h"
#include "GameObjects/AnimationObject.h"

/*
* enemy class that player cant shoot
*/

//----------------------------------------------------------------------------------
//constructor.
EnemyHole::EnemyHole(const sf::Vector2f loc)
	: AnimationObject(loc, ImageAndAudio::instance().animationData(ObjectsAnimation::Hole), Skin::defaults)
{
}