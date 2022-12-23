#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "ButtonData.h"

using std::string;

//this class is present button on the shop 
class ButtonShop :public ButtonData
{
public:
	ButtonShop(sf::Vector2f loc, const sf::Texture& texture, double scale, const sf::Texture& textureLock, int cost);//constractor
	virtual bool updateIfActive();//get if active
	int getPrice() const;//get price 
	void setActive(const bool pass);//set if active 
private:
	sf::Sprite m_buyBack; //sprite of buy skins back 
	sf::Sprite m_noMoneyBack;//sprite of back of not buy skins
	int m_cost;//cost
};