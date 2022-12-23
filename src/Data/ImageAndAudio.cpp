#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Data/Enums.h"
#include "Menu.h"
#include "Data/ImageAndAudio.h"
#include "Data/ConstForGame.h"
#include <fstream>
#include <vector>

using std::vector;

const int START_ENDSTICKS_POINT = 1847;
const int BLACK_HOLE_POINT = 966;

ImageAndAudio::ImageAndAudio() : m_data(Max)
{

	if (!m_texture.loadFromFile("animations.png"))
	{
		throw std::runtime_error("Can't load file");
	}

	m_data[ObjectsAnimation::Robot] = robotData();
	m_data[ObjectsAnimation::Monster] = monsterData();
	m_data[ObjectsAnimation::EndStick] = endStickData();
	m_data[ObjectsAnimation::Hole] = HoleData();
	m_data[ObjectsAnimation::Springs] = SpringData();

	sticksData();

	loadPictures();
	m_font.loadFromFile("font.TTF");
	loadAudio();

}

ImageAndAudio& ImageAndAudio::instance() {
	static ImageAndAudio inst;
	return inst;
}

//this function load the picture once to use in other places.
void ImageAndAudio::loadPictures()
{

	m_gameImage.clear();
	m_menuImage.clear();
	m_LevelImage.clear();
	m_shopImage.clear();

	loadGamePic();
	loadMenuPic();
	loadLevelPic();
	loadShopPic();
}
const sf::Texture& ImageAndAudio::texture() const
{
	return m_texture;
}
//----------------------------------------------------------------------------------
const AnimationData& ImageAndAudio::animationData(ObjectsAnimation object)const
{
	return m_data[object];
}
//----------------------------------------------------------------------------------
AnimationData ImageAndAudio::robotData()
{
	auto size = sf::Vector2i(PLAYER_WIDTH, PLAYER_HEIGHT);
	auto initSpace = sf::Vector2i(1, 1);
	auto middleSpace = sf::Vector2i(0, 1);
	int i = 1;
	auto Robot = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.y += size.y;
		return currentStart;
	};

	Robot.m_data[Skin::defaults].emplace_back(initSpace, size);
	Robot.m_data[Skin::defaults].emplace_back(nextStart(), size);
	Robot.m_data[Skin::defaults].emplace_back(nextStart(), size);
	Robot.m_data[Skin::defaults].emplace_back(nextStart(), size);
	Robot.m_data[Skin::defaults].emplace_back(nextStart(), size);
	Robot.m_data[Skin::defaults].emplace_back(Robot.m_data[Skin::defaults][3]);
	Robot.m_data[Skin::defaults].emplace_back(Robot.m_data[Skin::defaults][2]);
	Robot.m_data[Skin::defaults].emplace_back(Robot.m_data[Skin::defaults][1]);
	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 2, 1);
	i++;
	currentStart = initSpace;


	Robot.m_data[Skin::tie].emplace_back(initSpace, size);
	Robot.m_data[Skin::tie].emplace_back(nextStart(), size);
	Robot.m_data[Skin::tie].emplace_back(nextStart(), size);
	Robot.m_data[Skin::tie].emplace_back(nextStart(), size);
	Robot.m_data[Skin::tie].emplace_back(nextStart(), size);
	Robot.m_data[Skin::tie].emplace_back(Robot.m_data[Skin::tie][3]);
	Robot.m_data[Skin::tie].emplace_back(Robot.m_data[Skin::tie][2]);
	Robot.m_data[Skin::tie].emplace_back(Robot.m_data[Skin::tie][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 3, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::confuse].emplace_back(initSpace, size);
	Robot.m_data[Skin::confuse].emplace_back(nextStart(), size);
	Robot.m_data[Skin::confuse].emplace_back(nextStart(), size);
	Robot.m_data[Skin::confuse].emplace_back(nextStart(), size);
	Robot.m_data[Skin::confuse].emplace_back(nextStart(), size);
	Robot.m_data[Skin::confuse].emplace_back(Robot.m_data[Skin::confuse][3]);
	Robot.m_data[Skin::confuse].emplace_back(Robot.m_data[Skin::confuse][2]);
	Robot.m_data[Skin::confuse].emplace_back(Robot.m_data[Skin::confuse][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 4, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::cape].emplace_back(initSpace, size);
	Robot.m_data[Skin::cape].emplace_back(nextStart(), size);
	Robot.m_data[Skin::cape].emplace_back(nextStart(), size);
	Robot.m_data[Skin::cape].emplace_back(nextStart(), size);
	Robot.m_data[Skin::cape].emplace_back(nextStart(), size);
	Robot.m_data[Skin::cape].emplace_back(Robot.m_data[Skin::cape][3]);
	Robot.m_data[Skin::cape].emplace_back(Robot.m_data[Skin::cape][2]);
	Robot.m_data[Skin::cape].emplace_back(Robot.m_data[Skin::cape][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 5, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::heart].emplace_back(initSpace, size);
	Robot.m_data[Skin::heart].emplace_back(nextStart(), size);
	Robot.m_data[Skin::heart].emplace_back(nextStart(), size);
	Robot.m_data[Skin::heart].emplace_back(nextStart(), size);
	Robot.m_data[Skin::heart].emplace_back(nextStart(), size);
	Robot.m_data[Skin::heart].emplace_back(Robot.m_data[Skin::heart][3]);
	Robot.m_data[Skin::heart].emplace_back(Robot.m_data[Skin::heart][2]);
	Robot.m_data[Skin::heart].emplace_back(Robot.m_data[Skin::heart][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 6, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::work].emplace_back(initSpace, size);
	Robot.m_data[Skin::work].emplace_back(nextStart(), size);
	Robot.m_data[Skin::work].emplace_back(nextStart(), size);
	Robot.m_data[Skin::work].emplace_back(nextStart(), size);
	Robot.m_data[Skin::work].emplace_back(nextStart(), size);
	Robot.m_data[Skin::work].emplace_back(Robot.m_data[Skin::work][3]);
	Robot.m_data[Skin::work].emplace_back(Robot.m_data[Skin::work][2]);
	Robot.m_data[Skin::work].emplace_back(Robot.m_data[Skin::work][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 5, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::jetpack].emplace_back(initSpace, size);
	Robot.m_data[Skin::jetpack].emplace_back(nextStart(), size);
	Robot.m_data[Skin::jetpack].emplace_back(nextStart(), size);
	Robot.m_data[Skin::jetpack].emplace_back(nextStart(), size);
	Robot.m_data[Skin::jetpack].emplace_back(nextStart(), size);
	Robot.m_data[Skin::jetpack].emplace_back(Robot.m_data[Skin::jetpack][3]);
	Robot.m_data[Skin::jetpack].emplace_back(Robot.m_data[Skin::jetpack][2]);
	Robot.m_data[Skin::jetpack].emplace_back(Robot.m_data[Skin::jetpack][1]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 8, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::dead].emplace_back(initSpace, size);
	Robot.m_data[Skin::dead].emplace_back(nextStart(), size);
	Robot.m_data[Skin::dead].emplace_back(nextStart(), size);
	Robot.m_data[Skin::dead].emplace_back(nextStart(), size);
	Robot.m_data[Skin::dead].emplace_back(nextStart(), size);
	Robot.m_data[Skin::dead].emplace_back(Robot.m_data[Skin::dead][0]);
	Robot.m_data[Skin::dead].emplace_back(Robot.m_data[Skin::dead][1]);
	Robot.m_data[Skin::dead].emplace_back(Robot.m_data[Skin::dead][2]);
	Robot.m_data[Skin::dead].emplace_back(Robot.m_data[Skin::dead][3]);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 9, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::umbrella].emplace_back(initSpace, size);
	Robot.m_data[Skin::umbrella].emplace_back(nextStart(), size);
	Robot.m_data[Skin::umbrella].emplace_back(nextStart(), size);
	Robot.m_data[Skin::umbrella].emplace_back(nextStart(), size);
	Robot.m_data[Skin::umbrella].emplace_back(nextStart(), size);

	initSpace = sf::Vector2i(PLAYER_WIDTH * i + 10, 1);
	i++;
	currentStart = initSpace;

	Robot.m_data[Skin::shield].emplace_back(initSpace, size);
	Robot.m_data[Skin::shield].emplace_back(nextStart(), size);
	Robot.m_data[Skin::shield].emplace_back(nextStart(), size);
	Robot.m_data[Skin::shield].emplace_back(nextStart(), size);
	Robot.m_data[Skin::shield].emplace_back(nextStart(), size);

	return Robot;
}
//----------------------------------------------------------------------------------
//monster data
AnimationData ImageAndAudio::monsterData()
{
	int i = 1;
	const int  monster_width = 118;
	auto size = sf::Vector2i(118, 138);
	auto initSpace = sf::Vector2i(1, 1111);
	auto middleSpace = sf::Vector2i(0, 1);

	auto monster = AnimationData{};
	auto currentStart = initSpace;
	
	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.y += size.y;
		return currentStart;
	};

	monster.m_data[Skin::Level1].emplace_back(initSpace, size);
	monster.m_data[Skin::Level1].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level1].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level1].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level1].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level1].emplace_back(monster.m_data[Skin::Level1][3]);
	monster.m_data[Skin::Level1].emplace_back(monster.m_data[Skin::Level1][2]);
	monster.m_data[Skin::Level1].emplace_back(monster.m_data[Skin::Level1][1]);

	initSpace = sf::Vector2i(1, 1111);
	currentStart = initSpace;

	monster.m_data[Skin::Infinity].emplace_back(initSpace, size);
	monster.m_data[Skin::Infinity].emplace_back(nextStart(), size);
	monster.m_data[Skin::Infinity].emplace_back(nextStart(), size);
	monster.m_data[Skin::Infinity].emplace_back(nextStart(), size);
	monster.m_data[Skin::Infinity].emplace_back(nextStart(), size);
	monster.m_data[Skin::Infinity].emplace_back(monster.m_data[Skin::Infinity][3]);
	monster.m_data[Skin::Infinity].emplace_back(monster.m_data[Skin::Infinity][2]);
	monster.m_data[Skin::Infinity].emplace_back(monster.m_data[Skin::Infinity][1]);
	initSpace = sf::Vector2i(monster_width * i + 2, 1111);
	i++;
	currentStart = initSpace;

	monster.m_data[Skin::Level2].emplace_back(initSpace, size);
	monster.m_data[Skin::Level2].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level2].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level2].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level2].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level2].emplace_back(monster.m_data[Skin::Level2][3]);
	monster.m_data[Skin::Level2].emplace_back(monster.m_data[Skin::Level2][2]);
	monster.m_data[Skin::Level2].emplace_back(monster.m_data[Skin::Level2][1]);

	initSpace = sf::Vector2i(monster_width * i + 3, 1111);
	i++;
	currentStart = initSpace;

	monster.m_data[Skin::Level3].emplace_back(initSpace, size);
	monster.m_data[Skin::Level3].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level3].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level3].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level3].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level3].emplace_back(monster.m_data[Skin::Level3][3]);
	monster.m_data[Skin::Level3].emplace_back(monster.m_data[Skin::Level3][2]);
	monster.m_data[Skin::Level3].emplace_back(monster.m_data[Skin::Level3][1]);

	initSpace = sf::Vector2i(monster_width * i + 4, 1111);
	i++;
	currentStart = initSpace;

	monster.m_data[Skin::Level4].emplace_back(initSpace, size);
	monster.m_data[Skin::Level4].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level4].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level4].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level4].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level4].emplace_back(monster.m_data[Skin::Level4][3]);
	monster.m_data[Skin::Level4].emplace_back(monster.m_data[Skin::Level4][2]);
	monster.m_data[Skin::Level4].emplace_back(monster.m_data[Skin::Level4][1]);

	initSpace = sf::Vector2i(monster_width * i + 5, 1111);
	i++;
	currentStart = initSpace;

	monster.m_data[Skin::Level5].emplace_back(initSpace, size);
	monster.m_data[Skin::Level5].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level5].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level5].emplace_back(nextStart(), size);
	monster.m_data[Skin::Level5].emplace_back(nextStart(), size);


	return monster;
}
//----------------------------------------------------------------------------------
//hole data
AnimationData ImageAndAudio::HoleData()
{
	auto size = sf::Vector2i(85, 85);
	auto initSpace = sf::Vector2i(1, BLACK_HOLE_POINT);
	auto middleSpace = sf::Vector2i(1, 0);

	auto hole = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.x += size.x;
		return currentStart;
	};

	hole.m_data[Skin::defaults].emplace_back(initSpace, size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);
	hole.m_data[Skin::defaults].emplace_back(nextStart(), size);

	return hole;
}
//----------------------------------------------------------------------------------
AnimationData ImageAndAudio::SpringData()
{
	auto size = sf::Vector2i(40, 50);
	auto initSpace = sf::Vector2i(1, 2687);
	auto middleSpace = sf::Vector2i(1, 0);

	auto spring = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.x += size.x;
		return currentStart;
	};
	spring.m_data[Skin::Up].emplace_back(initSpace, size);

	spring.m_data[Skin::defaults].emplace_back(initSpace, size);
	spring.m_data[Skin::defaults].emplace_back(nextStart(), size);
	spring.m_data[Skin::defaults].emplace_back(nextStart(), size);
	spring.m_data[Skin::defaults].emplace_back(nextStart(), size);
	spring.m_data[Skin::defaults].emplace_back(nextStart(), size);
	spring.m_data[Skin::defaults].emplace_back(spring.m_data[Skin::defaults][3]);
	spring.m_data[Skin::defaults].emplace_back(spring.m_data[Skin::defaults][2]);
	spring.m_data[Skin::defaults].emplace_back(spring.m_data[Skin::defaults][1]);

	return spring;
}
//----------------------------------------------------------------------------------
//end stick data
AnimationData ImageAndAudio::endStickData()
{

	auto size = sf::Vector2i(END_STICK_WIDTH, END_STICK_HIGHT);
	auto initSpace = sf::Vector2i(1, START_ENDSTICKS_POINT);
	auto middleSpace = sf::Vector2i(0, 1);
	int i = 1;
	auto endStick = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.y += size.y;
		return currentStart;
	};

	endStick.m_data[Skin::Level1].emplace_back(initSpace, size);
	endStick.m_data[Skin::Level1].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level1].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level1].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level1].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level1].emplace_back(endStick.m_data[Skin::Level1][3]);
	endStick.m_data[Skin::Level1].emplace_back(endStick.m_data[Skin::Level1][2]);
	endStick.m_data[Skin::Level1].emplace_back(endStick.m_data[Skin::Level1][1]);

	initSpace = sf::Vector2i(END_STICK_WIDTH * i + 2, START_ENDSTICKS_POINT);
	i++;
	currentStart = initSpace;
	endStick.m_data[Skin::Level2].emplace_back(initSpace, size);
	endStick.m_data[Skin::Level2].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level2].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level2].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level2].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level2].emplace_back(endStick.m_data[Skin::Level2][3]);
	endStick.m_data[Skin::Level2].emplace_back(endStick.m_data[Skin::Level2][2]);
	endStick.m_data[Skin::Level2].emplace_back(endStick.m_data[Skin::Level2][1]);

	initSpace = sf::Vector2i(END_STICK_WIDTH * i, START_ENDSTICKS_POINT);
	i++;
	currentStart = initSpace;
	endStick.m_data[Skin::Level3].emplace_back(initSpace, size);
	endStick.m_data[Skin::Level3].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level3].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level3].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level3].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level3].emplace_back(endStick.m_data[Skin::Level3][3]);
	endStick.m_data[Skin::Level3].emplace_back(endStick.m_data[Skin::Level3][2]);
	endStick.m_data[Skin::Level3].emplace_back(endStick.m_data[Skin::Level3][1]);

	initSpace = sf::Vector2i(END_STICK_WIDTH * i + 4, START_ENDSTICKS_POINT);
	i++;
	currentStart = initSpace;

	endStick.m_data[Skin::Level4].emplace_back(initSpace, size);
	endStick.m_data[Skin::Level4].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level4].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level4].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level4].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level4].emplace_back(endStick.m_data[Skin::Level4][3]);
	endStick.m_data[Skin::Level4].emplace_back(endStick.m_data[Skin::Level4][2]);
	endStick.m_data[Skin::Level4].emplace_back(endStick.m_data[Skin::Level4][1]);

	initSpace = sf::Vector2i(END_STICK_WIDTH * i +5, START_ENDSTICKS_POINT);
	i++;
	currentStart = initSpace;
	endStick.m_data[Skin::Level5].emplace_back(initSpace, size);
	endStick.m_data[Skin::Level5].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level5].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level5].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level5].emplace_back(nextStart(), size);
	endStick.m_data[Skin::Level5].emplace_back(endStick.m_data[Skin::Level5][3]);
	endStick.m_data[Skin::Level5].emplace_back(endStick.m_data[Skin::Level5][2]);
	endStick.m_data[Skin::Level5].emplace_back(endStick.m_data[Skin::Level5][1]);

	return endStick;
}
//----------------------------------------------------------------------------------
//stick data
void ImageAndAudio::sticksData()
{
	int i = 1;

	auto size = sf::Vector2i(122, 27);
	auto initSpace = sf::Vector2i(1, 738);
	auto middleSpace = sf::Vector2i(0, 1);

	auto sticks = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart += middleSpace;
		currentStart.y += size.y;
		return currentStart;
	};

	sf::Texture texture;
	sf::Image image;
	image.loadFromFile("animations.png");

	m_sticks[Skin::Level1] = m_sticks[Skin::Infinity] = vector<sf::Texture>();

	texture.loadFromImage(image, sf::IntRect(initSpace, size));
	m_sticks[Skin::Level1].push_back(texture);
	m_sticks[Skin::Infinity].push_back(texture);

	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level1].push_back(texture);
	m_sticks[Skin::Infinity].push_back(texture);

	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level1].push_back(texture);
	m_sticks[Skin::Infinity].push_back(texture);

	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level1].push_back(texture);
	m_sticks[Skin::Infinity].push_back(texture);

	initSpace = sf::Vector2i(IMAGE_SIZE_WIDTH * i, 738);
	currentStart = initSpace;

	m_sticks[Skin::Level2] = vector<sf::Texture>();
	texture.loadFromImage(image, sf::IntRect(initSpace, size));
	m_sticks[Skin::Level2].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level2].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level2].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level2].push_back(texture);

	i++;
	initSpace = sf::Vector2i(IMAGE_SIZE_WIDTH * i - 1, 738);
	currentStart = initSpace;

	m_sticks[Skin::Level3] = vector<sf::Texture>();
	texture.loadFromImage(image, sf::IntRect(initSpace, size));
	m_sticks[Skin::Level3].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level3].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level3].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level3].push_back(texture);

	i++;
	initSpace = sf::Vector2i(IMAGE_SIZE_WIDTH * i - 2, 738);
	currentStart = initSpace;

	m_sticks[Skin::Level4] = vector<sf::Texture>();
	texture.loadFromImage(image, sf::IntRect(initSpace, size));
	m_sticks[Skin::Level4].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level4].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level4].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level4].push_back(texture);

	i++;
	initSpace = sf::Vector2i(IMAGE_SIZE_WIDTH * i - 3, 738);
	currentStart = initSpace;

	m_sticks[Skin::Level5] = vector<sf::Texture>();
	texture.loadFromImage(image, sf::IntRect(initSpace, size));
	m_sticks[Skin::Level5].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level5].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level5].push_back(texture);
	texture.loadFromImage(image, sf::IntRect(nextStart(), size));
	m_sticks[Skin::Level5].push_back(texture);
}
//----------------------------------------------------------------------------------
//load game picture
void ImageAndAudio::loadGamePic()
{
	sf::Texture texture;

	texture.loadFromFile("backgroundGame.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("backgroundGame2.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("backgroundGame3.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("backgroundGame4.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("backgroundGame5.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("monster.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("hole.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("spaceship.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("coin.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("Spring.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("endLevelStick.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("bullet.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("progressBar.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("progress.png");
	m_gameImage.push_back(texture);

	texture.loadFromFile("jetpack.png");
	m_gameImage.push_back(texture);
}
//----------------------------------------------------------------------------------
void ImageAndAudio::loadMenuPic()
{
	sf::Texture texture;

	texture.loadFromFile("backgroundMenu1.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("backgroundMenu2.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("backgroundMenu3.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("backgroundMenu4.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("backgroundMenu5.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("backgroundScore.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("play.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("score.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("shop.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("exit.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("helpImage.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("InstImage.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("left.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("right.png");
	m_menuImage.push_back(texture);

	texture.loadFromFile("audio.png");
	m_menuImage.push_back(texture);

}
//----------------------------------------------------------------------------------
//load level picture
void ImageAndAudio::loadLevelPic()
{
	sf::Texture texture;

	texture.loadFromFile("lock.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("Openlock.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("1.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("2.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("3.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("4.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("5.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("thanks.png");
	m_LevelImage.push_back(texture);

	texture.loadFromFile("more.png");
	m_LevelImage.push_back(texture);

}
//----------------------------------------------------------------------------------
//load shop picture
void ImageAndAudio::loadShopPic()
{
	sf::Texture texture;

	texture.loadFromFile("player.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopTie.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopConfuse.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopCape.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopHeart.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopWork.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopUmbrella.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("ShopShield.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("buyBack.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("noMoneyBack.png");
	m_shopImage.push_back(texture);

	texture.loadFromFile("back.png");
	m_shopImage.push_back(texture);
}
//----------------------------------------------------------------------------------
//get pic
const sf::Texture* ImageAndAudio::getPic(PicChoose where, int picName)const
{
	switch (where)
	{
	case PicChoose::GAME:
		return &m_gameImage[picName];
	case PicChoose::LEVEL:
		return &m_LevelImage[picName];
	case PicChoose::MENU:
		return &m_menuImage[picName];
	case PicChoose::SHOP_ITEMS:
		return &m_shopImage[picName];
	}

}
//----------------------------------------------------------------------------------
const sf::Texture* ImageAndAudio::getStick(Sticks stick) const
{
	auto it = m_sticks.find(static_cast<Skin>(Menu::m_currHighlightLevel));
	return &it->second.at(int(stick));
}
//----------------------------------------------------------------------------------
const sf::Font* ImageAndAudio::getFont()const
{
	return &m_font;
}
//----------------------------------------------------------------------------------
void ImageAndAudio::loadAudio()
{
	//GAME MUSIC
	sf::SoundBuffer gameMusic;
	if (!gameMusic.loadFromFile("resources/music.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//GAME MUSIC
	sf::SoundBuffer loseMusic1;
	if (!loseMusic1.loadFromFile("resources/lose1.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(loseMusic1);
	m_sound.push_back(sf::Sound(loseMusic1));

	//GAME MUSIC
	sf::SoundBuffer loseMusic2;
	if (!loseMusic2.loadFromFile("resources/lose2.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(loseMusic2);
	m_sound.push_back(sf::Sound(loseMusic2));
}
//----------------------------------------------------------------------------------
void ImageAndAudio::playSound(Sound sound)
{
	m_sound[int(sound)].setBuffer(m_soundBuffer[int(sound)]);
	m_sound[int(sound)].play();
	if (sound == Sound::GAME_MUSIC)
	{
		m_sound[int(sound)].setLoop(true);
	}
}
//----------------------------------------------------------------------------------
void ImageAndAudio::stopSound(Sound sound)
{
	m_sound[int(sound)].stop();
}