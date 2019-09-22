#include <SFML/Graphics.hpp>
#ifndef _GLIBCXX_IOSTREAM
    #include<iostream>
#endif
#include "stdsfmllib.h"
#include <Eigen/Dense>
#include <algorithm>
#include "dependencies/gaussian_distribution.cpp"
bool rgbToGray(sf::Image& image, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }
    for(unsigned int i = dimension.top ;i <  dimension.top + dimension.height; i++)
        for(unsigned int j = dimension.left ; j <  dimension.left + dimension.width ; j++){
            if(j >= image.getSize().x or i >= image.getSize().y)
                std::cout<<"Error: Exceeds Image bounds"<<std::endl;
            else{
                if(j > 650 and i > 650) std::cout<<j<<" "<<i<<std::endl;
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
    Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize).minCoeff();
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(t,t,t,255));
    }
    for(unsigned int i = int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(imageMatrix(j,i),imageMatrix(j,i),imageMatrix(j,i),255));
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

bool gaussianNoiseAdder(sf::Image& image,sf::IntRect dimension){
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
            image_matrix(j,i) = image.getPixel(j,i).r; 
    float mean = image_matrix.mean();
    std::cout<<"Mean "<<mean<<std::endl;
    Eigen::MatrixXd mean_matrix  = Eigen::MatrixXd::Constant(dimension.height,dimension.width,mean); 
    std::cout<<"Mean matrrix created "<< std::endl;
    Eigen::MatrixXd diff_matrix = image_matrix - mean_matrix;
    std::cout<< "Diff Matrix Created " << std::endl;
    float variance = (diff_matrix.transpose()*diff_matrix).diagonal().sum() / (dimension.height*dimension.width);
    std::cout<< "Variance: " << variance << std::endl;
    Eigen::MatrixXf gaussian_noise = Eigen::Map<Eigen::Matrix<float,6000,6000>>(
                mystdlib::gaussian_distribution(mean,variance,dimension.height*dimension.width).data());
    gaussian_noise.resize(dimension.height,dimension.width);
    std::cout<<"Noise Mean: "<<gaussian_noise.mean()<<std::endl;
    for(unsigned int i = dimension.left ; i < width; i++)
        for(unsigned int j = dimension.top ; j < height ; j++)
            image.setPixel(j,i,sf::Color(image.getPixel(j,i).r + (int)gaussian_noise(j,i),
                            image.getPixel(j,i).r + (int)gaussian_noise(j,i),image.getPixel(j,i).r + (int)gaussian_noise(j,i))); 
    return true;
}

