#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button\Button.h"
#include "Button\ButtonData.h"
#include "Button\ButtonShop.h"
#include "Data/Enums.h"
#include "Data/ConstForGame.h"
#include <array>
#include <memory>
#include <map>

using std::unique_ptr;
using std::array;
using std::pair;
using std::vector;

//this class manageress the menu in the game.
class Menu
{
public:
    Menu();          //constractor
    void openMenu(); //open menu
    int getSelectLevel() const;//get select level
    void updateButtonLevel(int level);//update level click
    void updateScoreChar(int score);//update score char
    void updateInfinityHighScore(array<pair<int, string>, HIGH_SCORE_PLAYERS>score);//update infinity score
    array<pair<int, string>, HIGH_SCORE_PLAYERS> getscoreInfinity()const;//get score of infinity mode
    string getName();//get name from user
    int getLastOpenLevel();//get last open level
    void backgroundCreate();//background of menu
    static int m_currHighlightLevel;//
    vector<int> getBoutSkins() const;//get skins that user buy it
    void updateSkins(vector<int> skins);//update buy skins
    bool getIfAudio();
private:
    //members
    sf::RenderWindow m_window;//window of menu
    vector < sf::Sprite > m_backgroundSprite;//background
    sf::Sprite m_currSkin;//current skin of the player
    vector<sf::Text> m_text;//text show on screen
    vector<unique_ptr<Button>> m_button;//vector of button
    vector<unique_ptr<Button>> m_shopButton;//shop buttons
    vector<unique_ptr<ButtonData>> m_buttonLevel;//vector of button
    array<int , 7> m_levelMaxScore;///max score
    array<pair<int, string>, HIGH_SCORE_PLAYERS> m_infinityHighScore;//infinity score array
    ButtonMenu m_buttonSelect;//select buttons
    int m_numOfLevel; //num of level in the game
    Skin m_player_skin;//player skin
    bool m_audio;
    //for the menu manager
    typedef pair<ButtonMenu, bool(Menu::*)()> option;
    vector<option> m_options;

    void addOptions();//add option to menu
    bool preformAction();//preform choose action
    //execute functions
    bool executeExit();
    bool executeInfinity();
    bool executeScore();
    bool executeShop();
    bool executeHelp();
    bool executeLeft();
    bool executeRight();
    bool executeLevel();
    bool executeNoPress();
    bool executeAudio();
    void handleMouseMove(int x, int y);//handle mouse click
    void drawMenu();//draw menu
    void drawShop();//draw shop
    void createAllButton();//create all button in menu
    void loadText();//load text
    void getClick(const sf::Vector2f& location);//get click user
    void handleClickShopWin(const sf::Vector2f& location, bool& exitShop);//hanlde click in shop

};

