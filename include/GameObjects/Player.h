#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory.h>
#include <vector>
#include "AnimationObject.h"
#include "Bullet.h"
#include "Data/Enums.h"
#include "Animation/Animation.h"

using std::vector;
using std::unique_ptr;

//this class if class of the player in the game

class Player : public AnimationObject
{
public:
	Player(const sf::Vector2f loc,  float moveSpeed);
	virtual ~Player() = default;

	static Skin m_wear;//skin of the player

	int getcollectedCoin() const;//how much coin the player have
	void setLose(bool iflose);//set if the player lose
	bool getLose()const ;//get if lose or not
	void setLevelPass(bool ifwin);//set level if pass
	bool getWin()const;//get if pass the level
	void fall(const float deltaTime, sf::Time time);//if the player lose and need to fall update location
	void updateBySide(const SideToMove side, const float deltaTime);//update the side of the sprite
	void changeSideSprite(SideToMove side);//chage side sprite
	void handlePlayerMoveSide();//move player to the other side
	void updatePlayerLocation(const float deltaTime,  sf::Time time);//update the location
	SideToMove getSide() const;//get side of the move object
	void draw(sf::RenderTarget& target) const;//draw the player
	float getspeed()const;//get speed of player
	void setSpeed(float speed);//set speed of player

	virtual void move(const float deltaTime, SideToMove side, sf::Time time );//move player
	void setUpLimit(float uplimit);//set up limit
	void setSide(SideToMove m_side);//set side of player
	void setUpPass(float upPass);//set up pass
	static int m_collectedCoin;//count of coin 
	void setScale(float size);//set scale of player
	void setLoseWay(LoseWay loseWay);//set lose way of player
	LoseWay getLoseWay();//get lose way of player
	void setDirectionAnimation();//set direction of the animatoins

private:
	float m_upLimit;//how much need to go up
	float m_moveSpeed;//move speed of the object
	float m_upPass;//how much pass
	SideToMove m_side;//side of player
	Skin m_prevWear;//the prev skin
	bool m_passLevel;//if pass the curr level
	bool m_lose;//if lose
	LoseWay m_loseWay;//way of lose 
};