#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int displayWidth = 500, displayHeight = 600, viewWidth = displayWidth, viewHeight = displayHeight, originX = 0, originY = 0;

sf::Image fractalImage;
sf::Texture fractalTexture;
siv::PerlinNoise perlin { 123456u };

sf::Sprite generateFractal(){
    fractalImage.create(displayWidth, displayHeight, sf::Color::Green);

    for(int x = 0; x < displayWidth; x++){
        for(int y = 0; y < displayHeight; y++){
            double value = perlin.noise2D_01((originX + x * viewWidth / displayWidth), (originY + y * viewHeight / displayHeight)) * 255;
            fractalImage.setPixel(x, y, sf::Color(value, value, value));
        }
    }
    
    fractalTexture.loadFromImage(fractalImage);
    
    sf::Sprite fractalSprite;
    fractalSprite.setScale(1, 1);
    fractalSprite.setPosition(300, 0);
    fractalSprite.setTexture(fractalTexture);

    return fractalSprite;
}

int main(){
    std::cout.flush();

    sf::Vector2i previousMousePosition;
    sf::Clock scrollingClock;
    bool isScrolling = false;
    bool isDragging = false;

    sf::RenderWindow window(sf::VideoMode(800, 600), "fraccelerate");
    sf::View defaultView = window.getDefaultView();

    sf::Image icon;
    icon.loadFromFile("files/icon.jpg");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    sf::RectangleShape sidebar(sf::Vector2f(300, 600));
    sidebar.setFillColor(sf::Color(30, 30, 30));
    sidebar.setPosition(0, 0);

    sf::Font lexend;
    lexend.loadFromFile("files/lexend.ttf");

    sf::Text title;
    title.setFont(lexend);
    title.setString("fraccelerate");
    title.setCharacterSize(20);
    title.setPosition(10, 10);
    title.setFillColor(sf::Color::White);

    sf::Sprite fractalSprite = generateFractal();

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();

            if(event.type == sf::Event::Resized){
                viewWidth = std::max(1, (int)ceil(viewWidth * (int)ceil(event.size.width - 300) / displayWidth));
                viewHeight = std::max(1, (int)ceil(viewHeight * (int)ceil(event.size.height) / displayHeight));
                displayWidth = (int)ceil(std::max(1, (int)event.size.width - 300));
                displayHeight = std::max(1, (int)ceil(event.size.height));

                defaultView.setSize(sf::Vector2f((float)event.size.width, (float)event.size.height));
                defaultView.setCenter(event.size.width/2, event.size.height/2);
                window.setView(defaultView);
                sidebar.setSize(sf::Vector2f(300, event.size.height));
                
                fractalSprite = generateFractal();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) isDragging = true;
                previousMousePosition = sf::Mouse::getPosition(window);
            }

            if(event.type == sf::Event::MouseButtonReleased){
                if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isDragging){
                    isDragging = false;

                    if(!isScrolling){
                        sf::Vector2f scale = fractalSprite.getScale();
                        viewWidth /= scale.x;
                        viewHeight /= scale.y;

                        sf::Vector2f position = fractalSprite.getPosition();
                        originX -= position.x - 300;
                        originY -= position.y;

                        fractalSprite = generateFractal();
                    }
                }
            }

            if(event.type == sf::Event::MouseMoved){
                if(isDragging){
                    sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                
                    int changeX = currentMousePosition.x - previousMousePosition.x;
                    int changeY = currentMousePosition.y - previousMousePosition.y;
                    
                    fractalSprite.move(changeX, changeY);
                    previousMousePosition = currentMousePosition;
                }
            }

            if(event.type == sf::Event::MouseWheelScrolled){
                float zoom = event.mouseWheelScroll.delta;
                sf::Vector2f previousScale = fractalSprite.getScale();
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2u center = window.getSize();
                center.x = 300 + (center.x - 300) / 2;
                center.y = center.y / 2;
                
                isScrolling = true;
                scrollingClock.restart();

                fractalSprite.setScale(previousScale.x - zoom / 100, previousScale.y - zoom / 100);
                fractalSprite.move((mousePosition.x - (int)center.x)/20, (mousePosition.y - (int)center.y)/20);
            }else{
                if(isScrolling) if(scrollingClock.getElapsedTime().asMilliseconds() > 50){
                    isScrolling = false;

                    if(!isDragging){
                        sf::Vector2f scale = fractalSprite.getScale();
                        viewWidth /= scale.x;
                        viewHeight /= scale.y;

                        sf::Vector2f position = fractalSprite.getPosition();
                        originX -= position.x - 300;
                        originY -= position.y;

                        fractalSprite = generateFractal();
                    }
                }
            }
        }

        window.clear(sf::Color(200, 200, 200));
        window.draw(fractalSprite);
        window.draw(sidebar);
        window.draw(title);
        window.display();
    }

    return 0;
}