#include "SFML/Graphics.hpp"
#include "mysf.hpp"
#include "misc.hpp"
// #include <future>

namespace mysf {
    double mean(sf::Image& image, sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
                dimension.height = image.getSize().y;
                dimension.width = image.getSize().x;
                dimension.left = dimension.top = 0;
        } 
        double sum = 0.0;
        for(unsigned int i = dimension.top ;i < (uint32_t)dimension.top +  dimension.height; i++)
            for(unsigned int j = dimension.left ; j < (uint32_t)dimension.left + dimension.width ; j++)
                sum += image.getPixel(j,i).r*0.34 + image.getPixel(j,i).g*0.33 + image.getPixel(j,i).b*0.33;
        return sum/(dimension.height*dimension.width);
    }

    // double mean_MT(sf::Image& image, sf::IntRect dimension){
    //     if(dimension.height == -1 or dimension.width == -1){
    //         dimension.height = image.getSize().y;
    //         dimension.width = image.getSize().x;
    //         dimension.left = dimension.top = 0;
    //     }
    //     sf::IntRect dim1 = {dimension.left,dimension.top,dimension.width/2,dimension.height/2};
    //     sf::IntRect dim2 = {dimension.left+dimension.width/2,dimension.top,dimension.width/2,dimension.height/2};
    //     sf::IntRect dim3 = {dimension.left,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
    //     sf::IntRect dim4 = {dimension.left+dimension.width/2,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};

    //     int coreCount = getCoreCount();
        

    //     std::future<double> t1 = std::async(std::launch::async, mean,std::ref(image),dim1);
    //     std::future<double> t2 = std::async(std::launch::async, mean,std::ref(image),dim2);
    //     std::future<double> t3 = std::async(std::launch::async, mean,std::ref(image),dim3);
    //     std::future<double> t4 = std::async(std::launch::async, mean,std::ref(image),dim4);
        
    //     return (t1.get()+t2.get()+t3.get()+t4.get())/4;
    // }
}