#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Sticks/MoveStick.h"
#include "GameObjects/SpriteObject.h"
#include "Data/constForGame.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

/*
* move right and left stick to player jump on
*/

const float LOW = 0.2;//lowest speed
const float HIGH = 0.5;//highest speed

//----------------------------------------------------------------------------------
//constructor.
MoveStick::MoveStick(const sf::Vector2f loc) 
	: SpriteObject(loc, *ImageAndAudio::instance().getStick(Sticks::MOVE))
{
	m_side = static_cast<SideToMove>((rand() % 2) + 1);//random start side
	m_speed = LOW + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HIGH - LOW)));//update speed between low and high
}

//----------------------------------------------------------------------------------
//move sticks left and right 
void MoveStick::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)//update if screen go down
		m_directionLoc = sf::Vector2f(0, 1);
	else
		m_directionLoc = sf::Vector2f(0, 0);

	

	if (m_sprite.getPosition().x < 30 || m_sprite.getPosition().x + IMAGE_SIZE_WIDTH - IMAGE_SIZE_MIDDLE - 10  > WINDOW_GAME_WIDTH)// chack if out of game window

		if (m_side == SideToMove::RIGHT)
		{
			m_side = SideToMove::LEFT;
		}
		else if (m_side == SideToMove::LEFT)
		{
			m_side = SideToMove::RIGHT;
		}
		if (m_side == SideToMove::LEFT)
		{
			m_directionLoc = sf::Vector2f(-m_speed, m_directionLoc.y);
		}
		if (m_side == SideToMove::RIGHT)
		{
			m_directionLoc = sf::Vector2f(m_speed, m_directionLoc.y);

		}

		m_sprite.move(m_directionLoc * deltaTime);
}