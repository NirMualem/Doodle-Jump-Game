#include "Animation/Animation.h"
#include "Data/ImageAndAudio.h"

const auto AnimationTime = sf::seconds(0.1f);

//this class is managers the animations in the game. 
Animation::Animation(const AnimationData& data, Skin dir, sf::Sprite& sprite)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_sprite.setTexture(ImageAndAudio::instance().texture());
    update();
}
//----------------------------------------------------------------------------------
//upadte picture
void Animation::skin(Skin dir)
{
    if (m_dir == dir || dir == Skin::Stay)
    {
        return;
    }

    m_dir = dir;
    update();
}
//----------------------------------------------------------------------------------
//update picture by time
void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

//set texture
void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}
