#include "SFML/Graphics.hpp"
#include "mysf.hpp"
#include <algorithm>
#include <cmath>
#include <future>

namespace mysf {
    //Variance = Sigma(x*(x-2mean) + mean^2) = Sigma(x*(x-2mean)) + Sigma(mean*mean)
    double firstPartOfSigma(sf::Image& image,sf::IntRect dimension,double mean){
        if(dimension.height == -1 or dimension.width == -1){
                dimension.height = image.getSize().y;
                dimension.width = image.getSize().x;
                dimension.left = dimension.top = 0;
        } 
        double sum = 0.0;
        for(unsigned int i = dimension.top ;i < (uint32_t)dimension.top +  dimension.height; i++)
            for(unsigned int j = dimension.left ; j < (uint32_t)dimension.left + dimension.width ; j++){
                double t = image.getPixel(j,i).r*0.34 + image.getPixel(j,i).g*0.33 + image.getPixel(j,i).b*0.33;
                sum += t*(t-2*mean);
            }
        return sum;
    }



    double variance(sf::Image& image,sf::IntRect dimension,double mean){
        if(dimension.height == -1 or dimension.width == -1){
                dimension.height = image.getSize().y;
                dimension.width = image.getSize().x;
                dimension.left = dimension.top = 0;
        } 
        if(mean == -1)  mean = mysf::mean(image,dimension);
        double firstPart = firstPartOfSigma(image,dimension,mean);
        double secondPart = dimension.height*dimension.width*mean*mean;
        return (firstPart+secondPart)/(dimension.height*dimension.width);
    }
    double variance_MT(sf::Image& image,sf::IntRect dimension){
        if(dimension.height == -1 or dimension.width == -1){
                dimension.height = image.getSize().y;
                dimension.width = image.getSize().x;
                dimension.left = dimension.top = 0;
        } 
        sf::IntRect dim1 = {dimension.left,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim2 = {dimension.left+dimension.width/2,dimension.top,dimension.width/2,dimension.height/2};
        sf::IntRect dim3 = {dimension.left,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
        sf::IntRect dim4 = {dimension.left+dimension.width/2,dimension.top+dimension.height/2,dimension.width/2,dimension.height/2};
        double mean_ = mysf::mean_MT(image,dimension);
        std::future<double> t1 = std::async(std::launch::async, variance,std::ref(image),dim1,mean_);
        std::future<double> t2 = std::async(std::launch::async, variance,std::ref(image),dim2,mean_);
        std::future<double> t3 = std::async(std::launch::async, variance,std::ref(image),dim3,mean_);
        std::future<double> t4 = std::async(std::launch::async, variance,std::ref(image),dim4,mean_);
        
        return (t1.get()+t2.get()+t3.get()+t4.get())/4;
    }

    double standard_deviation(sf::Image& image,sf::IntRect dimension){
        return std::sqrt((double)variance(image,dimension));
    }

}