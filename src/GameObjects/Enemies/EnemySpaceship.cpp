#include <SFML/Graphics.hpp>
#include "GameObjects/Enemies/EnemySpaceship.h"
#include "GameObjects/SpriteObject.h"
#include "Data/ConstForGame.h"
#include "Data/ImageAndAudio.h"

/*
* enemy class that move sideway
*/

//----------------------------------------------------------------------------------
//constructor.
EnemySpaceship::EnemySpaceship(const sf::Vector2f loc): SpriteObject(loc, *ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::SPACESHIP))
{
	m_side = static_cast<SideToMove>((rand() % 2) + 1);
}
//----------------------------------------------------------------------------------
//move spaceship
void EnemySpaceship::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)//if game down
		m_directionLoc = sf::Vector2f(0, 1);
	else
		m_directionLoc = sf::Vector2f(0, 0);

	if (m_sprite.getPosition().x < 0 || m_sprite.getPosition().x > 900 - IMAGE_MIDDLE)//if out of screen
		if (m_side == SideToMove::RIGHT)
			m_side = SideToMove::LEFT;
		else if (m_side == SideToMove::LEFT)
			m_side = SideToMove::RIGHT;

	if (m_side == SideToMove::RIGHT)
		m_directionLoc = sf::Vector2f(0.5, m_directionLoc.y);
	else if (m_side == SideToMove::LEFT)
		m_directionLoc = sf::Vector2f(-0.5, m_directionLoc.y);

	m_sprite.move(m_directionLoc * deltaTime);

}