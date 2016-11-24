//
//  Projectiles.cpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Projectiles.hpp"

Projectiles::Projectiles(){
    if (!texture.loadFromFile(resourcePath() + "meteor.png")) {
        return EXIT_FAILURE;
    }
    if (!shotSoundBuffer.loadFromFile(resourcePath() + "blaster.wav")) {
        return EXIT_FAILURE;
    }
    shotSound.setBuffer(shotSoundBuffer);
    std::cout << "vecProjs max size: " << vecProjs.max_size() << std::endl;
}

Projectiles::~Projectiles(){
    
}

void Projectiles::addProj(sf::CircleShape newProj, float xMove, float yMove){
    vecProjs.push_back(newProj);
    if (vecProjs.size()>=50){
        vecProjs.erase(vecProjs.begin());
        vecVels.erase(vecVels.begin());
        vecSprites.erase(vecSprites.begin());
    }
    std::vector<float> temp;
    temp.push_back(xMove);
    temp.push_back(yMove);
    vecVels.push_back(temp);
}
/*
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
    double scaleUp=2.5*newProj.getRadius()/sprite.getLocalBounds().width;
    std::cout << "ScaleUp: " << scaleUp << std::endl;
    sprite.setScale(scaleUp, scaleUp);
    //sprite.setPosition(newProj.getPosition().x-2*newProj.getRadius(), newProj.getPosition().y-2*newProj.getRadius());
    sprite.setPosition(newProj.getPosition().x, newProj.getPosition().y);
    vecSprites.push_back(sprite);
}
*/
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

void Projectiles::updateProjs(float elapsedTime){
    for (int i=0; i<vecProjs.size(); i++) {
        vecProjs[i].move(vecVels[i][0]*elapsedTime, vecVels[i][1]*elapsedTime);
    }
}

void Projectiles::updateProjsSprites(float elapsedTime){
    for (int i=0; i<vecProjs.size(); i++) {
        vecProjs[i].move(vecVels[i][0]*elapsedTime, vecVels[i][1]*elapsedTime);
        vecSprites[i].move(vecVels[i][0]*elapsedTime, vecVels[i][1]*elapsedTime);
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
    shotSound.play();
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

bool Projectiles::checkCollision(sf::CircleShape target){
    for (auto &proj: getProjs()){
        double m_x=proj.getPosition().x+proj.getRadius();
        double t_x=target.getPosition().x+target.getRadius();
        double m_y=proj.getPosition().y+proj.getRadius();
        double t_y=target.getPosition().y+target.getRadius();
        double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
        //std::cout << distance << std::endl;
        if (distance<(target.getRadius()+proj.getRadius())) {
            return true;
        }
    }
    return false;
}

void Projectiles::checkCollShots(std::vector<sf::CircleShape> shotVec, Ship &ship){
    for (int i=0; i<vecProjs.size(); i++){
        sf::CircleShape proj = vecProjs[i];
        double m_x=proj.getPosition().x+proj.getRadius();
        double m_y=proj.getPosition().y+proj.getRadius();
        for (auto &shot: shotVec){
            double t_x=shot.getPosition().x+shot.getRadius();
            double t_y=shot.getPosition().y+shot.getRadius();
            double distance=sqrt((m_x-t_x)*(m_x-t_x)+(m_y-t_y)*(m_y-t_y));
            //std::cout << distance << std::endl;
            if (distance<(shot.getRadius()+proj.getRadius())) {
                std::cout << "vecProjs size: " << vecProjs.size() << std::endl;
                vecProjs.erase(vecProjs.begin()+i);
                vecVels.erase(vecVels.begin()+i);
                vecSprites.erase(vecSprites.begin()+i);
                ship.setScore(ship.getScore()+1);
            }
        }
    }
}