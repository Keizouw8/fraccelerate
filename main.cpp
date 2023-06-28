#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Uint8* generateFractal(float x, float y, float width, float height){
    return new sf::Uint8[(int)(width * height * 4)];
}

int main(){
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

    sf::Texture fractalTexture;
    fractalTexture.update(generateFractal(0, 0, 500, 600));

    sf::Sprite fractalSprite;
    fractalSprite.setPosition(300, 0);
    fractalSprite.setTexture(fractalTexture);

    while(window.isOpen()){
        window.clear();
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::Resized){
                defaultView.setSize(sf::Vector2f((float)event.size.width, (float)event.size.height));
                defaultView.setCenter(event.size.width/2, event.size.height/2);
                sidebar.setSize(sf::Vector2f(300, event.size.height));
                window.setView(defaultView);
            }
        }

        window.draw(fractalSprite);
        window.draw(sidebar);
        window.draw(title);
        window.display();
    }

    return 0;
}