//
//  ToolBar.hpp
//  First_SFML
//
//  Created by rich_chan on 5/20/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#ifndef ToolBar_hpp
#define ToolBar_hpp
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "GameObject.hpp"
#include "PlanetDefenders.h"
#include "PowerUp.h"

using namespace PlanetDefenders;


class ToolBar 
{
    const unsigned int BAR_WIDTH = 300;
    const unsigned int BAR_HEIGHT = 720;

    sf::IntRect digitRects[10];
    sf::Sprite scoreSprites[3];
    sf::Sprite timeSprites[3];

    sf::Sprite hpBorderSp;
    sf::Sprite scoreSp;
    sf::Sprite timeSp;
    sf::Sprite activatedPowerUpContainerSp;
    sf::Sprite activatedPowerUpSp;
    PowerUp* activatedPowerUp;

    // Unused
    sf::Sprite cureSp;
    sf::Sprite protectSp;
    sf::Sprite shipSp;
    sf::Sprite addProtect;
    sf::Sprite deleteProtect;

    std::vector<GameObject*> shipNum;
    std::vector<GameObject*> thingNum;

    sf::Texture ToolBarTexture;
    sf::RectangleShape hpBar;
    sf::Clock timeClock;
    sf::Clock* powerUpClock;
    unsigned int powerUpDuration;
    sf::Font font;

    std::string countdownString;
    //GameText *timeText;
    int shipCount = 3;
    int protectTime;
    bool isProtect = false;
    unsigned int scoreCounter = 0;
    bool drawPowerUp = false;

    void generateDigitRects();
    void initializeHpBar(int hp);
    void updateScore();
    void updateTime();
    void updateShip();
    void updateActivatedPowerUp();
    void initializeSprites();

public:
    ToolBar(const sf::Vector2f& pos)
    {
        if(!ToolBarTexture.loadFromFile(TEXTURE_BASE_PATH + "toolbar.png"))
            std::cout << "cannot laod toolbar.png" << std::endl;
        initializeSprites();

    }
    int getShipCount() { return shipCount; }
    void addProtection(int num1);

    void addScore(unsigned int x) { scoreCounter += x; }
    void minusScore(int x) { scoreCounter -= x; }
    void updateHpBarSize(int hp);
    void setPowerUp(PowerUpEnum type, unsigned int duration);
    void update();
    void drawTo(sf::RenderWindow& window);
};
#endif /* ToolBar_hpp */