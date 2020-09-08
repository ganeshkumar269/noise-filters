#include "noisemodels.hpp"
#include <random>
#include <SFML/Graphics.hpp>
void addUniformNoise(sf::Image& image){
    std::mt19937 mt;
    std::uniform_real_distribution<float> ud(0,1);
    for(uint32_t x = 0;x < image.getSize().x;x++)
        for(uint32_t y = 0;y < image.getSize().y;y++){
            sf::Color tmp = image.getPixel(x,y);
            tmp.r += ud(mt)*255.0f;
            tmp.g += ud(mt)*255.0f;
            tmp.b += ud(mt)*255.0f;
            tmp.a += ud(mt)*255.0f;
            image.setPixel(x,y,tmp);
        }
}