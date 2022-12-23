#include<iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Data/DataOfGame.h"
#include "Data/ConstForGame.h"
#include <vector>
#include <sstream>


using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::ios;
using std::vector;
using std::stringstream;
/*
this class we save the file to read the data from the last play.
*/

const string NAME_OF_FILE_DATA = "..\\..\\..\\data.txt";

//constractor
DataOfGame::DataOfGame()
{
	m_fileOfData.open(NAME_OF_FILE_DATA, std::ios::in | std::ios::out);
	if (m_fileOfData.fail())
	{
		closeFile();
	}
	else
	{
		loadFromFile();
	}
}
//----------------------------------------------------------------------------------
//this function update all the locations of the player enemy and coins
void DataOfGame::loadFromFile()
{
	string line;

	m_fileOfData >> m_coinNumber;
	m_fileOfData >> m_level;
	m_fileOfData >> m_scoreHighLevel;
	m_fileOfData.get();
	getline(m_fileOfData, line);
	stringstream numbers(line);
	int num;
	while (numbers >> num)
	{
		m_skin.push_back(num);
	}
	for (int i = 0; i < HIGH_SCORE_PLAYERS; i++)
	{
		m_fileOfData >> m_infinityHighScore[i].first >> m_infinityHighScore[i].second;
	}
}
//----------------------------------------------------------------------------------
vector<int> DataOfGame::getSkins()const
{
	return m_skin;
}

//----------------------------------------------------------------------------------
int DataOfGame::getCoinNumber()const
{
	return m_coinNumber;

}
//----------------------------------------------------------------------------------
int DataOfGame::getLevel()const
{
	return m_level;
}
//----------------------------------------------------------------------------------
int DataOfGame::getscoreLevel()const
{
	return m_scoreHighLevel;

}
//----------------------------------------------------------------------------------
array<pair<int, string>, HIGH_SCORE_PLAYERS> DataOfGame::getscoreInfinity()const
{
	return m_infinityHighScore;
}
//----------------------------------------------------------------------------------
//this function update the file data
void DataOfGame::updateFile(const int coinNumber, const int score
							, const int level, const  vector<int> skins , array<pair<int, string>, HIGH_SCORE_PLAYERS> infinityScore)
{
	m_fileOfData.close();
	m_fileOfData.open(NAME_OF_FILE_DATA, ios::out | ios::trunc);
	if (m_fileOfData.is_open())
	{
		m_fileOfData << coinNumber << endl;
		m_fileOfData << level << endl;
		m_fileOfData << score << endl;

		for (int i = 0; i < skins.size(); i++)
		{
			m_fileOfData << skins[i] <<" ";
		}
		m_fileOfData << endl;
		m_fileOfData.flush();

		for (int i = 0; i < HIGH_SCORE_PLAYERS; i++)
		{
			m_fileOfData << infinityScore[i].first << " " << infinityScore[i].second << " ";
		}
		m_fileOfData.flush();
	}
	closeFile();
	
}
//----------------------------------------------------------------------------------
//close file in the end of the game
void DataOfGame::closeFile()
{
	m_fileOfData.close();
}