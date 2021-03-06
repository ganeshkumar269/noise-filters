#include <iostream>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "mytimer.cpp"

#include "mysf.hpp"
#include "noisefilters.hpp"
#include "noisemodels.hpp"

int main(int argc,char** argv){
    std::cout<<"Hello, World!"<<std::endl;
    sf::RenderWindow window(sf::VideoMode(300,500),"New Window",sf::Style::Default);
    window.setFramerateLimit((unsigned int) (60));
    sf::RectangleShape rectangle(sf::Vector2f(30,30));
    sf::Vector2u windowSize = {300,300};
    sf::Sprite sprite;
    sf::Sprite arrow_left,arrow_right;
    sf::Texture arrow_texture;
    sf::Image arrow_image;
    sf::Texture texture;
    sf::Image image,refImage;
    sf::Image orgImage;
    sf::Text max,min,median,box,gauss,reset,mono;
    sf::Font font;
    std::string path_to_image;
    std::string path_to_font;
    std::cout << "argc: " << argc <<std::endl;
    if(argc == 1){
        std::cout<<"Proper command is --> main.exe path_to_image path_to_font, using defualt values";
        path_to_image = "./resources/default.jpg";
        path_to_font = "./Fonts/default.otf";
    }
    else if(argv[1][0] == '-' && argv[1][1] == 'd'){
        path_to_image = "./resources/defaut.jpg";
        path_to_font = "./Fonts/defaut.otf";
    } else {
        path_to_image = argv[1];
        path_to_font = argv[2];
    }
    
    if(!font.loadFromFile(path_to_font.c_str()))
        std::cout<<"Filed to load Font"<<std::endl;
    if (!image.loadFromFile(path_to_image.c_str()))
        std::cout<<"Error in opening Image"<<std::endl;
    std::cout<<"Image size : "<<image.getSize().x<<" "<<image.getSize().y<<std::endl;

    max.setString("Max Filter");
    max.setFont(font);
    max.setFillColor(sf::Color::White);
    max.setCharacterSize(25);
    max.setPosition(0,300);

    min.setString("Min Filter");
    min.setFont(font);
    min.setFillColor(sf::Color::White);
    min.setCharacterSize(25);
    min.setPosition(150,300);

    median.setString("Med Filter");
    median.setFont(font);
    median.setFillColor(sf::Color::White);
    median.setCharacterSize(25);
    median.setPosition(0,350);

    box.setString("Box Filter");
    box.setFont(font);
    box.setFillColor(sf::Color::White);
    box.setCharacterSize(25);
    box.setPosition(150,350);

    gauss.setString("Gauss");
    gauss.setFont(font);
    gauss.setFillColor(sf::Color::White);
    gauss.setCharacterSize(25);
    gauss.setPosition(0,400);

    mono.setString("Mono");
    mono.setFont(font);
    mono.setFillColor(sf::Color::White);
    mono.setCharacterSize(25);
    mono.setPosition(150,400);

    reset.setString("Reset");
    reset.setFont(font);
    reset.setFillColor(sf::Color::White);
    reset.setCharacterSize(25);
    reset.setPosition(0,450);

    
    if(!arrow_texture.loadFromFile("./resources/arrow_right.jpg"))
        std::cout << "Error loading arrow texture " << std::endl;
    arrow_right.setTexture(arrow_texture);
    arrow_right.setScale(75/arrow_right.getLocalBounds().width , 50/arrow_right.getLocalBounds().height);
    arrow_right.setPosition(225,450);
    arrow_right.setOrigin(arrow_right.getGlobalBounds().width/2 ,arrow_right.getGlobalBounds().height/2);
    arrow_left = arrow_right;
    arrow_left.rotate(180);

    orgImage = image;
    refImage = image;
    // {
    //     Timer timer;
    //     mysf::rgbToGray(orgImage);
    //     mysf::rgbToGray(refImage);
    //     std::cout << "orgImage converted to gray in : ";
    // }
    unsigned int boxSize = 3;
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
                    if(max.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        // maxFilter(tmp,boxSize);
                        apply_filter(tmp,maxFilterReducer);
                        std::cout<<"Time taken for Max filter:";
                    } else if(min.getGlobalBounds().contains(translatedPos)and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        // minFilter(tmp,boxSize);
                        apply_filter(tmp,minFilterReducer);
                        std::cout<<"Time taken for Min filter:";
                    } else if(median.getGlobalBounds().contains(translatedPos)and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        medianFilter(tmp,boxSize);
                        std::cout<<"Time taken for Median filter:";
                    } else if(box.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        apply_filter(tmp,boxFilterReducer);
                        std::cout<<"Time taken for Box filter:";
                    } else if(gauss.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        addGaussianNoise(tmp);
                        orgImage = tmp;
                        std::cout<<"Time taken for Gauss Noise:";
                    } else if(gauss.getGlobalBounds().contains(translatedPos) and flag){
                        Timer timer;
                        std::cout<<"Filter Started."<<std::endl;
                        addUniformNoise(tmp);
                        orgImage = tmp;
                        std::cout<<"Time taken for Uniform Noise:";
                    }else if(sprite.getGlobalBounds().contains(translatedPos) and flag){
                        if(mousePosition.x < 150)
                            boxSize = boxSize < 5 ? 3 : boxSize - 2;
                        else
                            boxSize += 2;
                        std::cout<<"Box Size: "<<boxSize<<std::endl;
                    } else if(reset.getGlobalBounds().contains(translatedPos) and flag){
                        std::cout<<"Resetting to original gray image."<<std::endl;
                        tmp = refImage;
                    }else if(mono.getGlobalBounds().contains(translatedPos) and flag){ 
                        std::cout<<"Converting to Mono"<<std::endl;
                        mysf::rgbToGray(tmp);
                        mysf::grayToMono(tmp,mysf::mean(tmp));
                    }else if(flag){
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
        window.draw(gauss);
        window.draw(reset);
        window.draw(mono);
        // window.draw(arrow_right);
        // window.draw(arrow_left);
        window.display();
    }
    return 0;
}
