//
//  Projectiles.cpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Projectiles.hpp"

Projectiles::Projectiles(){
    if (!texture.loadFromFile(resourcePath() + "c40000.png")) {
        return EXIT_FAILURE;
    }
}

Projectiles::~Projectiles(){
    
}

void Projectiles::addProj(sf::CircleShape newProj, float xMove, float yMove){
    vecProjs.push_back(newProj);
    if (vecProjs.size()>=50){
        vecProjs.erase(vecProjs.begin());
        vecVels.erase(vecVels.begin());
    }
    std::vector<float> temp;
    temp.push_back(xMove);
    temp.push_back(yMove);
    vecVels.push_back(temp);
}

void Projectiles::addProjSprite(sf::CircleShape newProj, float xMove, float yMove){
    vecProjs.push_back(newProj);
    if (vecProjs.size()>=50){
        vecProjs.erase(vecProjs.begin());
        vecVels.erase(vecVels.begin());
    }
    std::vector<float> temp;
    temp.push_back(xMove);
    temp.push_back(yMove);
    vecVels.push_back(temp);
    
    sf::Sprite sprite(texture);
    sprite.setPosition(newProj.getPosition().x-2*newProj.getRadius(), newProj.getPosition().y-2*newProj.getRadius());
    vecSprites.push_back(sprite);
}

void Projectiles::drawProjs(sf::RenderWindow &window){
    for ( auto &proj : vecProjs ) {
        window.draw(proj);
    }

}

void Projectiles::drawProjsSprites(sf::RenderWindow &window){
    for ( auto &proj : vecProjs ) {
        window.draw(proj);
    }
    for (auto &sprite: vecSprites) {
        window.draw(sprite);
    }
}

void Projectiles::updateProjs(){
    for (int i=0; i<vecProjs.size(); i++) {
        vecProjs[i].move(vecVels[i][0], vecVels[i][1]);
    }
}

void Projectiles::updateProjsSprites(){
    for (int i=0; i<vecProjs.size(); i++) {
        vecProjs[i].move(vecVels[i][0], vecVels[i][1]);
        vecSprites[i].move(vecVels[i][0], vecVels[i][1]);
    }
}

std::vector<sf::CircleShape> Projectiles::getProjs(){
    return vecProjs;
}

void Projectiles::checkForDeletion(sf::RenderWindow &window){
    for (int i=0; i<vecProjs.size(); i++) {
        sf::CircleShape proj=vecProjs[i];
        float xloc=proj.getPosition().x;
        float yloc=proj.getPosition().y;
        if (xloc>window.sf::Window::getSize().x||xloc<0) {
            vecProjs.erase(vecProjs.begin()+i);
            vecVels.erase(vecVels.begin()+i);
        }
        else if(yloc>window.sf::Window::getSize().y||yloc<0) {
            vecProjs.erase(vecProjs.begin()+i);
            vecVels.erase(vecVels.begin()+i);
        }
    }
}

void Projectiles::checkForDeletionSprites(sf::RenderWindow &window){
    for (int i=0; i<vecProjs.size(); i++) {
        sf::CircleShape proj=vecProjs[i];
        float xloc=proj.getPosition().x;
        float yloc=proj.getPosition().y;
        if (xloc>window.sf::Window::getSize().x||xloc<0) {
            vecProjs.erase(vecProjs.begin()+i);
            vecVels.erase(vecVels.begin()+i);
            vecSprites.erase(vecSprites.begin()+i);
        }
        else if(yloc>window.sf::Window::getSize().y||yloc<0) {
            vecProjs.erase(vecProjs.begin()+i);
            vecVels.erase(vecVels.begin()+i);
            vecSprites.erase(vecSprites.begin()+i);
        }
    }
}

int Projectiles::getNumProjs(){
    return vecProjs.size();
}

void Projectiles::shoot(float xf, float yf, float xi, float yi, float rad){
    sf::CircleShape temp(10);
    double xOrig=xi+rad;
    double yOrig=yi+rad;
    temp.setPosition(xOrig, yOrig);
    float xDiff=xf-temp.getRadius()-xOrig;
    float yDiff=yf-temp.getRadius()-yOrig;
    float norm=sqrt(xDiff*xDiff+yDiff*yDiff);
    float speed=1.5;
    xDiff=speed*xDiff/norm;
    yDiff=speed*yDiff/norm;
    addProj(temp, xDiff, yDiff);
}

void Projectiles::shootSpecial(sf::Event event, sf::CircleShape markerShip){
    if (event.type==sf::Event::MouseButtonPressed){
        sf::CircleShape temp(10);
        double xOrig=markerShip.getPosition().x+2*markerShip.getRadius();
        double yOrig=markerShip.getPosition().y*markerShip.getRadius();
        temp.setPosition(xOrig, yOrig);
        float xDiff=event.mouseButton.x-temp.getRadius()-xOrig;
        float yDiff=event.mouseButton.y-temp.getRadius()-yOrig;
        float norm=sqrt(xDiff*xDiff+yDiff*yDiff);
        float speed=1.5;
        xDiff=speed*xDiff/norm;
        yDiff=speed*yDiff/norm;
        addProj(temp, xDiff, yDiff);
        sf::CircleShape temp2(10);
        xOrig=markerShip.getPosition().x;
        yOrig=markerShip.getPosition().y+markerShip.getRadius();
        temp2.setPosition(xOrig, yOrig);
        xDiff=event.mouseButton.x-temp2.getRadius()-xOrig;
        yDiff=event.mouseButton.y-temp2.getRadius()-yOrig;
        norm=sqrt(xDiff*xDiff+yDiff*yDiff);
        xDiff=speed*xDiff/norm;
        yDiff=speed*yDiff/norm;
        addProj(temp2, xDiff, yDiff);
    }
}