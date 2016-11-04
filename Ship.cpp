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
    
    markerShip.setRadius(50);
    
    markerShip.setFillColor(sf::Color::Green);
    
    markerShip.setOutlineThickness(5);
    
    markerShip.setOutlineColor(sf::Color::Blue);
    
    markerShip.setPosition(xPos, yPos);
    
    upB=false;
    downB=false;
    leftB=false;
    rightB=false;
}

Ship::~Ship(){
    
}

void Ship::drawShip(sf::RenderWindow &window){
    window.draw(markerShip);
}

void Ship::updateShip(sf::RenderWindow &window){
    if (upB && markerShip.getPosition().y>0) {markerShip.move(0, -1);}
    if (downB && markerShip.getPosition().y<window.getSize().y-2*markerShip.getRadius()) markerShip.move(0, 1);
    if (leftB && markerShip.getPosition().x>0) markerShip.move(-1, 0);
    if (rightB && markerShip.getPosition().x<window.getSize().x-2*markerShip.getRadius()) markerShip.move(1, 0);
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
