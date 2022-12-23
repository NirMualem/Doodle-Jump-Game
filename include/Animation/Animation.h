#pragma once

#include "Data/Enums.h"
#include "AnimationData.h"

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(const AnimationData& data, Skin dir, sf::Sprite& sprite);//constractor
    void skin(Skin dir);//skin - pic to show
    void update(sf::Time delta);//update animation

private:
    void update();

    const AnimationData& m_data;
    sf::Time m_elapsed = {};
    Skin m_dir = Skin::defaults;
    int m_index = 0;
    sf::Sprite& m_sprite;
};
