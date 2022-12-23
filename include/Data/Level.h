#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using std::string;
using std::vector;

//this class is level in the game 
class Level
{
public:
	Level(const int hight , const vector<string> objectOfLevel);//constractor
	int getHight()const;//get height
	vector <string> getCharLevel()const;//get chars of level

private:
	int m_hight;//height of level
	vector<string> m_objectOfLevel;//vector of the levels
};



