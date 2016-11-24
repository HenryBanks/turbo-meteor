//
//  Enemies.cpp
//  Test SFML
//
//  Created by Henry Banks on 13/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Enemies.hpp"
#include "ResourcePath.hpp"

Enemies::Enemies(){
    if (!texture.loadFromFile( resourcePath() + "ufoRed.png")) {
        //return EXIT_FAILURE;
    }
}

Enemies::~Enemies(){

}

void Enemies::drawProjsSprites(sf::RenderWindow &window){
    for ( auto &enemy : enemies ) {
        enemy.drawEnemy(window);
    }
}

void Enemies::updateProjsSprites(sf::RenderWindow &window, float elapsedTime){
    for ( auto &enemy : enemies){
        enemy.updateEnemy(window, elapsedTime);
    }
}

void Enemies::addEnemy(sf::RenderWindow &window,float speed){
    Enemy enemy(window,speed,texture);
    enemies.push_back(enemy);
}

void Enemies::checkForDeletion(sf::RenderWindow &window){
    for (int i=0; i<enemies.size(); i++) {
        sf::CircleShape shape=enemies[i].getMarker();
        float xloc=shape.getPosition().x;
        float yloc=shape.getPosition().y;
        if (xloc>window.sf::Window::getSize().x||xloc<0) {
            enemies.erase(enemies.begin()+i);
        }
        else if(yloc>window.sf::Window::getSize().y||yloc<0) {
            enemies.erase(enemies.begin()+i);
        }
    }
}

void Enemies::shootAll(Ship &ship){
    for (auto &enemy: enemies){
        enemy.shoot(ship);
    }
}

bool Enemies::checkCollision(sf::CircleShape target){
    for (auto &enemy: enemies){
        sf::CircleShape proj=enemy.getMarker();
        double m_x=proj.getPosition().x+proj.getRadius();
        double t_x=target.getPosition().x+target.getRadius();
        double m_y=proj.getPosition().y+proj.getRadius();
        double t_y=target.getPosition().y+target.getRadius();
        double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
        //std::cout << distance << std::endl;
        if (distance<(target.getRadius()+proj.getRadius())) {
            return true;
        }
        if (enemy.getProjs().checkCollision(target)){
            return true;
        }
    }
    return false;
}

void Enemies::checkCollShots(std::vector<sf::CircleShape> shotVec, Ship &ship){
    for (int i=0; i<enemies.size(); i++){
        sf::CircleShape proj = enemies[i].getMarker();
        double m_x=proj.getPosition().x+proj.getRadius();
        double m_y=proj.getPosition().y+proj.getRadius();
        for (auto &shot: shotVec){
            double t_x=shot.getPosition().x+shot.getRadius();
            double t_y=shot.getPosition().y+shot.getRadius();
            double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
            //std::cout << distance << std::endl;
            if (distance<(shot.getRadius()+proj.getRadius())) {
                enemies.erase(enemies.begin()+i);
                ship.setScore(ship.getScore()+5);
            }
        }
    }
}
