#pragma once
#include <vector>
#include <experimental/vector>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <memory.h>
#include "Controller.h"
#include "Data/HanldleFile.h"
#include "Data/ConstForGame.h"
#include "Data/Enums.h"
#include "Menu.h"
#include "Data/ImageAndAudio.h"
#include <time.h>
#include "CollisionHandling.h"
#include "GameObjects/Player.h"
#include <fstream>
#include <exception>
using std::vector;
using std::make_unique;

int Menu::m_currHighlightLevel = 0;

const string NAME_OF_FILE_LOG = "..\\..\\..\\log.txt";

Controller::Controller()
	:m_window(),m_backgroundSprite(sf::Sprite()),m_currLevel(0),m_ifInfinityMode(false)
{

	srand(time(NULL));
	loadText();
	GetLastData();
	m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(PicChoose::GAME ,BACKGROUND_GAME));
}
//----------------------------------------------------------------------------------
//this function main function to run the game.
void Controller::runGame()
{	
	std::ofstream out(NAME_OF_FILE_LOG, std::fstream::out | std::ofstream::trunc);
	std::cout.rdbuf(out.rdbuf());//change output to log file

	ImageAndAudio::instance().playSound(Sound::GAME_MUSIC);

	sf::Clock clock;
	sf::Clock clockTimeLevel;
	float deltaTime = 0;
	auto delta = clock.restart();

	//while user not close the window, run
	while (true)
	{
		m_menu.openMenu(); //open menu
		m_currLevel = m_menu.getSelectLevel();//get select level
		if(m_currLevel == Operate::EXIT)//exit
			break;
		else if (m_currLevel == Operate::INFINITY_GAME)//if infinity mode
		{
			m_ifInfinityMode = true;
			if(infinteMode(clock, clockTimeLevel))
			{
				m_dataFile.closeFile();
				return;
			}
		}
		else
		{
			m_ifInfinityMode = false;
			m_currLevel--;
			if (exeptionLoadObject(clock, clockTimeLevel))
			{
				m_dataFile.closeFile();
				return;
			}
		}
		if (m_ifInfinityMode)
			m_menu.updateScoreChar(m_score);
	}
	m_dataFile.updateFile(m_player->m_collectedCoin, m_score, m_menu.getLastOpenLevel(), m_menu.getBoutSkins(), m_menu.getscoreInfinity());
	m_dataFile.closeFile();
}
//----------------------------------------------------------------------------------
//handle event from user.
void Controller::handleEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	//mouse click to shot.
	case sf::Event::MouseButtonReleased:
		if(event.type)
			createBullet(event , sf::Vector2f(m_player->getLocation().x, m_player->getLocation().y));
		break;
	}
}
//----------------------------------------------------------------------------------
//move player
void Controller::playerMove(const float deltaTime, sf::Time time)
{
	if (!m_player->getLose())//while the player not lose update location
		m_player->updatePlayerLocation(deltaTime,time);

	if (m_player->getSide() == SideToMove::NO_MOVE)
		if (m_score >= MAX_SCORE)
				m_score = MAX_SCORE;
		else
				m_score += m_player->getspeed() * deltaTime /2;

	handleCollisions(*m_player);

	if (m_player->getLose())
	{
		m_player->setLevelPass(false);
		if (m_player->getLoseWay() == LoseWay::MONSTER)
		{
			m_player->fall(deltaTime , time);
		}
	}
}
//----------------------------------------------------------------------------------
//handle collision player with objects ans bullets with object
void Controller::handleCollisions(ObjectAbstract& obj)
{
	for (auto& movable : m_moveObject)
	{
		if (movable->getLocation().y < 0)
			break;

		if (obj.checkCollision(movable->getsprite().getGlobalBounds()))
		{
				processCollision(obj, *movable);
		}
	}
	std::experimental::erase_if(m_moveObject, [](unique_ptr <ObjectAbstract>& movable)
		{
			return movable->checkIfDelete();//erase static object taken by player
		});

	std::experimental::erase_if(m_bullet, [](unique_ptr <SpriteObject>& movable)
		{
			return movable->checkIfDelete();//erase bullet taken by object
		});
}
//----------------------------------------------------------------------------------
//run game when click on play 
void Controller::ObjectsGameRun(sf::Clock clock, sf::Clock clockTimeLevel)
{
	float deltaTime = 0;
	auto delta = clock.restart();

	loadLevelObject(clockTimeLevel);

	delta = clock.restart();
	deltaTime = delta.asSeconds();

	createWindow();
	clockTimeLevel.restart();
	sf::Event event;
	while (m_window.isOpen())
	{
		while (!m_player->getLose() && m_window.pollEvent(event))
		{
			handleEvent(event);
		}

		if (m_ifInfinityMode && m_moveObject[m_moveObject.size() - 1]->getLocation().y > -WINDOW_GAME_HEIGHT)
		{
			loadLevelObject(clockTimeLevel);
		}

		delta = clock.restart();
		deltaTime = delta.asSeconds();
		playerMove(deltaTime, delta);
		if (m_player->getWin())
		{
			m_menu.updateButtonLevel(m_currLevel + 1);
			m_player->setLevelPass(false);
			Sleep(1000);
			m_window.close();
		}
		if (m_player->getLocation().y >= WINDOW_GAME_HEIGHT)
		{
			Sleep(1000);
			m_window.close();
		}
		objectMove(deltaTime, delta);
		drawGame();
	}
}

