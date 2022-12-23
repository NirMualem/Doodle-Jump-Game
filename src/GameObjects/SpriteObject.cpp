#include <SFML/Graphics.hpp>
#include "GameObjects/SpriteObject.h"
#include "GameObjects/ObjectAbstract.h"
#include "Data/Enums.h"
#include <SFML/Graphics.hpp>
#include "GameObjects/Player.h"
#include "Data/ConstForGame.h"
#include <memory.h>

using std::vector;
using std::unique_ptr;

//this class is absract of move object in the game

//constractor
SpriteObject::SpriteObject(const sf::Vector2f loc, const sf::Texture& texture)
	: ObjectAbstract(loc)
{
	//update the texture
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getOrigin().x + IMAGE_MIDDLE, m_sprite.getOrigin().y));
	m_sprite.setPosition(sf::Vector2f(loc));

	m_side = SideToMove::RIGHT;
}
