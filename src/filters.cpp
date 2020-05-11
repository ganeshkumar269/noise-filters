#include "SFML/Graphics.hpp"
#ifndef _GLIBCXX_IOSTREAM
    #include<iostream>
#endif
#include <Eigen/Dense>
#include <algorithm>
#include "gaussian_distribution.cpp"
#include "filters.h"




bool boxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){ 
    unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize)
                                        .sum()/float(boxSize*boxSize);
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }   
    return true;
}


bool maxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize).maxCoeff();
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }        
    return true;
}


bool minFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Constant(width + boxSize - 1, height + boxSize - 1,255);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize).minCoeff();
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }
    return true;
}


bool meanFilter(sf::Image& image,uint32_t boxSize, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.width = image.getSize().x;
        dimension.height = image.getSize().y;
        dimension.top = dimension.left = 0;
    }
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd image_matrix = Eigen::MatrixXd::Zero(dimension.height + boxSize + 1,dimension.width + boxSize + 1);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        image_matrix(i,j) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r; 
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        long mean = image_matrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).mean();
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(mean,mean,mean,255));
    }
    return true;
}



bool medianFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        return false;
    }
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;    
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        Eigen::MatrixXd temp =imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize).transpose();
        std::sort(temp.data(),temp.data() + boxSize*boxSize);
        unsigned int t = temp.data()[int(boxSize*boxSize/2)];
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }
    return true;
}

bool gaussianNoiseAdder(sf::Image& image,float mean,float variance,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }
    std::cout<< dimension.top << " " << dimension.height << " " << dimension.left << " " << dimension.width <<std::endl;
    unsigned int height = dimension.top + dimension.height , width = dimension.width + dimension.left;
    Eigen::MatrixXd image_matrix = Eigen::MatrixXd::Zero(dimension.height,dimension.width);
    for(unsigned int i = dimension.left ; i < width; i++)
        for(unsigned int j = dimension.top ; j < height ; j++)
            image_matrix(j,i) = image.getPixel(i,j).r; 
    // float mean = image_matrix.mean();
    // Eigen::MatrixXd mean_matrix  = Eigen::MatrixXd::Constant(dimension.height,dimension.width,mean); 
    // Eigen::MatrixXd diff_matrix = image_matrix - mean_matrix;
    // float variance = (diff_matrix.transpose()*diff_matrix).diagonal().sum() / (dimension.height*dimension.width);
    std::vector<float> gaussian_noise = mystdlib::gaussian_distribution(mean,variance,dimension.height*dimension.width);
    unsigned int t =0 ;
    for(unsigned int  j=dimension.top ; j <  height ; j++)
        for(unsigned int i = dimension.left; i < width ; i++,t++){
            std::tuple<int,int,int> color=  std::make_tuple(image.getPixel(i,j).r + (int)gaussian_noise[t],
                            image.getPixel(i,j).r + (int)gaussian_noise[t],image.getPixel(i,j).r + (int)gaussian_noise[t]);
    
            if(std::get<0>(color) < 0 ) std::get<0>(color) = 0;
            else if(std::get<0>(color) > 255) std::get<0>(color) = 255;
            if(std::get<1>(color) < 0 ) std::get<1>(color) = 0;
            else if(std::get<1>(color) > 255) std::get<1>(color) = 255;
            if(std::get<2>(color) < 0 ) std::get<2>(color) = 0;
            else if(std::get<2>(color) > 255) std::get<2>(color) = 255;
            
            image.setPixel(i,j,sf::Color(std::get<0>(color),std::get<1>(color),std::get<2>(color)));
        } 
    return true;
}
