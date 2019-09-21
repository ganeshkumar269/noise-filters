#include <SFML/Graphics.hpp>
#include "stdsfmllib.h"
#include <Eigen/Dense>
#include <algorithm>
bool rgbToGray(sf::Image& image, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }
    for(unsigned int i = dimension.top ;i < dimension.height; i++)
        for(unsigned int j = dimension.left ; j < dimension.width ; j++){
            float gray_value_float = (float)0.3*image.getPixel(i,j).r 
                    + (float)0.59*image.getPixel(i,j).b + (float)0.11*image.getPixel(i,j).g ;
            unsigned int gray_value = (unsigned int)gray_value_float;
            image.setPixel(i,j,sf::Color(gray_value,gray_value,gray_value,255));
        }
    return true;
}


bool grayToMono(sf::Image& image, unsigned int threshold,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }
    for(unsigned int i = dimension.top ;i < dimension.height; i++)
        for(unsigned int j = dimension.left ; j < dimension.width ; j++){
            if(image.getPixel(i,j).r > threshold)
                image.setPixel(i,j,sf::Color(255,255,255,255));
            else
                image.setPixel(i,j,sf::Color(0,0,0,255));
        }
    return true;
}


bool boxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height - dimension.top , width = dimension.width - dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(dimension.height - dimension.top + boxSize - 1, dimension.width - dimension.left + boxSize - 1);
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(i,j) = image.getPixel(dimension.top + i,dimension.left + j).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).sum()/float(boxSize*boxSize);
        image.setPixel(i - int(boxSize/2),j - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }   
    return true;
}


bool maxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height - dimension.top , width = dimension.width - dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(dimension.height - dimension.top + boxSize - 1, dimension.width - dimension.left + boxSize - 1);
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(i,j) = image.getPixel(dimension.top + i,dimension.left + j).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).maxCoeff();
        image.setPixel(i - int(boxSize/2),j - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }        
    return true;
}


bool minFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height - dimension.top , width = dimension.width - dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(dimension.height - dimension.top + boxSize - 1, dimension.width - dimension.left + boxSize - 1);
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(i,j) = image.getPixel(dimension.top + i,dimension.left + j).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).minCoeff();
        image.setPixel(i - int(boxSize/2),j - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        image.setPixel(i - int(boxSize/2),j - int(boxSize/2) , 
                        sf::Color(imageMatrix(i,j),imageMatrix(i,j),imageMatrix(i,j),255));
    return true;
}

bool medianFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height - dimension.top , width = dimension.width - dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(dimension.height - dimension.top + boxSize - 1, dimension.width - dimension.left + boxSize - 1);
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(i,j) = image.getPixel(dimension.top + i,dimension.left + j).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        Eigen::MatrixXd temp =imageMatrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).transpose();
        std::sort(temp.data(),temp.data() + boxSize*boxSize);
        unsigned int t = temp.data()[int(boxSize*boxSize/2)];
        image.setPixel(i - int(boxSize/2),j - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }
    return true;
}



