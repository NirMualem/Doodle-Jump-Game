#include <SFML/Graphics.hpp>

# include <windows.h>
#include "CollisionHandling.h"
#include "GameObjects/ObjectAbstract.h"
#include "GameObjects/AnimationObject.h"
#include "Data/ImageAndAudio.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <time.h>

#include "GameObjects/Player.h"
#include "Data/ConstForGame.h"
#include "GameObjects/Sticks/StaticStick.h"
#include "GameObjects/Sticks/BrokenStick.h"
#include "GameObjects/Sticks/MoveStick.h"
#include "GameObjects/Sticks/DisapperStick.h"
#include "GameObjects/Sticks/endLevelStick.h"

#include "GameObjects/Enemies/EnemyMonster.h"
#include "GameObjects/Enemies/EnemyHole.h"
#include "GameObjects/Enemies/EnemySpaceship.h"
#include "GameObjects/Coin.h"
#include "GameObjects/Spring.h"
#include "GameObjects/Bullet.h"
#include "GameObjects/Jetpack.h"

using HitFunctionPtr = void (*)(ObjectAbstract&, ObjectAbstract&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

namespace // anonymous namespace — the standard way to make function "static"
{

// primary collision-processing functions
void playerStatic(ObjectAbstract& playerObj,
    ObjectAbstract& staticStick)
{
    Player& player = dynamic_cast<Player&>(playerObj);

    if (player.getSide() == SideToMove::DOWN && (staticStick.getsprite().getGlobalBounds().contains(player.getLocation().x - 20, player.getLocation().y + 85) || staticStick.getsprite().getGlobalBounds().contains(player.getLocation().x + 20, player.getLocation().y + 85)))
    {
            player.setUpLimit(player.getLocation().y - 700);
            player.setSide(SideToMove::UP);
            player.setUpPass(0);
    }
}

void playerDisappear(ObjectAbstract& playerObj,
    ObjectAbstract& disappearStick)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    DisappearStick& disStick = dynamic_cast<DisappearStick&>(disappearStick);

    if (player.getSide() == SideToMove::DOWN && (disappearStick.getsprite().getGlobalBounds().contains(player.getLocation().x - 20, player.getLocation().y + 85) || disappearStick.getsprite().getGlobalBounds().contains(player.getLocation().x + 20, player.getLocation().y + 85)))
    {
        player.setUpLimit(player.getLocation().y - 700);
        player.setSide(SideToMove::UP);
        player.setUpPass(0);
        disStick.setIfDeleted(true);
    }
}

void playerSpring(ObjectAbstract& playerObj,
    ObjectAbstract& springObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    Spring& spring = dynamic_cast<Spring&>(springObj);

    if (player.getSide() == SideToMove::DOWN && ( spring.getsprite().getGlobalBounds().contains(player.getLocation().x - 20, player.getLocation().y + 85) || spring.getsprite().getGlobalBounds().contains(player.getLocation().x + 20, player.getLocation().y + 85)))
    {
        spring.updateDir(Skin::defaults);

        player.setUpLimit(1000);
        player.setSide(SideToMove::UP);
        player.setUpPass(-400);
    }
}
void playerJetpack(ObjectAbstract& playerObj,
    ObjectAbstract& jetpackObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    Jetpack& jetpack = dynamic_cast<Jetpack&>(jetpackObj);

    if (jetpack.getsprite().getGlobalBounds().intersects(player.getsprite().getGlobalBounds()))
    {
        player.setUpLimit(1000);
        player.setUpPass(-700);
        Player::m_wear = Skin::jetpack;
        player.setSide(SideToMove::UP);
        player.setDirectionAnimation();
        jetpack.setIfDeleted(true);

    }
}

void playerBroken(ObjectAbstract& playerObj,
    ObjectAbstract& brokenStick)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    BrokenStick& broken = dynamic_cast<BrokenStick&>(brokenStick);

    if (player.getSide() == SideToMove::DOWN)
    {
        broken.setIfDeleted(true);
    }
}

void playerMonster(ObjectAbstract& playerObj,
    ObjectAbstract& mansterObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    EnemyMonster& monster = dynamic_cast<EnemyMonster&>(mansterObj);

    sf::Sprite checkSprite = monster.getsprite();
    checkSprite.setScale(float(0.8), float(0.8));
    
    if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()) && (player.getsprite().getPosition().y + PLAYER_HEIGHT) < checkSprite.getPosition().y + 30)
    {
        monster.setIfDeleted(true);
        player.setUpLimit(1000);
        player.setSide(SideToMove::UP);
        player.setUpPass(-300);
    }
    else if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()))
    {
        if (!player.getLose())
        {
            ImageAndAudio::instance().playSound(Sound::LOSE1);

        }
        player.setLose(true);
        player.setLoseWay(LoseWay::MONSTER);
        Player::m_wear = Skin::dead;
        player.setDirectionAnimation();

    }  
}

void playerHole(ObjectAbstract& playerObj,
    ObjectAbstract& holeObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    EnemyHole& hole = dynamic_cast<EnemyHole&>(holeObj);
    
    sf::Sprite checkSprite = hole.getsprite();
    checkSprite.setScale(float(0.8), float(0.8));

    if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()))
    {
        player.changeSideSprite(SideToMove::NO_MOVE);
        player.setLoseWay(LoseWay::HOLE);
        
        player.setOrigin(20,0);

        if (player.getsprite().getScale().x == -1)
        {
            player.setScale(1);

        }
        player.setLose(true);
        player.setPosition(sf::Vector2f(hole.getLocation().x, hole.getLocation().y + 30));
        player.setScale(player.getsprite().getScale().x - 0.2);
        Sleep(50);

        if (player.getsprite().getScale().x < 0.2)
        {
            ImageAndAudio::instance().playSound(Sound::LOSE2);

            player.setPosition(sf::Vector2f(player.getLocation().x, player.getLocation().y + 2000));
        }
    }
}

