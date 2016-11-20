
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Projectiles.hpp"
#include "Meteors.hpp"
#include "Ship.hpp"
#include "PowerUps.hpp"
#include "Enemy.hpp"
#include "Enemies.hpp"


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int playRound(sf::RenderWindow &window);

void endRound(sf::RenderWindow &window, int endScore);

int Menu(sf::RenderWindow &window);


int main(int, char const**)
{
    sf::Clock clock;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML window");
    
    //sf::RenderWindow window2(sf::VideoMode(800,600),"My Window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    window.setPosition(sf::Vector2i(10,50));
    
    //window.setSize(sf::Vector2u(640, 480));

    window.setTitle("SFML window");
    
    //window.setVerticalSyncEnabled(true); // call it once, after creating the window

    // Load a sprite to display
    

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "background.wav")) {
        return EXIT_FAILURE;
    }
    
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    
    //sf::Window windowGL(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    
    // it works out of the box
    glEnable(GL_TEXTURE_2D);
    
    while (window.isOpen()) {
        
        music.play();
        
        Menu(window);
        
        int endScore = playRound(window);
        
        endRound(window, endScore);
    }
    
    

    return EXIT_SUCCESS;
}

int playRound(sf::RenderWindow &window){
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Clock clock;
    sf::Clock clockPerm;
    
    double timeLastShot=0;
    
    Ship::Ship ship(window.getSize().x/2, window.getSize().y/2);
    
    Projectiles::Projectiles projectiles;
    
    Meteors::Meteors meteors;
    
    PowerUps::PowerUps powerUps;
    
    Enemies::Enemies enemies;
    
    sf::Text textTime("Hello World", font, 50);
    textTime.setFillColor(sf::Color::Green);
    
    sf::Text textScore("Hello World", font, 50);
    textScore.setFillColor(sf::Color::Green);
    textScore.setPosition(window.getSize().x/2, 0);
    
    sf::Text textSpeed("ShotTime: 0.001", font, 50);
    textSpeed.setFillColor(sf::Color::Green);
    textSpeed.setPosition(window.getSize().x-textSpeed.getLocalBounds().width, 0);
    
    double timeSecs;
    double timeLastMeteor=0;
    double timeLastPowerUp=0;
    double timeLastEnemy=0;
    
    bool running=true;
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "c40000.png")) {
        return EXIT_FAILURE;
    }
    
    //sf::Texture texture;
    //texture.loadFromImage(image);
    
    //sf::Sprite sprite(texture);
    
    bool shooting=false;
    
    while (running) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
                running=false;
                exit(0);
            }
            else if (event.type==sf::Event::KeyPressed||event.type==sf::Event::KeyReleased){
                ship.moveShip(event);
            }
            else if (event.type==sf::Event::MouseButtonPressed){
                shooting=true;
            }
            else if (event.type==sf::Event::MouseButtonReleased){
                shooting=false;
            }
            
        }
        
        
        sf::Time elapsed = clock.getElapsedTime();
        timeSecs=elapsed.asSeconds();
        textTime.setString("Time: " + std::to_string(timeSecs).substr(0,4));
        
        textScore.setString("Score: " + std::to_string(ship.getScore()));
        //std::cout << "Speed: " + std::to_string(ship.getShotTime()) << std::endl;
        textSpeed.setString("shotTime: " + std::to_string(ship.getShotTime()).substr(0,3));
        
        double difficulty=1+timeSecs/10;
        
        if (timeSecs-timeLastMeteor>0.5/difficulty) {
            meteors.randomMeteor(window, 0.8*difficulty);
            timeLastMeteor=timeSecs;
        }
        
        if (timeSecs-timeLastPowerUp>5) {
            powerUps.randomPowerUp(window, 0.8);
            timeLastPowerUp=timeSecs;
        }
        
        if (timeSecs-timeLastEnemy>5) {
            enemies.addEnemy(window, 0.4);
            timeLastEnemy=timeSecs;
            enemies.shootAll(ship);
        }
        
        if ((timeSecs-timeLastShot>ship.getShotTime())&&shooting) {
            float xPos=ship.getMarker().getPosition().x;
            float yPos=ship.getMarker().getPosition().y;
            float rad=ship.getMarker().getRadius();
            //std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
            projectiles.shoot(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, xPos, yPos, rad);
            timeLastShot=timeSecs;
        }
        //meteors.randomMeteor(window);
        
        enemies.updateProjsSprites(window);
        
        enemies.checkForDeletion(window);
        
        enemies.checkCollShots(projectiles.getProjs(), ship);
        
        projectiles.updateProjs();
        
        //sf::Thread threadP(&Projectiles::updateProjs, &projectiles);
        //threadP.launch();
        
        projectiles.checkForDeletion(window);
        
        meteors.updateProjsSprites();
        
        meteors.checkForDeletionSprites(window);
        
        meteors.checkCollShots(projectiles.getProjs(), ship);
        
        powerUps.checkCollision(ship);
        
        powerUps.updateProjsSprites();
        
        powerUps.checkForDeletionSprites(window);
        
        ship.updateShip(window);
        
        if (meteors.checkCollision(ship.getMarker())||(enemies.checkCollision(ship.getMarker()))) {
            running=false;
        }
        
        
        
        //Clear and draw elements
        window.clear();
        
        ship.drawShip(window);
        window.draw(textTime);
        window.draw(textScore);
        window.draw(textSpeed);
        projectiles.drawProjs(window);
        meteors.drawProjsSprites(window);
        powerUps.drawProjsSprites(window);
        enemies.drawProjsSprites(window);
        //window.draw(sprite);
        
        window.display();
        
        
    }

    return ship.getScore();
}

