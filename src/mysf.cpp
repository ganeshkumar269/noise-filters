#include "SFML/Graphics.hpp"
#ifndef _GLIBCXX_IOSTREAM
    #include<iostream>
#endif
#include "mysf.h"
#include <Eigen/Dense>
#include <algorithm>

namespace mysf {



bool rgbToGray(sf::Image& image, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }
    for(unsigned int i = dimension.top ;i <  dimension.top + dimension.height; i++)
        for(unsigned int j = dimension.left ; j <  dimension.left + dimension.width ; j++){
            if(j >= image.getSize().x or i >= image.getSize().y)
                return false;
            else{
                sf::Color pixel = image.getPixel(j,i);
                float gray_value_float = (float)0.3*pixel.r 
                        + (float)0.59*pixel.b + (float)0.11*pixel.g ;
                unsigned int gray_value = (unsigned int)gray_value_float;
                image.setPixel(j,i,sf::Color(gray_value,gray_value,gray_value,255));
            }
        }
    return true;
}


bool grayToMono(sf::Image& image, unsigned int threshold,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }
    for(unsigned int i = dimension.top ;i < dimension.top +  dimension.height; i++)
        for(unsigned int j = dimension.left ; j < dimension.left + dimension.width ; j++){
            if(image.getPixel(j,i).r > threshold)
                image.setPixel(j,i,sf::Color(255,255,255,255));
            else
                image.setPixel(j,i,sf::Color(0,0,0,255));
        }
    return true;
}

double mean(sf::Image& image, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
    } 
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd image_matrix = Eigen::MatrixXd::Zero(height,width);
    for(unsigned int i = dimension.top ;i < dimension.top +  dimension.height; i++)
        for(unsigned int j = dimension.left ; j < dimension.left + dimension.width ; j++)
            image_matrix(i,j) = image.getPixel(j,i).r;
    return image_matrix.mean();
}

double variance(sf::Image& image,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
            dimension.height = image.getSize().y;
            dimension.width = image.getSize().x;
            dimension.left = dimension.top = 0;
    } 
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd image_matrix = Eigen::MatrixXd::Zero(height,width);
    for(unsigned int i = dimension.top ;i < dimension.top +  dimension.height; i++)
        for(unsigned int j = dimension.left ; j < dimension.left + dimension.width ; j++)
            image_matrix(i,j) = image.getPixel(j,i).r;
    Eigen::MatrixXd transformed_matrix = (image_matrix - 
                Eigen::MatrixXd::Constant(dimension.height,dimension.width,image_matrix.mean()));

    return (transformed_matrix.transpose()*transformed_matrix).diagonal().mean();
}


}