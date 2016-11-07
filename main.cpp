
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


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

sf::Mutex mutex;

double playRound(sf::RenderWindow &window);

void endRound(sf::RenderWindow &window, double endTime);

int Menu(sf::RenderWindow &window);

void func()
{
    // this function is started when thread.launch() is called
    mutex.lock();
    
    
    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread number one" << std::endl;
    
    mutex.unlock();
}

void renderingThread(sf::Window* window)
{
    // activate the window's context
    window->setActive(true);
    
    // the rendering loop
    while (window->isOpen())
    {
        // draw...
        
        // end the current frame -- this is a rendering function (it requires the context to be active)
        window->display();
    }
}




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
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
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
        
        
        Menu(window);
        
        double endTime = playRound(window);
        
        endRound(window, endTime);
    }
    
    

    return EXIT_SUCCESS;
}

double playRound(sf::RenderWindow &window){
    
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
    
    sf::Text textTime("Hello World", font, 50);
    textTime.setFillColor(sf::Color::Red);
    
    double timeSecs;
    double timeLastMeteor=0;
    double timeLastPowerUp=0;
    
    bool running=true;
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "c40000.png")) {
        return EXIT_FAILURE;
    }
    
    //sf::Texture texture;
    //texture.loadFromImage(image);
    
    //sf::Sprite sprite(texture);
    
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
                if (clockPerm.getElapsedTime().asSeconds()-timeLastShot>ship.getMinShotTime()) {
                    float xPos=ship.getMarker().getPosition().x;
                    float yPos=ship.getMarker().getPosition().y;
                    float rad=ship.getMarker().getRadius();
                    projectiles.shoot(event.mouseButton.x, event.mouseButton.y, xPos, yPos, rad);
                    timeLastShot=clockPerm.getElapsedTime().asSeconds();
                }
            }
            
        }
        
        
        sf::Time elapsed = clock.getElapsedTime();
        timeSecs=elapsed.asSeconds();
        textTime.setString(std::to_string(timeSecs));
        
        double difficulty=1+timeSecs/10;
        
        if (timeSecs-timeLastMeteor>0.5/difficulty) {
            meteors.randomMeteor(window, 0.8*difficulty);
            timeLastMeteor=timeSecs;
        }
        
        if (timeSecs-timeLastPowerUp>5) {
            powerUps.randomPowerUp(window, 0.8);
            timeLastPowerUp=timeSecs;
        }
        //meteors.randomMeteor(window);
        
        projectiles.updateProjs();
        
        //sf::Thread threadP(&Projectiles::updateProjs, &projectiles);
        //threadP.launch();
        
        projectiles.checkForDeletion(window);
        
        meteors.updateProjsSprites();
        
        meteors.checkCollShots(projectiles.getProjs());
        
        meteors.checkForDeletionSprites(window);
        
        powerUps.checkCollision(ship);
        
        powerUps.updateProjs();
        
        powerUps.checkForDeletion(window);
        
        ship.updateShip(window);
        
        if (meteors.checkCollision(ship.getMarker())) {
            running=false;
        }
        
        
        
        //Clear and draw elements
        window.clear();
        
        ship.drawShip(window);
        window.draw(textTime);
        projectiles.drawProjs(window);
        meteors.drawProjsSprites(window);
        powerUps.drawProjs(window);
        //window.draw(sprite);
        
        window.display();
        
        
    }

    return timeSecs;
}

void endRound(sf::RenderWindow &window, double endTime){
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
            if (event.type==sf::Event::KeyPressed){
                ending=false;
            }
        }
        
        window.clear();
        sf::Text textEnd("GAME OVER", font, 150);
        sf::Text textTime("TIME: " + std::to_string(endTime),font, 150);
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
    sf::RectangleShape option1Box;
    textTitle.setFillColor(sf::Color::White);
    textTitle.setPosition((window.getSize().x-textTitle.getLocalBounds().width)/2, 0);
    textOption1.setFillColor(sf::Color::White);
    sf::Vector2f textPos((window.getSize().x-textOption1.getLocalBounds().width)/2, window.getSize().y/2);
    textOption1.setPosition(textPos);
    
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
