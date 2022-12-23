#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "Data/ConstForGame.h"

using std::vector;
using std::ifstream;
using std::string;
using std::array;
using std::fstream;
using std::pair;

/*
this class is the file of the level in the game
*/
class DataOfGame
{
	//public function

public:
	DataOfGame();//constractor
	void closeFile();//close file
	void loadFromFile();//load data from file
	void updateFile(const int coinNumber, const int score, const int level,
		const  vector<int> skins, array<pair<int, string>, HIGH_SCORE_PLAYERS> infinityScore);//update file before exit
	array<pair<int, string>, HIGH_SCORE_PLAYERS> getscoreInfinity()const;//scores in infinity mode
	int getscoreLevel()const;//score of level
	int getLevel()const;//get last level
	int getCoinNumber()const;//get coin
	vector<int> getSkins()const;//get skins that the user buy

	//private members and function
private:
	fstream m_fileOfData;//file to read data
	int m_coinNumber;//coin
	int m_scoreHighLevel;//score
	int m_level;//level
	vector<int> m_skin;//skins
	array<pair<int, string> , HIGH_SCORE_PLAYERS> m_infinityHighScore;//score infinity top 10
};


