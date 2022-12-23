#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Bullet.h"
#include "GameObjects/SpriteObject.h"
#include "Data/ImageAndAudio.h"
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include <memory.h>

//this class represents bullet of the player.
Bullet::Bullet(const sf::Vector2f loc, sf::Vector2f mouse_loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::BULLET))
{
	float angle;
	float leanth;
	sf::Vector2f direct(mouse_loc.x - loc.x, mouse_loc.y - loc.y);
	leanth = sqrt(direct.x * direct.x + direct.y * direct.y);
	direct = sf::Vector2f(direct.x / leanth, direct.y / leanth);//normalize the vector to be |v| = 1 
	m_direction = direct;
	angle = atan2((mouse_loc.x - loc.x), (loc.y - mouse_loc.y));
	angle *= 180 / (atan(1) * 4);//convert to degree	
	m_sprite.setRotation(angle);
}//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//move the bullet to direction the player click
void Bullet::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)
		m_directionLoc = sf::Vector2f(0, 1);
	else
		m_directionLoc = sf::Vector2f(0, 0);

	m_directionLoc = sf::Vector2f(m_direction.x * 1.2, (m_directionLoc.y + m_direction.y) * 1.2);
	m_sprite.move(m_directionLoc * deltaTime);
}