void playerSpaceShip(ObjectAbstract& playerObj,
    ObjectAbstract& spaceObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    EnemySpaceship& spaceShip = dynamic_cast<EnemySpaceship&>(spaceObj);

    sf::Sprite checkSprite = spaceShip.getsprite();
    checkSprite.setScale(float(0.8), float(0.8));

    if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()) && (player.getsprite().getPosition().y + PLAYER_HEIGHT) < checkSprite.getPosition().y + 30)
    {
        spaceShip.setIfDeleted(true);
        player.setUpLimit(1000);
        player.setSide(SideToMove::UP);
        player.setUpPass(-300);
    }
    else if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()))
    {
        player.setLoseWay(LoseWay::HOLE);
        player.setLose(true);
        
        player.setOrigin(IMAGE_MIDDLE_PLAYER, 0.f);
        if (player.getsprite().getScale().x == -1)
        {
            player.setScale(1);

        }
        player.setPosition(sf::Vector2f(spaceShip.getLocation().x, spaceShip.getLocation().y + 70));

        player.setScale(player.getsprite().getScale().x - 0.2);
        Sleep(50);

        if (player.getsprite().getScale().x < 0.2)
        {
            ImageAndAudio::instance().playSound(Sound::LOSE2);

            player.setPosition(sf::Vector2f(player.getLocation().x, player.getLocation().y + 2000));
        }
    }
}

void playerCoin(ObjectAbstract& playerObj,
    ObjectAbstract& CoinObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    Coin& coin = dynamic_cast<Coin&>(CoinObj);
    {
        coin.setIfDeleted(true);
        Player::m_collectedCoin++;
    }
}

void playerEnd(ObjectAbstract& playerObj,
    ObjectAbstract& endStickObj)
{
    Player& player = dynamic_cast<Player&>(playerObj);
    EndLevelStick& endStick = dynamic_cast<EndLevelStick&>(endStickObj);
    sf::Sprite checkSprite = player.getsprite();
    checkSprite.setScale(float(0.4), float(0.4));

    if (checkSprite.getGlobalBounds().intersects(player.getsprite().getGlobalBounds()))
    {
        if (player.getSide() == SideToMove::DOWN && player.getLocation().y < endStick.getLocation().y)
        {
            player.setSide(SideToMove::DOWN);
            player.setUpLimit(1000);
            player.setUpPass(-700);
        }
        else if (player.getSide() == SideToMove::DOWN && !endStick.getsprite().getGlobalBounds().contains(player.getLocation().x, player.getLocation().y + PLAYER_HEIGHT))
        {
            player.setSide(SideToMove::UP);
        }
        else if (player.getSide() == SideToMove::DOWN && endStick.getsprite().getGlobalBounds().contains(player.getLocation().x, player.getLocation().y)
            && endStick.getsprite().getGlobalBounds().contains(player.getLocation().x, player.getLocation().y + PLAYER_HEIGHT))
        {
            player.setLevelPass(true);
        }
        if (Player::m_wear == Skin::jetpack)
        {
            player.setUpPass(200);
        }
    }
}
void bulletEnemy(ObjectAbstract& bulletObj,
    ObjectAbstract& monster)
{
    Bullet& bullet = dynamic_cast<Bullet&>(bulletObj);
    EnemyMonster& enmey = dynamic_cast<EnemyMonster&>(monster);

    enmey.setIfDeleted(true);
}

void bulletEnemyShip(ObjectAbstract& bulletObj,
    ObjectAbstract& monster)
{
    Bullet& bullet = dynamic_cast<Bullet&>(bulletObj);
    EnemySpaceship& ship = dynamic_cast<EnemySpaceship&>(monster);

    ship.setIfDeleted(true);
}

void bulletEnemyHole(ObjectAbstract& bulletObj,
    ObjectAbstract& monster)
{
    Bullet& bullet = dynamic_cast<Bullet&>(bulletObj);
    EnemyHole& enmey = dynamic_cast<EnemyHole&>(monster);

    bullet.setIfDeleted(true);
}


HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Player), typeid(StaticStick   ))] = &playerStatic;
    phm[Key(typeid(Player), typeid(MoveStick     ))] = &playerStatic;
    phm[Key(typeid(Player), typeid(DisappearStick))] = &playerDisappear;
    phm[Key(typeid(Player), typeid(BrokenStick   ))] = &playerBroken;
    phm[Key(typeid(Player), typeid(EnemyMonster  ))]=  &playerMonster;
    phm[Key(typeid(Player), typeid(EnemySpaceship))] = &playerSpaceShip;
    phm[Key(typeid(Player), typeid(EnemyHole     ))] = &playerHole;
    phm[Key(typeid(Player), typeid(Coin          ))] = &playerCoin;
    phm[Key(typeid(Player), typeid(Spring        ))] = &playerSpring;
    phm[Key(typeid(Player), typeid(EndLevelStick ))] = &playerEnd;
    phm[Key(typeid(Player), typeid(Jetpack       ))] = &playerJetpack;
    phm[Key(typeid(Bullet), typeid(EnemyMonster  ))] = &bulletEnemy;
    phm[Key(typeid(Bullet), typeid(EnemySpaceship))] = &bulletEnemyShip;
    phm[Key(typeid(Bullet), typeid(EnemyHole     ))] = &bulletEnemyHole;
    

    //...
    return phm;
}

HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace

void processCollision(ObjectAbstract& object1, ObjectAbstract& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        return;
    }
    phf(object1, object2);
}
