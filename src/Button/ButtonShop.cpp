#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "Button/ButtonShop.h"
#include "Button/ButtonData.h"
#include "Data/ImageAndAudio.h"
#include "GameObjects/Player.h"
#include <iostream>

using std::string;
//this class is present button on the shop 
ButtonShop::ButtonShop(sf::Vector2f loc, const sf::Texture& texture, double scale, const sf::Texture& textureLock , int cost) :ButtonData(loc, texture, scale , textureLock), m_cost(cost)
{
	m_lock.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 90);
	m_buyBack.setTexture(*ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::BUY_BACK));
	m_noMoneyBack.setTexture(*ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::NO_MONEY_BACK));
}

//----------------------------------------------------------------------------------
//update if active or not
bool ButtonShop::updateIfActive()
{
	if (Player::m_collectedCoin < m_cost && !m_active)
	{
		sf::RenderWindow noMoney(sf::VideoMode(300, 200), "jump jump", sf::Style::Titlebar | sf::Style::Close);
		while (noMoney.isOpen())
		{
			noMoney.clear();
			noMoney.draw(m_noMoneyBack);
			noMoney.display();
			Sleep(1700);
			noMoney.close();
			return false;
		}
	}
	else if(m_active)
		return true;
	else
	{
		sf::RenderWindow buy(sf::VideoMode(300, 200), "jump jump", sf::Style::Titlebar | sf::Style::Close);
		while (buy.isOpen())
		{
			buy.clear();
			buy.draw(m_buyBack);
			sf::Sprite buySprite = m_sprite;
			buySprite.setScale(1, 1); 
			buySprite.setPosition(sf::Vector2f(130, 110));
			buy.draw(buySprite);
			buy.display();
			for (auto event = sf::Event{}; buy.pollEvent(event);)
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					buy.close();
					return false;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Y)
					{

						Player::m_collectedCoin = Player::m_collectedCoin - m_cost;
						setActive(true);
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}

	}
}
//----------------------------------------------------------------------------------
//set active
void ButtonShop::setActive(const bool pass)
{
	m_lock.setTexture(*ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::OPEN_LOCK));
	m_active = pass;
	m_cost = 0;
}
//----------------------------------------------------------------------------------
//get price
int ButtonShop::getPrice()const
{
	return m_cost;
}