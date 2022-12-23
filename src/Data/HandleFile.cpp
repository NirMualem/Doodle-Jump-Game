#include<iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Data/HanldleFile.h"
#include "Data/Level.h"

#include "GameObjects/Player.h"
#include "GameObjects/Sticks/BrokenStick.h"
#include "GameObjects/Sticks/StaticStick.h"
#include "GameObjects/Sticks/MoveStick.h"
#include "GameObjects/Sticks/DisapperStick.h"
#include "GameObjects/Sticks/endLevelStick.h"

#include "GameObjects/AnimationObject.h"
#include "GameObjects/SpriteObject.h"
#include "GameObjects/Coin.h"
#include "GameObjects/Jetpack.h"
#include "GameObjects/Spring.h"
#include "GameObjects/ProgressBar.h"

#include "GameObjects/Enemies/EnemyMonster.h"
#include "GameObjects/Enemies/EnemySpaceship.h"
#include "GameObjects/Enemies/EnemyHole.h"
#include "GameObjects/Enemies/EnemyMonster.h"

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::make_unique;

/*
this class we create the board of the game for each level
save the file to read the levels.
members description in the board header file.
*/

//in the oo1_ex05 folder.
const string NAME_OF_FILE_DATA = "..\\..\\..\\Board.txt";
const  string NAME_INFINITY_FILE = "..\\..\\..\\Infinity.txt";

//----------------------------------------------------------------------------------
//constractor
HanldleFile::HanldleFile()
{
	m_fileOfLevels.open(NAME_OF_FILE_DATA);
	m_fileOfInfinity.open(NAME_INFINITY_FILE);
	if (m_fileOfLevels.fail() || m_fileOfInfinity.fail())
	{
		closeFileOfLevels();
	}
	else
	{
		loadFromFile(m_fileOfLevels,m_levels);
		loadFromFile(m_fileOfInfinity, m_infinityPartOfGame);
	}
	closeFileOfLevels();

}
//----------------------------------------------------------------------------------
//this function update all the locations 
void HanldleFile::loadFromFile(fstream& file, vector<Level> &levels)
{
	char symbol = ' ';
	int rows = 0;
	vector <string> levelChars;
	string line;

 	while (!file.eof())
	{
		getline(file, line);
		rows = 0;
		//go over the map and update with get line
		while (line != "end")
		{
			getline(file, line);
			if (line[0] != 'e' && line.size() < OBJECT_LEVEL_IN_ROW)
				while (line.size() < OBJECT_LEVEL_IN_ROW + 1)
					line.append(" ");
			levelChars.push_back(line);
			rows++;
		}
		getline(file, line);
		Level level(rows - 1, levelChars);
		levelChars.clear();
		levels.push_back(level);
	}
	getline(file, line);
}
//----------------------------------------------------------------------------------
//get levels in the game
vector<Level> HanldleFile::getLevels() const
{
	return m_levels;
}
//----------------------------------------------------------------------------------
//get parts of levels for the infinity mode
vector <Level> HanldleFile::getPartOfLevel() const
{
	return m_infinityPartOfGame;
}
//close file in the end of the game
void HanldleFile::closeFileOfLevels()
{
	m_fileOfLevels.close();
	m_fileOfInfinity.close();
}


//----------------------------------------------------------------------------------
//load curr level objects
void HanldleFile::loadObjects(sf::Clock& clockTimeLevel,int score, bool isinfinity,int currLevel, vector<unique_ptr<ObjectAbstract>>& move_object)
{
	int real_row, row, width, randomPart, infinityContinue;
	if (!isinfinity)
	{
		infinityContinue = 0;
		real_row = getLevels()[currLevel].getHight() - 20;
		row = getLevels()[currLevel].getHight() - 1;
	}
	else
	{
		if (move_object.size() == 0)
		{
			infinityContinue = 0;
			randomPart = 0;
		}
		else
		{
			infinityContinue = move_object[move_object.size() - 1]->getLocation().y - WINDOW_GAME_HEIGHT;

			if (score < 2000 || score >5000)
				randomPart = rand() % m_infinityPartOfGame.size();
			else
				randomPart = rand() % 4 + 7;
		}

		real_row = getPartOfLevel()[randomPart].getHight() - 20;
		row = getPartOfLevel()[randomPart].getHight() - 1;
	}

	for (; row >= 0; row--)
	{
		for (int col = 0; col < OBJECT_LEVEL_IN_ROW; col++)
		{
			char charToCheck;
			if (!isinfinity)
			{
				charToCheck = getLevels()[currLevel].getCharLevel()[row][col];
				move_object.push_back(make_unique <ProgressBar>(sf::Vector2f(WINDOW_GAME_WIDTH - 16, 50), (getLevels()[currLevel].getHight()) * IMAGE_SIZE_HEIGHT));
			}
			else
			{
				charToCheck = getPartOfLevel()[randomPart].getCharLevel()[row][col];
			}
			switch (charToCheck)
			{
			case SPACE_CHAR:
			{
				break;
			}
			case STATIC_STICK_CHAR:
			{
				move_object.push_back(
					make_unique<StaticStick>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case BROKEN_STICK_CHAR:
			{
				move_object.push_back(
					make_unique <BrokenStick>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case MOVE_STICK_CHAR:
			{
				move_object.push_back(
					make_unique <MoveStick>(sf::Vector2f(450, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case DISAPPEAR_STICK_CHAR:
			{
				move_object.push_back(
					make_unique <DisappearStick>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case MONSTER_CHAR:
			{
				move_object.push_back(
					make_unique <EnemyMonster>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case SPACESHIP_CHAR:
			{
				move_object.push_back(
					make_unique <EnemySpaceship>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case HOLE_CHAR:
			{
				move_object.push_back(
					make_unique <EnemyHole>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case COIN_CHAR:
			{
				move_object.push_back(
					make_unique <Coin>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE, (row - real_row) * IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case SPRING_CHAR:
			{
				int rand_loc = rand() % (IMAGE_SIZE_WIDTH - IMAGE_SIZE_MIDDLE);
				move_object.push_back(
					make_unique <Spring>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE + rand_loc, ((row - real_row) + 1) * IMAGE_SIZE_HEIGHT - IMAGE_SIZE_HEIGHT + infinityContinue)));
				break;
			}
			case JETPACK_CHAR:
			{
				int rand_loc = rand() % (IMAGE_SIZE_WIDTH - IMAGE_SIZE_MIDDLE);
				move_object.push_back(
					make_unique <Jetpack>(sf::Vector2f((col * IMAGE_SIZE_WIDTH) + IMAGE_SIZE_MIDDLE + rand_loc, ((row - real_row) + 1) * IMAGE_SIZE_HEIGHT - IMAGE_SIZE_HEIGHT * 1.5 + infinityContinue)));
				break;
			}
			default:
				throw std::invalid_argument ( "char in file is wrong " );
			}
		}
	}
	if (!isinfinity)
	{
		move_object.push_back(make_unique <EndLevelStick>(sf::Vector2f(150, (row - real_row - 3) * (IMAGE_SIZE_HEIGHT))));
	}
}
