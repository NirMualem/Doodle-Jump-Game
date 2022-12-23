#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data/Enums.h"

class Player;
class StaticStick;

class ObjectAbstract
{
public:
    ObjectAbstract(const sf::Vector2f loc);//constractor
    virtual ~ObjectAbstract() = default;
    virtual void draw(sf::RenderWindow& window) const;//draw the sprite
    sf::Vector2f getLocation();//get location
    sf::Sprite getsprite()const;//get the sprite
    void setPosition(sf::Vector2f last);//set position of the sprite
    void setOrigin(float x, float y);
    bool checkIfDelete() const;
    virtual void move(const float deltaTime, SideToMove side, sf::Time time);
    void setIfDeleted(bool ifDelete);

    bool checkCollision(const sf::FloatRect& rect) const;//check collision
protected:
    SideToMove m_side;//side of the object
    sf::Sprite m_sprite;
    bool m_delete;
    sf::Vector2f m_directionLoc;//side of the sprite

};