void endRound(sf::RenderWindow &window, int endScore){
    bool ending=true;
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    while (ending) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type==sf::Event::KeyPressed||event.type==sf::Event::MouseButtonPressed){
                ending=false;
            }
        }
        
        window.clear();
        sf::Text textEnd("GAME OVER", font, 150);
        sf::Text textTime("SCORE: " + std::to_string(endScore),font, 150);
        textEnd.setFillColor(sf::Color::White);
        textEnd.setPosition((window.getSize().x-textEnd.getLocalBounds().width)/2, (window.getSize().y-textEnd.getLocalBounds().height)/2);
        textTime.setFillColor(sf::Color::White);
        textTime.setPosition((window.getSize().x-textTime.getLocalBounds().width)/2, (window.getSize().y+textEnd.getLocalBounds().height)/2);
        window.draw(textEnd);
        window.draw(textTime);
        window.display();
        
    }
    
    return EXIT_SUCCESS;
}

int Menu(sf::RenderWindow &window){
    
    bool menu=true;
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text textTitle("TURBO-METEOR", font, 150);
    sf::Text textOption1("NEW GAME",font, 150);
    textTitle.setFillColor(sf::Color::White);
    textTitle.setPosition((window.getSize().x-textTitle.getLocalBounds().width)/2, 0);
    textOption1.setFillColor(sf::Color::White);
    sf::Vector2f textPos((window.getSize().x-textOption1.getLocalBounds().width)/2, window.getSize().y/2);
    textOption1.setPosition(textPos);
    sf::RectangleShape option1Box(sf::Vector2f(textOption1.getLocalBounds().width*1.03,textOption1.getLocalBounds().height*1.05));
    option1Box.setFillColor(sf::Color::Transparent);
    option1Box.setPosition((window.getSize().x-textOption1.getLocalBounds().width)/2, window.getSize().y/2+textOption1.getLocalBounds().height*0.40);
    option1Box.setOutlineColor(sf::Color::White);
    option1Box.setOutlineThickness(10);
        
    while (menu) {
        
        sf::Event event;
        
        
        
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type==sf::Event::MouseButtonPressed){
                if ((textOption1.getPosition().x<event.mouseButton.x)&&(event.mouseButton.x<textOption1.getPosition().x+textOption1.getLocalBounds().width)) {
                    if ((textOption1.getPosition().y+textOption1.getLocalBounds().height/2<event.mouseButton.y)&&(event.mouseButton.y<textOption1.getPosition().y+3*textOption1.getLocalBounds().height/2)) {
                        textOption1.setFillColor(sf::Color::Red);
                    }
                }
            }
            if (event.type==sf::Event::MouseButtonReleased){
                if ((textOption1.getPosition().x<event.mouseButton.x)&&(event.mouseButton.x<textOption1.getPosition().x+textOption1.getLocalBounds().width)) {
                    if ((textOption1.getPosition().y+textOption1.getLocalBounds().height/2<event.mouseButton.y)&&(event.mouseButton.y<textOption1.getPosition().y+3*textOption1.getLocalBounds().height/2)) {
                        menu=false;
                    }
                }
            }
        }
        
        window.clear();
        
        
        window.draw(option1Box);
        window.draw(textTitle);
        window.draw(textOption1);
        window.display();
        
    }
    
    return EXIT_SUCCESS;
}
