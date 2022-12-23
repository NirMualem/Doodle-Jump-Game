#include <SFML/Graphics.hpp>
#include "GameObjects/ObjectAbstract.h"
#include "Data/ConstForGame.h"
#include "Data/Enums.h"
//this class is abstract for object

ObjectAbstract::ObjectAbstract(const sf::Vector2f loc): m_delete(false)
{
	m_directionLoc = sf::Vector2f(1, 0);
}
//----------------------------------------------------------------------------------
//set position
void ObjectAbstract::setPosition(sf::Vector2f last)
{
	m_sprite.setPosition(last);
}
//----------------------------------------------------------------------------------
//
void ObjectAbstract::setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);
}

//get the location
sf::Vector2f ObjectAbstract::getLocation()
{
	return m_sprite.getPosition();
}
//get the sprite
sf::Sprite ObjectAbstract::getsprite()const
{
	return m_sprite;
}

bool ObjectAbstract::checkCollision(const sf::FloatRect& rect) const
{
	return m_sprite.getGlobalBounds().intersects(rect);
}

void ObjectAbstract::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
bool ObjectAbstract::checkIfDelete() const
{
	return m_delete;
}

void ObjectAbstract::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)
	{
		m_directionLoc = sf::Vector2f(0, 1);
		m_sprite.move(m_directionLoc * deltaTime);
	}
}
void ObjectAbstract::setIfDeleted(bool ifDelete)
{
	m_delete = ifDelete;
}