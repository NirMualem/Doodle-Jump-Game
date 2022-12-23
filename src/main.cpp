
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Data/HanldleFile.h"
#include "Controller.h"
#include "Data/ImageAndAudio.h"

/*jump jump game :)
*/

int main()
{	
	//create controller and run game.
	Controller con;
	con.runGame();
	return EXIT_SUCCESS;
}