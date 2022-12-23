#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enums.h"
#include <vector>
#include "Animation/AnimationData.h"

using std::vector;

//in this class we load all the pic and aduio in the game
class ImageAndAudio {
public:
	static ImageAndAudio& instance();
	~ImageAndAudio() {};
	
	const sf::Texture* getPic(PicChoose where, int picName)const;//get pic from vector
	const sf::Font *getFont()const;//get font
	const sf::Texture& texture() const;//texture for game and animations.
	const sf::Texture* getStick(Sticks stick)const;//get stick
	const AnimationData& animationData(ObjectsAnimation object)const;//animation data

	void playSound(Sound sound);//play select sound 
	void stopSound(Sound sound);//stop sound


private:
	
	ImageAndAudio();//constractor
	ImageAndAudio(const ImageAndAudio&) = default;//constractor
	ImageAndAudio& operator=(const ImageAndAudio&) = default;
	void loadPictures();//load pic
	void loadGamePic();//load game pic
	void loadMenuPic();//load menu pic
	void loadLevelPic();//load level pic
	void loadShopPic();//load shop pic
	void loadAudio();//load audio


	AnimationData robotData();//robot data animation
	AnimationData monsterData();//monster data animation
	AnimationData endStickData();//endstick data animation
	AnimationData HoleData();//hole data animation
	AnimationData SpringData();//spring data animation
	void sticksData();//stick images

	vector <sf::Texture> m_gameImage;//vector of image for game
	vector <sf::Texture> m_menuImage;//vector of image for menu
	vector <sf::Texture> m_LevelImage;//vector of image for level
	vector <sf::Texture> m_shopImage;//vector of image for shop
	std::unordered_map<Skin , vector <sf::Texture>> m_sticks;//map of sticks level
	sf::Font m_font;//font
	std::vector<AnimationData> m_data;//animation  data
	vector <sf::Sound> m_sound;//sound in the game
	vector <sf::SoundBuffer> m_soundBuffer;//sound buffer
	sf::Texture m_texture;//texture for animation and images 
};
