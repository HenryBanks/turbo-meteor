//
//  PowerUp.cpp
//  Test SFML
//
//  Created by Henry Banks on 04/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "PowerUps.hpp"

void PowerUps::randomPowerUp(sf::RenderWindow &window, float speed){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, window.getSize().x);
    float xStart, yStart, xMove, yMove;
    float xEnd, yEnd;
    xStart=dis(gen);
    xEnd=dis(gen);
    yStart=0;
    yEnd=window.sf::Window::getSize().y;
    xMove=xEnd-xStart;
    yMove=yEnd-yStart;
    float norm=sqrt(xMove*xMove+yMove*yMove);
    xMove=speed*xMove/norm;
    yMove=speed*yMove/norm;
    sf::CircleShape temp(20);
    temp.setFillColor(sf::Color::Blue);
    temp.setPosition(xStart, yStart);
    addProj(temp, xMove, yMove);
}

void PowerUps::checkCollision(Ship::Ship &ship){
    sf::CircleShape target=ship.getMarker();
    
    for (int i=0; i<vecProjs.size(); i++) {
        sf::CircleShape powerUp=vecProjs[i];
        double m_x=powerUp.getPosition().x+powerUp.getRadius();
        double t_x=target.getPosition().x+target.getRadius();
        double m_y=powerUp.getPosition().y+powerUp.getRadius();
        double t_y=target.getPosition().y+target.getRadius();
        double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
        //std::cout << distance << std::endl;
        if (distance<(target.getRadius()+powerUp.getRadius())) {
            ship.setMinShotTime(ship.getMinShotTime()/2);
            vecProjs.erase(vecProjs.begin()+i);
            vecVels.erase(vecVels.begin()+i);
        }
    }
}