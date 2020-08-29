#include "SFML/Graphics.hpp"
#include "mysf.hpp"
#include <thread>

namespace mysf {
    void rgbToGray(sf::Image& image, sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
        }
        for(unsigned int i = dimension.top ;i <  (uint32_t)dimension.top + dimension.height; i++)
            for(unsigned int j = dimension.left ; j <  (uint32_t)dimension.left + dimension.width ; j++){
                    sf::Color pixel = image.getPixel(j,i);
                    float gray_value_float = (float)0.3*pixel.r + (float)0.59*pixel.b + (float)0.11*pixel.g ;
                    unsigned int gray_value = (unsigned int)gray_value_float;
                    image.setPixel(j,i,sf::Color(gray_value,gray_value,gray_value,255));
            }
    }


    void rgbToGray_MT(sf::Image& image, sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
        }
        sf::IntRect dim1 = {dimension.left,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim2 = {dimension.left+dimension.width/2,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim3 = {dimension.left,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
        sf::IntRect dim4 = {dimension.left+dimension.width/2,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
        
        std::thread t1(rgbToGray,std::ref(image),dim1);
        std::thread t2(rgbToGray,std::ref(image),dim2);
        std::thread t3(rgbToGray,std::ref(image),dim3);
        std::thread t4(rgbToGray,std::ref(image),dim4);
        
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}
