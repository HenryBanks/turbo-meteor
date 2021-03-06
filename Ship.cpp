//
//  Ship.cpp
//  Test SFML
//
//  Created by Henry Banks on 04/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Ship.hpp"

Ship::Ship(){

}

Ship::Ship(float xPos, float yPos){

    double radius=45.5;

    markerShip.setRadius(radius);

    markerShip.setFillColor(sf::Color::Transparent);

    markerShip.setOutlineThickness(5);

    markerShip.setOutlineColor(sf::Color::Blue);

    markerShip.setPosition(xPos, yPos);

    upB=false;
    downB=false;
    leftB=false;
    rightB=false;

    shotTime=0.5;

    if (!texture.loadFromFile(resourcePath() + "ufoGreen.png")) {
        return;// EXIT_FAILURE;
    }

    sprite.setTexture(texture);

    //sprite.setScale(100, 100);


    sprite.setPosition(xPos, yPos);

    score=0;

    speed=1;

}

Ship::~Ship(){

}

void Ship::drawShip(sf::RenderWindow &window){
    window.draw(markerShip);
    window.draw(sprite);
}

void Ship::updateShip(sf::RenderWindow &window, float elapsedTime){
    float dis=elapsedTime*speed;
    if (upB && markerShip.getPosition().y>0) {
        markerShip.move(0, -dis);
        sprite.move(0, -dis);}
    if (downB && markerShip.getPosition().y<window.getSize().y-2*markerShip.getRadius()){
        markerShip.move(0, dis);
        sprite.move(0, dis);}
    if (leftB && markerShip.getPosition().x>0){
        markerShip.move(-dis, 0);
        sprite.move(-dis, 0);}
    if (rightB && markerShip.getPosition().x<window.getSize().x-2*markerShip.getRadius()){
        markerShip.move(dis, 0);
        sprite.move(dis, 0);}
}

void Ship::moveShip(sf::Event &event){

    if (event.type==sf::Event::KeyPressed){
        if (event.key.code==sf::Keyboard::Up||event.key.code==sf::Keyboard::W) {
            upB=true;
        }
        else if (event.key.code==sf::Keyboard::Down||event.key.code==sf::Keyboard::S) {
            downB=true;
        }
        else if (event.key.code==sf::Keyboard::Left||event.key.code==sf::Keyboard::A) {
            leftB=true;
        }
        else if (event.key.code==sf::Keyboard::Right||event.key.code==sf::Keyboard::D) {
            rightB=true;
        }
    }
    else if (event.type==sf::Event::KeyReleased){
        if (event.key.code==sf::Keyboard::Up||event.key.code==sf::Keyboard::W) {
            upB=false;
        }
        else if (event.key.code==sf::Keyboard::Down||event.key.code==sf::Keyboard::S) {
            downB=false;
        }
        else if (event.key.code==sf::Keyboard::Left||event.key.code==sf::Keyboard::A) {
            leftB=false;
        }
        else if (event.key.code==sf::Keyboard::Right||event.key.code==sf::Keyboard::D) {
            rightB=false;
        }
    }
}


sf::CircleShape Ship::getMarker(){
    return markerShip;
}

void Ship::setShotTime(float time){
    if (time>=minShotTime) {
        shotTime=time;
    }
}

float Ship::getMinShotTime(){
    return minShotTime;
}

float Ship::getShotTime(){
    return shotTime;
}

int Ship::getScore(){
    return score;
}

void Ship::setScore(int newScore){
    score=newScore;
}

int Ship::getSpeed(){
    return speed;
}

void Ship::setSpeed(int newSpeed){
    speed=newSpeed;
}
