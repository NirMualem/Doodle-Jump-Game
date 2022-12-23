#pragma once
//this enum for the image option
enum PicNameMenu {
	BACKGROUND_MENU_1	  = 0,
	BACKGROUND_MENU_2	  = 1,
	BACKGROUND_MENU_3	  = 2,
	BACKGROUND_MENU_4	  = 3,
	BACKGROUND_MENU_5	  = 4,
	BACKGROUND_MENU_SCORE = 5,
	PLAY				  = 6,
	SCORE				  = 7,
	SHOP				  = 8,
	EXIT_GAME			  = 9,
	HELP				  = 10,
	INST_BACKGROUND		  = 11,
	LEFT				  = 12,
	RIGHT				  = 13,
	AUDIO                 = 14
};

enum PicNameGame {
	BACKGROUND_GAME = 0,
	BACKGROUND_GAME_2 = 1,
	BACKGROUND_GAME_3 = 2,
	BACKGROUND_GAME_4 = 3,
	BACKGROUND_GAME_5 = 4,
	MONSTER			= 5,
	HOLE			= 6,
	SPACESHIP		= 7,
	COIN			= 8,
	SPRING          = 9,
	END_LEVEL_STICK = 10,
	BULLET          = 11,
	PROGRESS_BAR    = 12,
	PROGRESS        = 13,
	JETPACK			= 14,
	SPACE			= 15
};

enum PicNameLevel {
	LOCK		= 0,
	OPEN_LOCK	= 1,
	LEVEL_ONE	= 2,
	LEVEL_TWO	= 3,
	LEVEL_THREE = 4,
	LEVEL_FOUR	= 5,
	LEVEL_FIVE  = 6,
	THANKS   	= 7,
	MORE		= 8
};

enum PicNameShop {
	PLAYER_DEFAULT = 0,
	TIE			   = 1,
	CONFUSE		   = 2,
	CAPE		   = 3,
	HEART		   = 4,
	WORK		   = 5,
	UMBRELLA       = 6,
	SHIELD         = 7,
	BUY_BACK	   = 8,
	NO_MONEY_BACK  = 9,
	BACK		   = 10
};

enum PicChoose {
	GAME		= 0,
	MENU		= 1,
	LEVEL		= 2,
	SHOP_ITEMS	= 3
};

enum Operate {
	EXIT = -1,
	INFINITY_GAME = 0,
};

enum ButtonMenu {
	 EXIT_GAME_PRESS = 0,
	 PLAY_PRESS		 = 1,
	 SCORE_PRESS     = 2,
	 SHOP_PRESS		 = 3,
	 HELP_PRESS		 = 4,
	 LEFT_PRESS		 = 5,
	 RIGHT_PRESS	 = 6,
	 AUDIO_PRESS     = 7,
	 LEVEL_PRESS	 = 8,
	 NO_PRESS		 = 9
};

enum typeOfEnemy {
	randomEnemy		= 0,
	backForthEnemy	= 1,
	smartEnemy		= 2
};

enum class SideToMove {
	NO_MOVE	= 0,
	RIGHT	= 1,
	LEFT	= 2,
	UP		= 3,
	DOWN	= 4
};
enum class LoseWay {
	MONSTER = 0,
	HOLE	= 1
};

enum class Sticks {
	NORMAL = 0,
	BROKE = 1,
	MOVE = 2,
	DISSAPEAR = 3
};

enum class Sound
{
	GAME_MUSIC	= 0,
	LOSE1		= 1,
	LOSE2		= 2
	
};

enum ObjectsAnimation
{
	Robot,
	Monster,
	EndStick,
	Hole,
	Springs,
	Max,
};
enum class Skin
{
	Infinity = 0,
	Level1 = 1,
	Level2 = 2,
	Level3 = 3,
	Level4 = 4,
	Level5 = 5,
	defaults = 6,
	tie = 7,
	confuse = 8,
	cape = 9,
	heart = 10,
	work = 11,
	umbrella = 12,
	shield = 13,
	jetpack = 14,
	dead = 15,
	Up = 16,
	Stay = 17

};