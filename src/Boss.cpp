#include <iostream>
#include "Boss.hpp"
#include "Projectile.h"
#include "PlanetDefenders.h"
using namespace PlanetDefenders;

Boss::~Boss()
{
    std::cout << "Boss removed" << std::endl;
    delete objSprite;
}

std::vector<Projectile*>* Boss::shoot(int num)
{
    // for demonstration
    double shootProbability = 0.8;
    double betweenZeroAndOne = ((double)rand() / RAND_MAX);
    sf::Time elapse_time = shootClock.getElapsedTime();
    std::vector<Projectile*>* shootArr = new std::vector<Projectile*>();
    sf::IntRect spriteRect;
    float spd = 0, damage;
    if (elapse_time >= BossShootTimeDelta + sf::milliseconds((betweenZeroAndOne) * 50))
    {
        shootClock.restart();
        if (betweenZeroAndOne < shootProbability)        // shoot
        {
            ProjectileType randType = static_cast<ProjectileType>(rand() % NumberOfProjectileType);
            switch (randType)
            {
            case RedCircle:
                spriteRect = ProjectileRedCircle;
                spd = ProjectileRedCircleSpd;
                damage = ProjectileRedCircleDamage;
                break;
            case RedSharp:
                spriteRect = ProjectileRedSharp;
                spd = ProjectileRedSharpSpd;
                damage = ProjectileRedSharpDamage;
                break;
            }
            for (int i = 0; i < num; i++) {
                float randomPos = rand() % 100 - 50;
                shootArr->push_back(new Projectile(
                    *objSprite->getTexture(),
                    spriteRect,
                    sf::Vector2f(
                        getSprite().getPosition() + sf::Vector2f(getSprite().getGlobalBounds().width / 2 + i * randomPos, getSprite().getGlobalBounds().height)
                    ),
                    sf::Vector2f(0, 1.0f),
                    spd,
                    BossProjectileDamage,
                    randType
                ));

            }
        }
    }
    return shootArr;
}

//update the hp bar to horizontal
void Boss::updateBossHpBarSize(int hp)
{
    bossHpBar.setSize(sf::Vector2f((float)hp * eachInterval, 33.f));
    std::cout << (float)hp << " " << eachInterval << std::endl;
    setHpText(hp);
}

void Boss::updateBossHpBarSize()
{
    updateBossHpBarSize(getHp());
}

void Boss::drawTo(sf::RenderWindow& window) {
    window.draw(bossHpBar);
    window.draw(hpText);
    window.draw(*objSprite);
}
void Boss::setHpText(int hp) {
    hpText = sf::Text(std::to_string(static_cast<int>(hp)) + "%", font);
    hpText.setPosition(sf::Vector2f(bossHpBar.getSize().x - 60.0f, -5));
}

