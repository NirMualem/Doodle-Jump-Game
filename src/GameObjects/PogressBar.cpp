#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/ProgressBar.h"
#include "GameObjects/SpriteObject.h"
#include "Data/ConstForGame.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"
/*
* class that represent the progress in levels
*/
//----------------------------------------------------------------------------------
//constructor.
ProgressBar::ProgressBar(const sf::Vector2f loc , float levelHight) 
	: SpriteObject(loc, *ImageAndAudio::instance().getPic(PicChoose::GAME , PicNameGame::PROGRESS_BAR)) ,m_levelHightFactor(levelHight)
{
	m_levelHightFactor = m_levelHightFactor / (WINDOW_GAME_HEIGHT - 200);//calculate factor to go up
	m_pogressMark.setTexture(*ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::PROGRESS));
	m_pogressMark.setPosition(sf::Vector2f(WINDOW_GAME_WIDTH - 50, WINDOW_GAME_HEIGHT - 100));
}
//----------------------------------------------------------------------------------
//draw bar and mark
void ProgressBar::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);//draw bar
	window.draw(m_pogressMark);
}

//----------------------------------------------------------------------------------
//move mark as progress in level
 void ProgressBar::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)
		m_directionLoc = sf::Vector2f(0, -1);
	else
		m_directionLoc = sf::Vector2f(0, 0);
	if(m_pogressMark.getPosition().y > 60)
		m_pogressMark.move(m_directionLoc * deltaTime / m_levelHightFactor);
}

