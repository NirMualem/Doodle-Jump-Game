#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <string>
#include "Data/Enums.h"
#include <windows.h>
#include <vector>
#include <memory>
#include "Controller.h"
#include "Data/ImageAndAudio.h"
#include "Data/ConstForGame.h"
#include "GameObjects/Player.h"
#include "Button/Button.h"
#include "Button/ButtonData.h"
#include "Button/ButtonShop.h"
#include <map>

using std::vector;
using std::make_unique;
using std::pair;
using std::unique_ptr;

const int BUTTON_LOCATION = 100;
const int BUTTON_LEVEL_LOCATION = 170;

//this class is the start window to get from user the 
Menu::Menu() :m_window(), m_player_skin(Skin::defaults), m_currSkin(*ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS,
	PicNameShop::PLAYER_DEFAULT)), m_audio(false)
{
	m_levelMaxScore = { 0 };
	 
	createAllButton();//create button of the windows.
	loadText();
	backgroundCreate();
	m_currSkin.setPosition(sf::Vector2f(450, 70));
	m_currSkin.setScale(1.5 , 1.5);
	addOptions();
}
//----------------------------------------------------------------------------------
//open menu
void Menu::openMenu()
{
	m_window.create(sf::VideoMode(900, 1000), "jump jump", sf::Style::Titlebar | sf::Style::Close);
	m_window.setPosition(sf::Vector2i(m_window.getPosition().x, 0));

	//draw the members
	drawMenu();

	while (m_window.isOpen())
	{
		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			Player::m_wear = m_player_skin;
			switch (event.type)
			{
			case sf::Event::Closed:
				m_buttonSelect = ButtonMenu::EXIT_GAME_PRESS;
				m_currHighlightLevel = -1;
				m_window.close();
				return;
			case sf::Event::MouseMoved:
			{
				handleMouseMove(event.mouseMove.x, event.mouseMove.y);
				break;
			}
			//if the mouse press handle.
			case sf::Event::MouseButtonReleased:
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				getClick(location);
				if (preformAction())
				{
					m_window.close();
					return;
				}
				//draw the members
				drawMenu();
			}
		}
		drawMenu();
	}
}
//----------------------------------------------------------------------------------
//add option of menu click
void Menu::addOptions()
{
	m_options.emplace_back(option(ButtonMenu::EXIT_GAME_PRESS, &Menu::executeExit));
	m_options.emplace_back(option(ButtonMenu::SCORE_PRESS, &Menu::executeScore));
	m_options.emplace_back(option(ButtonMenu::PLAY_PRESS, &Menu::executeInfinity));
	m_options.emplace_back(option(ButtonMenu::SHOP_PRESS, &Menu::executeShop));
	m_options.emplace_back(option(ButtonMenu::HELP_PRESS, &Menu::executeHelp));
	m_options.emplace_back(option(ButtonMenu::LEFT_PRESS, &Menu::executeLeft));
	m_options.emplace_back(option(ButtonMenu::RIGHT_PRESS, &Menu::executeRight));
	m_options.emplace_back(option(ButtonMenu::LEVEL_PRESS, &Menu::executeLevel));
	m_options.emplace_back(option(ButtonMenu::AUDIO_PRESS, &Menu::executeAudio));
	
}
//----------------------------------------------------------------------------------
//exit
bool Menu::executeExit()
{
	m_currHighlightLevel = -1;
	return true;
}
//----------------------------------------------------------------------------------
//infinity mode
bool Menu::executeInfinity()
{
	Player::m_wear = m_player_skin;
	m_currHighlightLevel = 0;
	return true;
}

//----------------------------------------------------------------------------------
//audio mode
bool Menu::executeAudio()
{
	if (m_audio)
	{
		ImageAndAudio::instance().playSound(Sound::GAME_MUSIC);
	}
	else
	{
		ImageAndAudio::instance().stopSound(Sound::GAME_MUSIC);
	}
	m_audio = !m_audio;
	return false;
}

