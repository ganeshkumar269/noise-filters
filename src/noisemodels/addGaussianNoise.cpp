#include "SFML/Graphics.hpp"
#include <random>
#include "mysf.hpp"

bool savedValFlag = false;
float savedVal;

float nextGaussian(){
    //Marsagalia Polar Method on Box-Muller Transfrom to generate Gaussian Distribution
    if(savedValFlag) {
        savedValFlag = false;
        return savedVal;
    }
    float v1,v2,s;
    std::mt19937 mt;
    std::uniform_real_distribution<float> rng1(0,1);
    std::uniform_real_distribution<float> rng2(0,1);
    do{
        v1 = 2*rng1(mt) - 1.0f;
        v2 = 2*rng2(mt) - 1.0f;
        s = v1*v1 + v2*v2;
    }while(s > 1.0f || s == 0.f);
    s = std::sqrt((-2.0f*std::log(s))/s);
    savedValFlag = true;
    savedVal = s*v2;
    return v1*s;
}
float nextGaussian(float mean,float stddev){
    return mean+nextGaussian()*stddev;
}

void addGaussianNoise(sf::Image& image){
    float _mean_r = mysf::mean(image,0);
    float _mean_g = mysf::mean(image,1);
    float _mean_b = mysf::mean(image,2);
    float stddev_r = std::sqrt(mysf::variance(image,0));
    float stddev_g = std::sqrt(mysf::variance(image,1));
    float stddev_b = std::sqrt(mysf::variance(image,2));
    for(uint32_t x = 0;x < image.getSize().x;x++)
        for(uint32_t y = 0;y < image.getSize().y;y++){
            sf::Color tmp = image.getPixel(x,y);
            tmp.r += nextGaussian(_mean_r,stddev_r);
            tmp.g += nextGaussian(_mean_g,stddev_g);
            tmp.b += nextGaussian(_mean_b,stddev_b);
            // tmp.a += nextGaussian(_mean,stddev);
            image.setPixel(x,y,tmp);
        }
}