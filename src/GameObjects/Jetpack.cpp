#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObjects/Jetpack.h"
#include "GameObjects/SpriteObject.h"
#include "GameObjects/Player.h"
#include "Data/Enums.h"
#include <memory.h>
#include "Data/ImageAndAudio.h"

//this class represents jetpack in the game.
Jetpack::Jetpack(const sf::Vector2f loc)
	: SpriteObject(loc, *ImageAndAudio::instance().getPic(PicChoose::GAME, PicNameGame::JETPACK))
{
}
