#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Level.h"
#include "GameObjects/ObjectAbstract.h"

using std::vector;
using std::ifstream;
using std::string;
using std::fstream;
using std::unique_ptr;
/*
this class is the file of the level in the game
*/
class HanldleFile
{
	//public function

public:
	HanldleFile();			//constractor
	void closeFileOfLevels();//close the files
	void loadFromFile(fstream &m_file, vector<Level>& levels);//load chars from file
	vector<Level> getLevels() const;						  //get levels
	vector<Level> getPartOfLevel() const;					  //get parts of infinity mode
	void loadObjects(sf::Clock& clockTimeLevel,int score, bool isinfinity, int currLevel,
						vector<unique_ptr<ObjectAbstract>>& move_object);//load objects for game.
	
	//private members and function
private:
	vector<Level> m_levels;				//levels
	vector<Level> m_infinityPartOfGame; //parts of infinity
	fstream m_fileOfLevels;				//file to read level
	fstream m_fileOfInfinity;			//file to read part of infinity game
};


