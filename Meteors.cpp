//
//  Meteors.cpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Meteors.hpp"

void Meteors::randomMeteor(sf::RenderWindow &window){
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
    float speed=0.8;
    xMove=speed*xMove/norm;
    yMove=speed*yMove/norm;
    sf::CircleShape temp(20);
    temp.setFillColor(sf::Color::Red);
    temp.setPosition(xStart, yStart);
    addProj(temp, xMove, yMove);
}

bool Meteors::checkCollision(sf::CircleShape target){
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

void Meteors::checkCollShots(std::vector<sf::CircleShape> shotVec){
    for (int i=0; i<vecProjs.size(); i++){
        sf::CircleShape meteor = vecProjs[i];
        double m_x=meteor.getPosition().x+meteor.getRadius();
        double m_y=meteor.getPosition().y+meteor.getRadius();
        for (auto &shot: shotVec){
            double t_x=shot.getPosition().x+shot.getRadius();
            double t_y=shot.getPosition().y+shot.getRadius();
            double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
            //std::cout << distance << std::endl;
            if (distance<(shot.getRadius()+meteor.getRadius())) {
                vecProjs.erase(vecProjs.begin()+i);
                vecVels.erase(vecVels.begin()+i);
            }
        }
    }
}