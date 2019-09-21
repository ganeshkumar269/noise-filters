#include<SFML/Graphics.hpp>
#include<iostream>
#include "d:\mytimer.cpp"
#include "stdsfmllib.h"
int main(){
    std::cout<<"Hello, World!"<<std::endl;
    sf::RenderWindow window(sf::VideoMode(300,300),"New Window",sf::Style::Default);
    sf::RectangleShape rectangle(sf::Vector2f(30,30));
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image image;
    sf::Image croppedImage;


    if (!image.loadFromFile("./parking_lot.jpg"))
        std::cout<<"Error in opening Image"<<std::endl;
    
    {
        Timer timer;
        rgbToGray(image,{0,0,300,300});
        std::cout<<"Time taken for rgb to Gray conversion: ";
    }
    sf::Image orgImage = image;
    {
        Timer timer;
        sf::Image tmp = image;
        boxFilter(tmp,3,{0,0,300,300});
        std::cout<<"Time Taken for Box Filter Operation : ";
    }

    {
        Timer timer;
        sf::Image tmp = image;
        minFilter(tmp,3,{0,0,300,300});
        std::cout<<"Time Taken for Mix Filter Operation : ";
    }
    {
        Timer timer;
        sf::Image tmp = image;
        medianFilter(tmp,3,{0,0,300,300});
        std::cout<<"Time taken for Medain Filter Operation :";
        image = tmp;
    }
    texture.loadFromImage(image,sf::IntRect(0,0,300,300));
    sprite.setTexture(texture);

    unsigned int boxSize = 3;
    unsigned int prevSize = 3;
    std::cout<<"Window Opened"<<std::endl;
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
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            prevSize = boxSize;
            if(mousePosition.x < 150)
                boxSize = boxSize < 5 ? 3 : boxSize - 2;
            else
                boxSize += 2;
            std::cout<<boxSize<<std::endl;
        }
        if(prevSize != boxSize){
            sf::Image tmp = orgImage;
            medianFilter(tmp,boxSize,{0,0,300,300});
            texture.loadFromImage(tmp,{0,0,300,300});
            sprite.setTexture(texture);
            prevSize = boxSize;
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