//----------------------------------------------------------------------------------
//left click
bool Menu::executeLeft()
{
	if (m_currHighlightLevel > 0)
	{
		m_buttonLevel[m_currHighlightLevel]->setScale(1);
		m_currHighlightLevel -= 1;
	}
	return false;
}
//----------------------------------------------------------------------------------
//right click
bool Menu::executeRight()
{
	if (m_currHighlightLevel < m_buttonLevel.size() - 1)
	{
		m_buttonLevel[m_currHighlightLevel]->setScale(1);
		m_currHighlightLevel += 1;
	}
	return false;
}
//----------------------------------------------------------------------------------
//help click
bool Menu::executeHelp()
{
	sf::RenderWindow inst;
	sf::Sprite instBack;
	instBack.setTexture(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::INST_BACKGROUND));
	instBack.setPosition(sf::Vector2f(0, 0));
	inst.create(sf::VideoMode(1004, 636), "instructions", sf::Style::Titlebar | sf::Style::Close);
	inst.clear();
	inst.draw(instBack);
	inst.display();

	while (inst.isOpen())
	{
		for (auto event = sf::Event{}; inst.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				inst.close();
				break;
			}
		}
	}
	auto event = sf::Event{};
	while (m_window.pollEvent(event))
	{
	}
	return false;
}
//----------------------------------------------------------------------------------
//shop click
bool Menu::executeShop()
{
	m_button[ButtonMenu::SHOP_PRESS]->setScale(1);
	bool exitShop = false;
	drawShop();
	while (true)
	{
		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_buttonSelect = ButtonMenu::EXIT_GAME_PRESS;
				m_currHighlightLevel = -1;
				m_window.close();
				return true;

				//if the mouse press handle.
			case sf::Event::MouseButtonReleased:
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				handleClickShopWin(location, exitShop);
			}
		}
		if (exitShop)
			return false;

		drawShop();
	}

}
//----------------------------------------------------------------------------------
//level click
bool Menu::executeLevel()
{
	return true;
}
//----------------------------------------------------------------------------------
//score click
bool Menu::executeScore()
{
	sf::RenderWindow score;
	sf::Sprite scoreBack;
	scoreBack.setTexture(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_SCORE));
	scoreBack.setPosition(sf::Vector2f(0, 0));
	score.create(sf::VideoMode(600, 750), "high score", sf::Style::Titlebar | sf::Style::Close);
	score.clear();
	score.draw(scoreBack);

	sf::Vector2f l(40, 160);
	for (int i = 0; i < HIGH_SCORE_PLAYERS; i++)
	{
		m_text[0].setString(std::to_string(i + 1) + ". " + m_infinityHighScore[i].second);
		m_text[0].setPosition(l);
		m_text[3].setString(std::to_string(m_infinityHighScore[i].first));
		m_text[3].setPosition(l.x +350, l.y);
		score.draw(m_text[3]);
		score.draw(m_text[0]);
		l.y += 55;
	}
	score.display();

	while (score.isOpen())
	{
		for (auto event = sf::Event{}; score.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				score.close();
				break;
			}
		}
	}
	return false;
}
//----------------------------------------------------------------------------------
//no press
bool Menu::executeNoPress()
{
	return false;
}
//----------------------------------------------------------------------------------
//background of menu
void Menu::backgroundCreate()
{
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_1)));
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_2)));
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_3)));
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_4)));
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::BACKGROUND_MENU_5)));
	m_backgroundSprite.push_back(sf::Sprite(*ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::BACKGROUND_GAME)));

}
//----------------------------------------------------------------------------------
//preform action
bool Menu::preformAction()
{
	for (int i = 0; i < m_options.size(); i++)
		if (m_options[i].first == m_buttonSelect)
		{
			return (this->*m_options[i].second)();
		}
	return false;
}
//----------------------------------------------------------------------------------
//update skins
void Menu::updateSkins(vector<int> skins)
{
	for (int i = 0; i < skins.size() ; i++)
	{
		ButtonShop& button = dynamic_cast<ButtonShop&>(*m_shopButton[skins[i]]);
		button.setActive(true);
	}
}
//----------------------------------------------------------------------------------
//this function change the mouse according the location.
void Menu::handleMouseMove(int x, int y)
{
	sf::Vector2f loc(x, y);
	//if on the menu in regular mouse 
	for (int i = 0; i < m_button.size(); ++i)
		{
			if (m_button[i]->getSprite().getGlobalBounds().contains(loc))
					m_button[i]->setScale(1.1);		
			else
					m_button[i]->setScale(1);
		}
	//draw the members
	drawMenu();
}
//----------------------------------------------------------------------------------
//this function handle click on the mouse
void Menu::getClick(const sf::Vector2f& location)
{
	//check if click on buttons
	for (auto i = 0; i < m_button.size(); ++i)
	{
		if (m_button[i]->handleClick(location))
		{
			m_buttonSelect = static_cast<ButtonMenu>(i);
			return;
		}
	}

	for (auto i = m_currHighlightLevel ; i < m_currHighlightLevel+3; ++i)
	{
		if (m_buttonLevel[i]->handleClick(location))
		{
			if (m_buttonLevel[i]->updateIfActive())
			{
				m_buttonSelect = ButtonMenu::LEVEL_PRESS;
				m_currHighlightLevel = i + 1;
				return;
			}
		}
	}
	m_buttonSelect = ButtonMenu::NO_PRESS;
}
//----------------------------------------------------------------------------------
//handle events of shop
void Menu::handleClickShopWin(const sf::Vector2f& location , bool& exitShop)
{
	//check if click on buttons
	for (auto i = 0; i < m_shopButton.size(); ++i)
	{
		if (m_shopButton[i]->handleClick(location))
		{
			if (i == m_shopButton.size()-1)
			{
				exitShop = true;
				break;
			}
			else if (typeid(*m_shopButton[i]) == typeid(ButtonShop))
			{
				ButtonShop& button = dynamic_cast<ButtonShop&>(*m_shopButton[i]);
				if (button.updateIfActive())
				{
					Player::m_wear = static_cast<Skin>(i + 6);
					m_player_skin = static_cast<Skin>(i + 6);
					m_currSkin.setTexture(*ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop(i)));
					break;
				}
				auto event = sf::Event{};
				while (m_window.pollEvent(event))
				{
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------
//this function draw the members in the windows.
void Menu::drawMenu()
{
	m_window.clear();
	if (m_currHighlightLevel > m_buttonLevel.size() - 3)
	{
		m_currHighlightLevel = m_buttonLevel.size() - 3;
	}
	m_window.draw(m_backgroundSprite[m_currHighlightLevel]);
	//buttons
	for (int i = 0; i < m_button.size(); ++i)
	{
		m_button[i]->draw(m_window);
	}

	sf::Vector2f l(250, 800);

	m_buttonLevel[m_currHighlightLevel]->setScale(1.2);

	for (int i = m_currHighlightLevel ; i < m_buttonLevel.size() && i < m_currHighlightLevel + 3 ; ++i)
	{
		m_buttonLevel[i]->setLoc(l);
		m_buttonLevel[i]->draw(m_window);
		l.x += 150;
	}
	m_window.display();
}
//----------------------------------------------------------------------------------
//draw shop
void Menu::drawShop()
{
	m_window.clear();
	m_window.draw(m_backgroundSprite[m_backgroundSprite.size()-1]);
	//buttons
	m_text[3].setString(std::to_string(Player::m_collectedCoin));
	m_text[3].setPosition(sf::Vector2f(780, 20));
	sf::Sprite coin(*ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::COIN));
	coin.setPosition(m_text[3].getPosition().x + 40, m_text[3].getPosition().y);
	coin.setScale(0.8, 0.8);
	m_window.draw(coin);

	for (int i = 0; i < m_shopButton.size(); ++i)
	{
		m_shopButton[i]->draw(m_window);
	}
	for (int price = 0; price < m_shopButton.size() - 1; price++)
	{
		ButtonShop& button = dynamic_cast<ButtonShop&>(*m_shopButton[price]);
		m_text[0].setPosition(button.getSprite().getPosition().x, button.getSprite().getPosition().y + 130);
		coin.setPosition(m_text[0].getPosition().x + 30, m_text[0].getPosition().y);
		if (button.getPrice() == 0)
			m_text[0].setString("own");
		else 
		{
			m_text[0].setString(std::to_string(button.getPrice()));
			m_window.draw(coin);
		}
		m_window.draw(m_text[0]);
	}
	for (int i = 1; i < m_text.size(); i++)
	{
		m_window.draw(m_text[i]);//draw text
	}
	m_window.draw(m_currSkin);
	m_window.display();
}
//----------------------------------------------------------------------------------
//get select level in menu
int Menu::getSelectLevel() const
{
	return m_currHighlightLevel;
}
//----------------------------------------------------------------------------------
//get bouts skin 
vector<int> Menu::getBoutSkins() const
{
	vector<int> skins;
	for (int skin = 0; skin < m_shopButton.size() - 1; skin++)
	{
		ButtonShop& button = dynamic_cast<ButtonShop&>(*m_shopButton[skin]);
		if (button.getPrice() == 0)
		{
			skins.push_back(skin);
		}
	}
	return skins;
}
//----------------------------------------------------------------------------------
//update button of level if pass
void Menu::updateButtonLevel(int level)
{
	if(level < LEVELS)
		m_buttonLevel[level]->setActive(true);
}
//----------------------------------------------------------------------------------
//get last open level
int Menu::getLastOpenLevel()
{
	int i;
	for( i=0; i< m_buttonLevel.size(); i++)
		if (!m_buttonLevel[i]->updateIfActive())
		{
			break;
		}
	return i;
}
//----------------------------------------------------------------------------------
//update score char
void Menu::updateScoreChar(int score)
{
	auto oldArrayIndex = 0;
	auto newArrayIndex = 0;
	bool update = false;
	array<pair<int, string>, HIGH_SCORE_PLAYERS> scoreChar;
	for (; newArrayIndex < HIGH_SCORE_PLAYERS; oldArrayIndex++ , newArrayIndex++)
	{
		if (!update && m_infinityHighScore[oldArrayIndex].first < score)
		{
			scoreChar[oldArrayIndex].first = score;
			scoreChar[oldArrayIndex].second = getName();
			oldArrayIndex--;
			update = true;
		}
		else
		{
			scoreChar[newArrayIndex].first = m_infinityHighScore[oldArrayIndex].first;
			scoreChar[newArrayIndex].second = m_infinityHighScore[oldArrayIndex].second;
		}
	}
	m_infinityHighScore = scoreChar;
	executeScore();
}
//----------------------------------------------------------------------------------
//get name from user when the score enter to the high score
string Menu::getName()
{
	string name = "";

	try
	{
		char letter;
		sf::RenderWindow nameWin;
		sf::Sprite nameBack;
		nameBack.setTexture(*ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::BACKGROUND_GAME));
		nameBack.setPosition(sf::Vector2f(0, -200));
		nameWin.create(sf::VideoMode(600, 200), " get name", sf::Style::Titlebar | sf::Style::Close);
		nameWin.clear();
		nameWin.draw(nameBack);
		m_text[0].setString("Enter your name \n (max 10 char , only letters) : ");
		m_text[0].setPosition(sf::Vector2f(15, 20));
		nameWin.draw(m_text[0]);
		nameWin.display();
		while (nameWin.isOpen())
		{
			for (auto event = sf::Event{}; nameWin.pollEvent(event);)
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					nameWin.close();
					break;
				}
				case sf::Event::TextEntered:
				{
					letter = event.text.unicode;
					if (!isalpha(letter))
						break;
					name += letter;
					m_text[3].setString(name);
					m_text[3].setPosition(sf::Vector2f(70, 120));
					nameWin.clear();
					nameWin.draw(nameBack);
					nameWin.draw(m_text[0]);
					nameWin.draw(m_text[3]);
					nameWin.display();
					break;
				}
				}
				if (event.key.code == sf::Keyboard::Backspace && name.size() > 0)
				{
					name = "";
					m_text[3].setString(name);
					nameWin.clear();
					nameWin.draw(nameBack);
					nameWin.draw(m_text[0]);
					nameWin.draw(m_text[3]);
					nameWin.display();
				}
				else if (name.size() >= 10 || event.key.code == sf::Keyboard::Enter)
				{
					nameWin.close();
					break;
				}
			}
		}
	}
	catch ( std::exception)
	{
			std::cout << "name in hebrew is not vaild\n";
	}
		
	if (name != "")
		return name;
	else
		return "anonymous";
}
void Menu::updateInfinityHighScore(array<pair<int, string>, HIGH_SCORE_PLAYERS> score)
{
	for (int i = 0; i < HIGH_SCORE_PLAYERS; i++)
	{
		m_infinityHighScore[i].first = score[i].first;
		m_infinityHighScore[i].second = score[i].second;
	}
}
//----------------------------------------------------------------------------------
array<pair<int, string>, HIGH_SCORE_PLAYERS> Menu::getscoreInfinity()const
{
	return m_infinityHighScore;
}
//----------------------------------------------------------------------------------
//this function  create all button.
void Menu::createAllButton()
{
	//three button in the up of the page
	m_button.clear();

	sf::Vector2f l(650, 900);
	//exit
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::EXIT_GAME), 1));

	//play 
	l = sf::Vector2f(70, 350);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::PLAY), 1));

	l = sf::Vector2f(70, 550);
	//score
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::SCORE), 1));

	//shop 
	l = sf::Vector2f(70, 150);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::SHOP), 1));

	//help
	l = sf::Vector2f(10, 20);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::HELP), 1));

	l = sf::Vector2f(100, 800);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::LEFT), 1));

	l = sf::Vector2f(700, 800);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::RIGHT), 1));

	//audio
	l = sf::Vector2f(800, 10);
	m_button.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::MENU, PicNameMenu::AUDIO), 1));

	//levels menu buttons
	l = sf::Vector2f(200 , 200);
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LEVEL_ONE), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));
	m_buttonLevel[0]->setActive(true);

	l.x += BUTTON_LEVEL_LOCATION;
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LEVEL_TWO), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));

	l.x += BUTTON_LEVEL_LOCATION;
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LEVEL_THREE), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));

	l.x = 200;
	//l.y += BUTTON_LEVEL_LOCATION;
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LEVEL_FOUR), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));

	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LEVEL_FIVE), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));

	l = sf::Vector2f(20 , 300);
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::THANKS), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));
	l = sf::Vector2f(100, 350);

	l = sf::Vector2f(20, 300);
	m_buttonLevel.push_back(make_unique<ButtonData>(l, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::MORE), 1, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK)));
	l = sf::Vector2f(100, 350);

	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::PLAYER_DEFAULT), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::OPEN_LOCK),0));
	ButtonShop& button = dynamic_cast<ButtonShop&>(*m_shopButton[0]);
	button.setActive(true);

	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::TIE), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), CHEAP_PRICE));

	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::CONFUSE), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), CHEAP_PRICE));

	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::CAPE), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), MEDIUM_PRICE));

	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::HEART), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), MEDIUM_PRICE));

	l.x = 100;
	l.y += 200;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::WORK), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), HIGH_PRICE));
	
	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::UMBRELLA), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), HIGH_PRICE));

	l.x += 150;
	m_shopButton.push_back(make_unique<ButtonShop>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::SHIELD), 1.5, *ImageAndAudio::instance().getPic(PicChoose::LEVEL, PicNameLevel::LOCK), HIGH_PRICE));

	l = sf::Vector2f(20, 20);
	m_shopButton.push_back(make_unique<Button>(l, *ImageAndAudio::instance().getPic(PicChoose::SHOP_ITEMS, PicNameShop::BACK), 1));
}
//----------------------------------------------------------------------------------
//load text
void Menu::loadText()//load text of the windows
{
	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(), 40));
	m_text[0].setFillColor(sf::Color(255, 255, 130));

	m_text.push_back(sf::Text("your skin:", *ImageAndAudio::instance().getFont(), 34));
	m_text[1].setPosition(sf::Vector2f(285, 130));
	m_text[1].setFillColor(sf::Color(255, 255, 130));

	m_text.push_back(sf::Text("coins: ", *ImageAndAudio::instance().getFont(), 40));
	m_text[2].setPosition(sf::Vector2f(690, 20));
	m_text[2].setFillColor(sf::Color(255, 255, 130));

	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(), 40));
	m_text[3].setPosition(sf::Vector2f(780, 20));
	m_text[3].setFillColor(sf::Color(255, 255, 130));

	m_text.push_back(sf::Text("player skins: ", *ImageAndAudio::instance().getFont(), 40));
	m_text[4].setPosition(sf::Vector2f(10, 310));
	m_text[4].setFillColor(sf::Color(255, 255, 130));
}
bool Menu::getIfAudio()
{
	return m_audio;
}
