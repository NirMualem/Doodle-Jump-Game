#include <SFML/Graphics.hpp>
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include "Data/ConstForGame.h"
#include <memory.h>
#include "Controller.h"
#include "GameObjects/Sticks/BrokenStick.h"
#include "GameObjects/AnimationObject.h"
#include "Data/ImageAndAudio.h"
#include "GameObjects/Sticks/StaticStick.h"
#include <optional>
#include "GameObjects/Bullet.h"
#include "Animation/Animation.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

//this class if class of the player in the game

int Player::m_collectedCoin = 30;
Skin Player::m_wear = Skin::defaults;

//constractor
Player::Player(const sf::Vector2f loc, float moveSpeed)
	: AnimationObject(loc, ImageAndAudio::instance().animationData(ObjectsAnimation::Robot), Skin::defaults),
	m_moveSpeed( moveSpeed),m_upLimit(IMAGE_SIZE * 2.5), m_upPass(0),
	m_lose(false),m_passLevel(false)
{
	m_side = SideToMove::DOWN;
	srand(time(NULL));
	setOrigin(IMAGE_MIDDLE_PLAYER,0);
	m_prevWear = m_wear;
	setDirectionAnimation();

}

//----------------------------------------------------------------------------------
//draw player
void Player::draw(sf::RenderTarget& target) const
{
	target.draw(m_sprite);
}
//----------------------------------------------------------------------------------
//handle if player change move side
void Player::handlePlayerMoveSide()
{
	if (getLocation().x <= 10)
	{
		setPosition(sf::Vector2f(WINDOW_GAME_WIDTH, getLocation().y));
	}
	else if (getLocation().x >= WINDOW_GAME_WIDTH)
	{
		setPosition(sf::Vector2f(10, getLocation().y));
	}
}
//----------------------------------------------------------------------------------
//update player location from key press of user
void Player::updatePlayerLocation(const float deltaTime, sf::Time time)
{
	if (!getLose()) {
		handlePlayerMoveSide();
		if (m_upPass - IMAGE_MIDDLE * 3 > m_upLimit)
			m_upLimit = 0;
		if ((IMAGE_SIZE * 2.5) + IMAGE_MIDDLE < m_upPass)
		{
			m_side = SideToMove::DOWN;
			m_upPass = 0;
			m_animation.skin(m_prevWear);
		}
		else if (m_upLimit < m_upPass - IMAGE_MIDDLE * 2 || m_sprite.getPosition().y < 400)
		{
			m_side = SideToMove::NO_MOVE;
		}
		
		//go right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_directionLoc = sf::Vector2f(1, 0);
			updateBySide(SideToMove::RIGHT, deltaTime);
		}
		//go left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_directionLoc = sf::Vector2f(-1, 0);
			updateBySide(SideToMove::LEFT, deltaTime);
		}

		//go up
		if (m_side == SideToMove::UP)
		{
			m_upPass += m_moveSpeed * deltaTime;
			m_directionLoc = sf::Vector2f(0, -1);
			updateBySide(SideToMove::UP, deltaTime);
		}
		else if (m_side == SideToMove::NO_MOVE)
		{
			m_upPass += m_moveSpeed * deltaTime;
		}
		//go down
		else
		{
			m_directionLoc = sf::Vector2f(0, 1);
			updateBySide(SideToMove::DOWN, deltaTime);
		}
	}
	m_animation.update(time);

}
//----------------------------------------------------------------------------------
//move player
void Player::move(const float deltaTime, SideToMove side, sf::Time time)
{
	m_directionLoc = sf::Vector2f(0, 1);
	m_sprite.move(m_directionLoc * deltaTime);
	if (getLocation().x <= 0)
	{
		m_sprite.setPosition(sf::Vector2f(850, m_sprite.getPosition().y));
	}
}
//----------------------------------------------------------------------------------
//get count of coin
int Player::getcollectedCoin() const//get number of coin taken
{
	return m_collectedCoin;
}

//----------------------------------------------------------------------------------
//set how much need to go up
void Player::setUpLimit(float uplimit)
{
	m_upLimit = uplimit;
}

//----------------------------------------------------------------------------------
//set side of player
void Player::setSide(SideToMove side)
{
	m_side = side;
}
//----------------------------------------------------------------------------------
//set how much pass
void Player::setUpPass(float upPass)
{
	m_upPass = upPass;
}

//----------------------------------------------------------------------------------
//get side of player
SideToMove Player::getSide() const
{
	return m_side;
}
//----------------------------------------------------------------------------------
//set if player lose
void Player::setLose(bool iflose)
{
	m_lose = iflose;
}
//----------------------------------------------------------------------------------
//get if player lose
bool Player::getLose() const
{
	return m_lose;
}
//----------------------------------------------------------------------------------
//set lose way
void Player::setLoseWay(LoseWay loseWay)
{
	m_loseWay = loseWay;
}

//----------------------------------------------------------------------------------
//get lose way
LoseWay Player::getLoseWay()
{
	return m_loseWay;
}
//----------------------------------------------------------------------------------
//set if level pass- the player win
void Player::setLevelPass(bool ifwin)
{
	m_passLevel = ifwin;
}
//----------------------------------------------------------------------------------
//get if win
bool Player::getWin()const 
{
	return m_passLevel;
}
//fall if lose by monster
void Player::fall(const float deltaTime, sf::Time time)
{
	switch (m_loseWay)
	{
		case LoseWay::MONSTER:
			m_directionLoc = sf::Vector2f(0, 1);
			m_sprite.move(m_directionLoc * deltaTime);
			if (m_sprite.getPosition().y < WINDOW_GAME_HEIGHT)
			{

				m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 5));
				m_animation.update(time);
			}

			break;
		
		break;
	default:
		break;
	}

}
//----------------------------------------------------------------------------------
///set scale of player
void Player::setScale(float size)
{
	m_sprite.setScale(sf::Vector2f(size,size));
}
//----------------------------------------------------------------------------------
void Player::setDirectionAnimation()
{
	m_animation.skin(m_wear);
}
//----------------------------------------------------------------------------------
//get speed of player
float Player::getspeed()const
{
	return m_moveSpeed;
}
//----------------------------------------------------------------------------------
//update the texture side
void Player::updateBySide(const SideToMove side, const float deltaTime)
{
	switch (side)
	{
	case SideToMove::RIGHT:
	{
		changeSideSprite(SideToMove::RIGHT);
		m_directionLoc = sf::Vector2f(1.1, 0);
		m_sprite.move(m_directionLoc * (m_moveSpeed)*deltaTime);
		break;
	}
	case SideToMove::LEFT:
	{
		changeSideSprite(SideToMove::LEFT);
		m_directionLoc = sf::Vector2f(-1.1, 0);
		m_sprite.move(m_directionLoc * (m_moveSpeed)*deltaTime);

		break;
	}
	case SideToMove::UP:
	{
		m_directionLoc = sf::Vector2f(0, -1);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);

		break;
	}
	case SideToMove::DOWN:
	{
		m_directionLoc = sf::Vector2f(0, 1);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);
		break;
	}
	}
}
//----------------------------------------------------------------------------------s
//change side of sprite
void Player::changeSideSprite(SideToMove side)
{
	if (side == SideToMove::RIGHT)
	{
		m_sprite.setScale(-1, 1);
	}
	if (side == SideToMove::LEFT)
	{
		m_sprite.setScale(1, 1);
	}
}
//----------------------------------------------------------------------------------s
//set speed of the player
void Player::setSpeed(float speed)
{
	m_moveSpeed = speed;
}
