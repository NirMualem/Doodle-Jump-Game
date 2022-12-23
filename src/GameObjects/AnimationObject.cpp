#include <SFML/Graphics.hpp>
#include "GameObjects/AnimationObject.h"
#include "GameObjects/ObjectAbstract.h"
#include "Data/Enums.h"
#include <SFML/Graphics.hpp>
#include "GameObjects/Player.h"
#include "Data/ConstForGame.h"
#include <memory.h>
#include "Animation/Animation.h"

using std::vector;
using std::unique_ptr;

//this class is absract of move object in the game

//constractor
AnimationObject::AnimationObject(const sf::Vector2f loc,const AnimationData& animation, Skin skin)
	: ObjectAbstract(loc) , m_animation(Animation(animation, skin ,m_sprite))
{
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getOrigin().x + IMAGE_MIDDLE, m_sprite.getOrigin().y));
	m_sprite.setPosition(sf::Vector2f(loc));

	m_side = SideToMove::RIGHT;
	m_directionLoc = sf::Vector2f(1, 0);
}
//----------------------------------------------------------------------------------
//update the image to the correct dir/skin
void AnimationObject::updateDir(Skin skin)
{
	m_animation.skin(skin);
}
void AnimationObject::move(const float deltaTime, SideToMove side, sf::Time time)
{
	if (side == SideToMove::NO_MOVE)
	{
		m_directionLoc = sf::Vector2f(0, 1);
		m_sprite.move(m_directionLoc * deltaTime);
	}
	m_animation.update(time);

}