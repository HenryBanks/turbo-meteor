//
//  PowerUp.cpp
//  Test SFML
//
//  Created by Henry Banks on 04/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "PowerUp.hpp"

void PowerUp::randomPowerUp(sf::RenderWindow &window, float speed){
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

bool PowerUp::checkCollision(sf::CircleShape target){
    for (auto &meteor: getProjs()){
        double m_x=meteor.getPosition().x+meteor.getRadius();
        double t_x=target.getPosition().x+target.getRadius();
        double m_y=meteor.getPosition().y+meteor.getRadius();
        double t_y=target.getPosition().y+target.getRadius();
        double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
        //std::cout << distance << std::endl;
        if (distance<(target.getRadius()+meteor.getRadius())) {
            return true;
        }
    }
    return false;
}