#include<SFML/Graphics.hpp>
#include<iostream>
#include "d:\mytimer.cpp"
#include "stdsfmllib.h"
int main(){
    std::cout<<"Hello, World!"<<std::endl;
    sf::RenderWindow window(sf::VideoMode(300,400),"New Window",sf::Style::Default);
    window.setFramerateLimit((unsigned int) (60));
    sf::RectangleShape rectangle(sf::Vector2f(30,30));
    sf::Vector2u windowSize = {300,300};
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image image;
    sf::Image orgImage;
    sf::Text max,min,median,box;
    sf::Font MontserratBold;
    MontserratBold.loadFromFile("Fonts/Montserrat-Bold.otf");
    max.setString("Max Filter");
    max.setFont(MontserratBold);
    max.setFillColor(sf::Color::White);
    max.setCharacterSize(25);
    max.setPosition(0,300);

    min.setString("Min Filter");
    min.setFont(MontserratBold);
    min.setFillColor(sf::Color::White);
    min.setCharacterSize(25);
    min.setPosition(150,300);

    median.setString("Med Filter");
    median.setFont(MontserratBold);
    median.setFillColor(sf::Color::White);
    median.setCharacterSize(25);
    median.setPosition(0,350);

    box.setString("Box Filter");
    box.setFont(MontserratBold);
    box.setFillColor(sf::Color::White);
    box.setCharacterSize(25);
    box.setPosition(150,350);

    if (!image.loadFromFile("./lil_owl.jpg"))
        std::cout<<"Error in opening Image"<<std::endl;
    std::cout<<"Image size : "<<image.getSize().x<<" "<<image.getSize().y<<std::endl;
    orgImage = image;
    unsigned int boxSize = 3;
    unsigned int prevSize = 3;
    std::cout<<"Window Opened"<<std::endl;


    sf::Clock clock;
    double delay = 0;
    double delay_time = 0.8;
    sf::Image tmp = orgImage;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed : 
                    window.close();
                    std::cout<<"Window Closed"<<std::endl;
                    break;
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
                        window.close();
                        std::cout<<"Window Closed"<<std::endl;
                        break;
                    }
                case sf::Event::MouseButtonReleased:{
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f translatedPos = window.mapPixelToCoords(mousePosition);
                    bool flag = false;
                    delay = clock.getElapsedTime().asSeconds();
                    if(delay > delay_time){
                        flag = true;
                        clock.restart();
                    } else continue;
                    tmp = orgImage;
                    if(max.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        maxFilter(tmp,boxSize);
                        std::cout<<"Time taken for Max filter:";
                    } else if(min.getGlobalBounds().contains(translatedPos)and flag){
                        Timer timer;
                        minFilter(tmp,boxSize);
                        std::cout<<"Time taken for Min filter:";
                    } else if(median.getGlobalBounds().contains(translatedPos)and flag){
                        Timer timer;
                        medianFilter(tmp,boxSize);
                        std::cout<<"Time taken for Median filter:";
                    } else if(box.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        boxFilter(tmp,boxSize);
                        std::cout<<"Time taken for Box filter:";
                    } else if(sprite.getGlobalBounds().contains(translatedPos) and flag){
                        prevSize = boxSize;
                        if(mousePosition.x < 150)
                            boxSize = boxSize < 5 ? 3 : boxSize - 2;
                        else
                            boxSize += 2;
                        std::cout<<"Box Size: "<<boxSize<<std::endl;
                    } else if(flag){
                        std::cout<<"Out of Bounds Click"<<std::endl;
                    }
                }
            }
        }
        texture.loadFromImage(tmp);
        sprite.setTexture(texture);
        sprite.setScale(windowSize.x/sprite.getLocalBounds().width , windowSize.y / sprite.getLocalBounds().height);
        window.clear();
        window.draw(sprite);
        window.draw(max);
        window.draw(min);
        window.draw(median);
        window.draw(box);
        window.display();
    }
    return 0;
}
