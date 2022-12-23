#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Data/HanldleFile.h"
#include "Menu.h"
#include "GameObjects/ObjectAbstract.h"
#include "GameObjects/Player.h"
#include "GameObjects/Bullet.h"
#include <memory>
#include "Data/DataOfGame.h"

using std::unique_ptr;
using std::vector;

/*this class is controller on the game*/

class Controller
{
public:
	Controller();//constructor
	void runGame();//run the game

private:
	int	 m_currLevel;		 //save curr level
	int m_score;			 //save the score of level
	bool m_ifInfinityMode;	 //to know what open
	HanldleFile m_handleFile;//get the level from board.txt
	DataOfGame m_dataFile;	 //get the level from board.txt 

	Menu m_menu;				  //menu of the game
	vector<sf::Text> m_text;	  //text show on screen
	sf::Sprite m_backgroundSprite;//background sprite
	sf::RenderWindow m_window;    //window
	unique_ptr<Player> m_player;  //player

	vector<unique_ptr<ObjectAbstract>>m_moveObject; //vector of object in the game.
	vector<unique_ptr<SpriteObject>>m_bullet;		 //vector of bullet in the game.
	

	void drawGame();	//draw the game.
	void loadText();	//load text in the window.
	void createWindow();//create window for the game.
	void GetLastData(); //get last saved data.
	void handleEvent(sf::Event event);//handle events 
	void handleCollisions(ObjectAbstract& obj);//handle collisions
	void loadLevelObject(sf::Clock& clockTimeLevel);//load curr level objects
	void playerMove(const float deltaTime, sf::Time time);//move player
	void objectMove(const float deltaTime, sf::Time time);//move objects
	bool infinteMode(sf::Clock clock, sf::Clock clockTimeLevel);//infinity play
	void createBullet(sf::Event event, sf::Vector2f startLoc);//create bullet
	void ObjectsGameRun(sf::Clock clock, sf::Clock clockTimeLevel);//run game.
	bool exeptionLoadObject(sf::Clock clock, sf::Clock clockTimeLevel);//exeption check
	
};