#include <SFML/Graphics.hpp>
#include "Data/Level.h"

// 
Level::Level(const int hight,  const vector<string> objectOfLevel)
	: m_hight(hight), m_objectOfLevel(objectOfLevel)
{
}

//----------------------------------------------------------------------------------
//height of level
int Level::getHight()const
{
	return m_hight;
}
//----------------------------------------------------------------------------------
//get char of level
vector <string> Level::getCharLevel()const
{
	return m_objectOfLevel;
}
