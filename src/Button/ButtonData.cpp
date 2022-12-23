#include <SFML/Graphics.hpp>
#include "Button/Button.h"
#include <string>
#include "Button/ButtonData.h"
#include "Data/ImageAndAudio.h"
#include <iostream>

using std::string;

//constrctor
ButtonData::ButtonData(sf::Vector2f loc, const sf::Texture& texture, double scale, const sf::Texture& textureLock) 
							:Button(loc,texture,scale), m_lockTexture(textureLock)
{
	m_active = false;
	create();
}
//----------------------------------------------------------------------------------
//set the button to be active
void ButtonData::setActive(const bool pass)
{
	m_lock.setTexture(*ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::OPEN_LOCK));
	m_active = pass;
}
//----------------------------------------------------------------------------------
//get if active
bool ButtonData::updateIfActive()
{
	return m_active;
}
//----------------------------------------------------------------------------------
//draw the button
void ButtonData::draw(sf::RenderWindow& window) const
{
		window.draw(m_sprite);
		window.draw(m_lock);
}
//----------------------------------------------------------------------------------
//create 
void ButtonData::create()
{
	auto lock = sf::Sprite(m_lockTexture);
	lock.setScale(m_scale, m_scale);
	lock.setPosition(sf::Vector2f(m_location.x, m_location.y));
	m_lock = lock;

	auto result = sf::Sprite(m_texture);
	result.setScale(m_scale, m_scale);
	result.setPosition(sf::Vector2f(m_location.x, m_location.y));
	m_sprite = result;
}
//----------------------------------------------------------------------------------
//set location
void ButtonData::setLoc(const sf::Vector2f& location)
{
	m_sprite.setPosition(location);
	m_lock.setPosition(location);
}