#include "SFML/Graphics.hpp"
#include "mysf.hpp"
#include <thread>

namespace mysf {
    void grayToMono(sf::Image& image, unsigned int threshold,sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
        }
        for(unsigned int i = (uint32_t)dimension.top ;i < (uint32_t)dimension.top +  dimension.height; i++)
            for(unsigned int j = dimension.left ; j < (uint32_t)dimension.left + dimension.width ; j++)
                image.getPixel(j,i).r > threshold ? image.setPixel(j,i,sf::Color(255,255,255,255)):
                    image.setPixel(j,i,sf::Color(0,0,0,255));
    }

        
    void grayToMono_MT(sf::Image& image, unsigned int threshold,sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
        }
        sf::IntRect dim1 = {dimension.left,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim2 = {dimension.left+dimension.width/2,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim3 = {dimension.left,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
        sf::IntRect dim4 = {dimension.left+dimension.width/2,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};

        std::thread t1(grayToMono,std::ref(image),threshold,dim1);
        std::thread t2(grayToMono,std::ref(image),threshold,dim2);
        std::thread t3(grayToMono,std::ref(image),threshold,dim3);
        std::thread t4(grayToMono,std::ref(image),threshold,dim4);
        
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

}