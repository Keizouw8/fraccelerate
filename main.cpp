#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int displayWidth = 500, viewWidth = displayWidth;
int displayHeight = 600, viewHeight = displayHeight;
int originX, originY;
sf::Image fractalImage;
sf::Texture fractalTexture;
siv::PerlinNoise perlin { 123456u };

sf::Sprite generateFractal(){
    fractalImage.create(displayWidth, displayHeight, sf::Color::Green);

    for(int x = 0; x < displayWidth; x++){
        for(int y = 0; y < displayHeight; y++){
            double value = perlin.noise2D_01(originX + x * viewWidth / displayWidth / 10, originY + y * viewHeight / displayHeight / 10) * 255;
            fractalImage.setPixel(x, y, sf::Color(value, value, value, 255));
        }
    }
    
    fractalTexture.loadFromImage(fractalImage);
    
    sf::Sprite fractalSprite;
    fractalSprite.setPosition(300, 0);
    fractalSprite.setTexture(fractalTexture);

    return fractalSprite;
}

int main(){
    std::cout.flush();
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
                std::cout << viewWidth << ", " << displayWidth << ", " << viewHeight << ", " << displayHeight << std::endl;
                defaultView.setSize(sf::Vector2f((float)event.size.width, (float)event.size.height));
                defaultView.setCenter(event.size.width/2, event.size.height/2);
                window.setView(defaultView);
                sidebar.setSize(sf::Vector2f(300, event.size.height));
                fractalSprite = generateFractal();
            }
        }

        window.clear();
        window.draw(fractalSprite);
        window.draw(sidebar);
        window.draw(title);
        window.display();
    }

    return 0;
}