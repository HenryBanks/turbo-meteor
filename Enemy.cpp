//
//  Enemy.cpp
//  Test SFML
//
//  Created by Henry Banks on 13/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Enemy.hpp"

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

Enemy::Enemy(float xPos, float yPos){

    double radius=45.5;

    markerShip.setRadius(radius);

    markerShip.setFillColor(sf::Color::Transparent);

    markerShip.setOutlineThickness(5);

    markerShip.setOutlineColor(sf::Color::Blue);

    markerShip.setPosition(xPos, yPos);

    shotTime=0.5;

    if (!texture.loadFromFile(resourcePath() + "ufoRed.png")) {
        //return EXIT_FAILURE;
    }

    sprite.setTexture(texture);

    //sprite.setScale(100, 100);


    sprite.setPosition(xPos, yPos);

}

Enemy::Enemy(sf::RenderWindow &window, float speed, sf::Texture &texture){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, window.getSize().y);
    float xStart, yStart, xMove, yMove;
    float xEnd, yEnd;
    xStart=0;
    xEnd=window.getSize().x;
    yStart=dis(gen);
    yEnd=dis(gen);
    xMove=xEnd-xStart;
    yMove=yEnd-yStart;

    sprite.setTexture(texture);

    double radius=45.5;
    markerShip.setRadius(radius);
    float norm=sqrt(xMove*xMove+yMove*yMove);
    xMove=speed*xMove/norm;
    yMove=speed*yMove/norm;
    markerShip.setFillColor(sf::Color::Red);
    markerShip.setPosition(xStart, yStart);
    sprite.setPosition(xStart, yStart);
    velocity=sf::Vector2f(xMove,yMove);
}

void Enemy::drawEnemy(sf::RenderWindow &window){
    window.draw(markerShip);
    window.draw(sprite);
    enemyProjs.drawProjs(window);
}

void Enemy::updateEnemy(sf::RenderWindow &window,float elapsedTime){
    //std::cout << markerShip.getPosition().x << " " << markerShip.getPosition().y << std::endl;
    markerShip.move(velocity*elapsedTime);
    sprite.move(velocity*elapsedTime);
    enemyProjs.updateProjs(elapsedTime);
}

sf::CircleShape Enemy::getMarker(){
    return markerShip;
}

void Enemy::shoot(Ship &ship){
    float x_i=markerShip.getPosition().x;
    float y_i=markerShip.getPosition().y;
    float x_f=ship.getMarker().getPosition().x;
    float y_f=ship.getMarker().getPosition().y;
    float rad=markerShip.getRadius();
    enemyProjs.shoot(x_f, y_f, x_i, y_i, rad);

}

Projectiles Enemy::getProjs(){
    return enemyProjs;
}