//----------------------------------------------------------------------------------
//try catch load object
bool Controller::exeptionLoadObject(sf::Clock clock, sf::Clock clockTimeLevel)
{
	try {
		ObjectsGameRun(clock, clockTimeLevel);
	}
	catch (std::invalid_argument)
	{
		if(m_ifInfinityMode)
			std::cout << "char in infinity not exist. , fix infinity file \n";
		else
			std::cout << "char in level " << m_currLevel+1 << " not exist.  , fix board file\n";
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------
//infinity mode
bool Controller::infinteMode(sf::Clock clock,sf::Clock clockTimeLevel)
{
	m_moveObject.clear();
	m_bullet.clear();
	clockTimeLevel.restart();
	m_score = 0;

	m_player = make_unique<Player>(sf::Vector2f(450, 800), 350.f);
	if (exeptionLoadObject(clock, clockTimeLevel))
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------
//create bullet
void Controller::createBullet(sf::Event event , sf::Vector2f startLoc)
{

	if (event.mouseButton.button != sf::Mouse::Right && event.mouseButton.button != sf::Mouse::Left || m_bullet.size() > 1)
		return;

	if (event.mouseButton.y < startLoc.y)
	{
		sf::Vector2f mouse_loc(event.mouseButton.x, event.mouseButton.y);
		m_bullet.push_back(make_unique<Bullet>(startLoc, mouse_loc));
	}
}
//----------------------------------------------------------------------------------
//move objects
void Controller::objectMove(const float deltaTime, sf::Time time)
{
	for (auto& movable : m_moveObject)
	{
		movable->move(deltaTime * m_player->getspeed(), m_player->getSide(), time);
		if (movable->getLocation().y + IMAGE_SIZE_HEIGHT / 2 > WINDOW_GAME_HEIGHT)	
				movable->setIfDeleted(true);		
	}
	for (auto& bullet : m_bullet)
	{
		if (bullet != nullptr)
		{
			bullet->move(deltaTime * m_player->getspeed(), m_player->getSide(),time);
			if (bullet->getLocation().x < 0 || bullet->getLocation().x > WINDOW_GAME_WIDTH || bullet->getLocation().y + IMAGE_SIZE_HEIGHT * 3 < 0 || bullet->getLocation().y + IMAGE_SIZE_HEIGHT / 2 > WINDOW_GAME_HEIGHT)
				bullet->setIfDeleted(true);
			handleCollisions(*bullet);
		}
	}
}
//----------------------------------------------------------------------------------
//draw all
void Controller::drawGame()
{
	m_window.clear();
	m_window.draw(m_backgroundSprite);
	
	for (int i = 0; i < m_moveObject.size() ; i++)
	{
		if (m_moveObject[i]->getLocation().y +IMAGE_SIZE_HEIGHT * 3 < 0)
			break;
		m_moveObject[i]->draw(m_window);
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		if (m_bullet[i]->getLocation().y + IMAGE_SIZE_HEIGHT * 3 < 0)
			break;
		m_bullet[i]->draw(m_window);
	}

	m_text[1].setString(std::to_string(m_score));

	for (int i = 0; i < m_text.size(); i++)
	{
		m_window.draw(m_text[i]);
	}
	m_player->draw(m_window);

	m_window.display();
}
//----------------------------------------------------------------------------------
//create window
void Controller::createWindow()
{
	m_window.create(sf::VideoMode(WINDOW_GAME_WIDTH,WINDOW_GAME_HEIGHT), "Jump Jump", sf::Style::Titlebar | sf::Style::Close);
	m_window.setPosition(sf::Vector2i(m_window.getPosition().x, 0));
	m_window.setFramerateLimit(60);
	m_window.clear();
	drawGame();
	m_window.display();
}
//----------------------------------------------------------------------------------
//load curr level objects or part of level for infinity
void Controller::loadLevelObject(sf::Clock& clockTimeLevel)
{
	if (!m_ifInfinityMode)
	{
		m_moveObject.clear();
		m_bullet.clear();
		clockTimeLevel.restart();
		m_score = 0;
		m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(PicChoose::GAME, int(m_currLevel)));
		m_player = make_unique<Player>(sf::Vector2f(450, 800), 350.f);
	}
	else
	{
		if (m_score > 2000)
		{
			m_player->setSpeed(400.f);
		}
		m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(PicChoose::GAME, BACKGROUND_GAME));
	}
	m_handleFile.loadObjects(clockTimeLevel,m_score, m_ifInfinityMode, m_currLevel, m_moveObject);
}
//----------------------------------------------------------------------------------
//this function load the picture once to use in other places.
void Controller::loadText()
{
	m_text.push_back(sf::Text("score", *ImageAndAudio::instance().getFont(), 34));
	m_text[0].setPosition(sf::Vector2f(WINDOW_GAME_WIDTH - 130 , 20));
	m_text[0].setColor(sf::Color(255,255,168));

	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(),40));
	m_text[1].setPosition(sf::Vector2f(WINDOW_GAME_WIDTH - 130, 50));
	m_text[1].setColor(sf::Color(255, 255, 168));
}
//----------------------------------------------------------------------------------
//get last data.
void Controller::GetLastData()
{
	m_player->m_collectedCoin = m_dataFile.getCoinNumber();
	m_currLevel = m_dataFile.getLevel();
	m_score = m_dataFile.getscoreLevel();

	for (int i = 0; i < m_currLevel; i++)
	{
		m_menu.updateButtonLevel(i);
	}

	m_menu.updateSkins(m_dataFile.getSkins());
	m_menu.updateInfinityHighScore(m_dataFile.getscoreInfinity());
}
