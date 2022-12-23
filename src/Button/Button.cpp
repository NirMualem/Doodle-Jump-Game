#include <SFML/Graphics.hpp>
#include "Button/Button.h"
#include <string>

using std::string;
//----------------------------------------------------------------------------------
//constrctor
Button::Button(sf::Vector2f loc, const sf::Texture& texture, double scale)
	:m_location(loc), m_texture(texture), m_scale(scale), m_choose(false)
{
	create();
	setScale(scale);
}
//----------------------------------------------------------------------------------
//return sprite
sf::Sprite Button::getSprite()const
{
	return m_sprite;
}
//----------------------------------------------------------------------------------
//check if click on the button
bool Button::handleClick(const sf::Vector2f& location) const
{
	if (m_sprite.getGlobalBounds().contains(location))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------------
//draw the button
 void Button::draw(sf::RenderWindow& window) const
{ 
	window.draw(m_sprite);
}
 //----------------------------------------------------------------------------------
//create 
void Button::create()
{
	auto result = sf::Sprite(m_texture);
	result.setPosition(sf::Vector2f(m_location.x, m_location.y));
	result.setScale(m_scale,m_scale);
	m_sprite = result;
}
//----------------------------------------------------------------------------------
//set scale of button
void Button::setScale(double scale)
{
	m_scale = scale;
	m_sprite.setScale(m_scale, m_scale);
}

//----------------------------------------------------------------------------------
//set choose button
void Button::setChoose(bool choose)
{
	m_choose = choose;
}
//get choose button
bool Button::getChoose() const
{
	return m_choose;
}
//----------------------------------------------------------------------------------
//set location of button
void Button::setLoc(const sf::Vector2f& location)
{
	m_sprite.setPosition(location);
}


