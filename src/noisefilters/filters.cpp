#include "SFML/Graphics.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <algorithm>
#include "gaussian_distribution.cpp"
#include "noisefilters.hpp"
#include <vector>


void boxFilterReducer(float& x,uint y,uint boxSize){
    x += y/(float)(boxSize*boxSize);
}
void maxFilterReducer(float& x,uint y,uint boxSize){
    x = std::max(x,y/(float)(boxSize*boxSize));
}
void minFilterReducer(float& x,uint y,uint boxSize){
    if(x == 0) x = 1<<8;
    x = std::min(x,y/(float)(boxSize*boxSize));
}

sf::Color boxFilter(sf::Image& image,uint32_t boxSize,uint32_t x,uint32_t y){
    float r=0,g=0,b=0,a=0;
    for(uint m= x - boxSize/2; m < x + boxSize/2;m++){
        for(uint n= y-boxSize/2; n < y+boxSize/2;n++){
            r += image.getPixel(m,n).r/(float)(boxSize*boxSize);
            g += image.getPixel(m,n).g/(float)(boxSize*boxSize);
            b += image.getPixel(m,n).b/(float)(boxSize*boxSize);
            a += image.getPixel(m,n).a/(float)(boxSize*boxSize);
        }        
    }
    if(r > 256 || g > 256 || b > 256 || a > 256)
        std::cout << "filters.cpp:Exceeds limits" << std::endl;
    return sf::Color(r,g,b,a);
}

// void boxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
//     if(dimension.height == -1 or dimension.width == -1){
//         dimension.height = image.getSize().y;
//         dimension.width = image.getSize().x;
//         dimension.left = dimension.top = 0;
//     }

//     if(!(boxSize&1)){
//         std::cerr << "Box Size must be odd" << std::endl;
//         // return false;
//     }
//     unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
//     Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
//     for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
//     for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
//         imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
//     for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
//     for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){ 
//     unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize)
//                                         .sum()/float(boxSize*boxSize);
//         image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
//                         sf::Color(t,t,t,255));
//     }   
// }


void maxFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
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
}


void minFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        std::cerr << "Box Size must be odd" << std::endl;
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
}


void meanFilter(sf::Image& image,uint32_t boxSize, sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.width = image.getSize().x;
        dimension.height = image.getSize().y;
        dimension.top = dimension.left = 0;
    }
    int halfSize = boxSize/2;
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    // Eigen::MatrixXd image_matrix = Eigen::MatrixXd::Zero(dimension.height + boxSize + 1,dimension.width + boxSize + 1);
    // for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    // for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
    //     image_matrix(i,j) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r; 
    // for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    // for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
    //     long mean = image_matrix.block(i - int(boxSize/2), j - int(boxSize/2),boxSize,boxSize).mean();
    //     image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
    //                     sf::Color(mean,mean,mean,255));
    // }

    for(uint i =dimension.top+halfSize; i < height-halfSize;i++)
    for(uint j =dimension.left+halfSize; i < width-halfSize;j++){
        float sumOfWindow[3] = {0.0}; //array of 3, since 3 channels
        for(uint m = i-halfSize; m <= i+halfSize;m++)
        for(uint n = j-halfSize; n <= j+halfSize;n++){
            sumOfWindow[0] += image.getPixel(m,n).r;
            sumOfWindow[1] += image.getPixel(m,n).g;
            sumOfWindow[2] += image.getPixel(m,n).b;
        }
        for(float& i : sumOfWindow) i/=boxSize;
        image.setPixel(i,j,
                sf::Color(sumOfWindow[0],sumOfWindow[1],sumOfWindow[2],image.getPixel(i,j).a)
                );
    }
}



void medianFilter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        std::cerr << "Box Size must be odd" << std::endl;
    }
    int halfSize = boxSize/2;
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    // Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
    // for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    // for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
    //     imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;    
    std::vector<std::vector<uint>> curr_window(boxSize*boxSize,std::vector<uint>(4));
    for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
    for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
        // Eigen::MatrixXd temp =imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize).transpose();
        uint ind = 0;
        for(uint m = i-halfSize; m <= i+halfSize;m++)
        for(uint n = j-halfSize; n <= j+halfSize;n++){
            curr_window[ind][0] = image.getPixel(m,n).r;
            curr_window[ind][1] = image.getPixel(m,n).g;
            curr_window[ind][2] = image.getPixel(m,n).b;
            curr_window[ind][3] = image.getPixel(m,n).a;
            ind++;
            // curr_window.push_back({image.getPixel(m,n).r,image.getPixel(m,n).g,image.getPixel(m,n).b,image.getPixel(m,n).a});
            // curr_window[0] += image.getPixel(m,n).r
            // curr_window[1] += image.getPixel(m,n).g
            // curr_window[2] += image.getPixel(m,n).b
        }
        uint newPixel[4] = {0};
        for(uint itr =0 ; itr < 4; itr++){
            std::sort(curr_window.begin(),curr_window.end(),[itr](std::vector<uint> x,std::vector<uint> y){return x[itr] < y[itr];});
            newPixel[itr] = curr_window[boxSize*boxSize/2][itr];    
        }
        image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
                        sf::Color(newPixel[0],newPixel[1],newPixel[2],newPixel[4]));
    }
}

void gaussianNoiseAdder(sf::Image& image,float mean,float variance,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }
    // std::cout<< dimension.top << " " << dimension.height << " " << dimension.left << " " << dimension.width <<std::endl;
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
            if(std::get<0>(color) > 255) std::get<0>(color) = 255;
            if(std::get<1>(color) < 0 ) std::get<1>(color) = 0;
            if(std::get<1>(color) > 255) std::get<1>(color) = 255;
            if(std::get<2>(color) < 0 ) std::get<2>(color) = 0;
            if(std::get<2>(color) > 255) std::get<2>(color) = 255;
            
            image.setPixel(i,j,sf::Color(std::get<0>(color),std::get<1>(color),std::get<2>(color)));
        } 
}
