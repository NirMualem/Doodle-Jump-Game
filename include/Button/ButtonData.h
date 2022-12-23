#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

using std::string;

//this class is present button on the windows 
class ButtonData :public Button
{
public:
	ButtonData(sf::Vector2f loc, const sf::Texture& texture, double scale ,const sf::Texture& textureLock);//constractor
	void setActive(const bool pass);//set active button
	virtual bool updateIfActive() ;//get if the button active
	virtual void setLoc(const sf::Vector2f& location);//set location of button
	virtual void draw(sf::RenderWindow& window) const override;//draw button
	virtual void create() override;//create button

protected:
	sf::Sprite m_lock;//lock sprite
	bool m_active;//if the button active or not 
	const sf::Texture& m_lockTexture;//texture of lock
private:

};