
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


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

sf::Mutex mutex;


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
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text textTime("Hello World", font, 50);
    textTime.setFillColor(sf::Color::Red);

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
    
    
    // deactivate its OpenGL context
    //window.setActive(false);
    
    // launch the rendering thread
    //sf::Thread thread(&renderingThread, &window);
    //thread.launch();
    
    sf::CircleShape shape(50);
    
    shape.setFillColor(sf::Color::Green);
    
    shape.setOutlineThickness(5);
    
    shape.setOutlineColor(sf::Color::Blue);
    
    shape.setPosition(window.getSize().x/2, window.getSize().y/2);
    
    //sf::CircleShape proj(10);
    
    //proj.setFillColor(sf::Color::White);
    
    bool upB, downB, leftB, rightB;
    
    upB=false;
    downB=false;
    leftB=false;
    rightB=false;

    double xDiff=0, yDiff=0;
    
    Projectiles::Projectiles projectiles;
    
    Meteors::Meteors meteors;
    
    double timeHolder=0;
    
    bool running=true;
    
    
    while (running) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
                running=false;
            }
            else if (event.type==sf::Event::KeyPressed){
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
            else if (event.type==sf::Event::MouseButtonPressed){
                sf::CircleShape temp(10);
                double xOrig=shape.getPosition().x+shape.getRadius();
                double yOrig=shape.getPosition().y+shape.getRadius();
                temp.setPosition(xOrig, yOrig);
                xDiff=event.mouseButton.x-temp.getRadius()-xOrig;
                yDiff=event.mouseButton.y-temp.getRadius()-yOrig;
                float norm=sqrt(xDiff*xDiff+yDiff*yDiff);
                float speed=1.5;
                xDiff=speed*xDiff/norm;
                yDiff=speed*yDiff/norm;
                projectiles.addProj(temp, xDiff, yDiff);
                
            }
            
        }
        if (upB && shape.getPosition().y>0) {shape.move(0, -1);}
        if (downB && shape.getPosition().y<window.getSize().y-2*shape.getRadius()) shape.move(0, 1);
        if (leftB && shape.getPosition().x>0) shape. move(-1, 0);
        if (rightB && shape.getPosition().x<window.getSize().x-2*shape.getRadius()) shape.move(1, 0);
        
        //proj.move(xDiff, yDiff);
        
        
        
        sf::Time elapsed = clock.getElapsedTime();
        double timeSecs=elapsed.asSeconds()+timeHolder;
        textTime.setString(std::to_string(timeSecs));
        
        double difficulty=1;
        
        if (clock.getElapsedTime().asSeconds()>0.5/difficulty) {
            meteors.randomMeteor(window);
            timeHolder+=clock.getElapsedTime().asSeconds();
            clock.restart();
        }
        //meteors.randomMeteor(window);
        
        projectiles.updateProjs();
        
        meteors.updateProjs();
        
        meteors.checkCollShots(projectiles.getProjs());
        
        window.clear();
        
        window.draw(textTime);
        
        window.draw(shape);
        
        //window.draw(proj);
        
        projectiles.drawProjs(window);
        
        meteors.drawProjs(window);
        
        if (meteors.checkCollision(shape)) {
            running=false;
        }
        
        window.display();
        
        
    }

    // Play the music
    //music.play();
    while (window.isOpen()) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear();
        sf::Text textEnd("GAME OVER", font, 150);
        textEnd.setFillColor(sf::Color::White);
        textEnd.setPosition((window.getSize().x-textEnd.getLocalBounds().width)/2, (window.getSize().y-textEnd.getLocalBounds().height)/2);
        window.draw(textEnd);
        window.draw(textTime);
        window.display();
        
    }

    return EXIT_SUCCESS;
}
