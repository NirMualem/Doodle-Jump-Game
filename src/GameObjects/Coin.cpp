#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Coin.h"
#include "GameObjects/SpriteObject.h"
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

//this class represent coin in the game
Coin::Coin(const sf::Vector2f loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::COIN))
{
}
