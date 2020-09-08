#include "noisefilters.hpp"
#include <iostream>
void apply_filter(sf::Image& image,void (*reducer)(float&,uint32_t,uint32_t),unsigned int boxSize,sf::IntRect dimension){
    if(dimension.height == -1 or dimension.width == -1){
        dimension.height = image.getSize().y;
        dimension.width = image.getSize().x;
        dimension.left = dimension.top = 0;
    }

    if(!(boxSize&1)){
        std::cerr << "Box Size must be odd" << std::endl;
        return;
    }
    sf::Image tmp = image;
    unsigned int height = dimension.height + dimension.top , width = dimension.width + dimension.left;
    for(unsigned int y = dimension.top + int(boxSize/2) ;y < height - int(boxSize/2); y++)
    for(unsigned int x = dimension.left + int(boxSize/2) ; x < width - int(boxSize/2) ; x++){
        float r=0,g=0,b=0,a=tmp.getPixel(x,y).a;
        for(uint m= x - boxSize/2; m < x + boxSize/2;m++){
            for(uint n= y-boxSize/2; n < y+boxSize/2;n++){
                reducer(r,tmp.getPixel(m,n).r,boxSize);
                reducer(g,tmp.getPixel(m,n).g,boxSize);
                reducer(b,tmp.getPixel(m,n).b,boxSize);
                // reducer(a,tmp.getPixel(m,n).a,boxSize);
            }     
        }
        image.setPixel(x,y,sf::Color(r,g,b,a));
    }   
}


// void apply_filter(sf::Image& image,unsigned int boxSize,sf::IntRect dimension,sf::Color (*filter)(sf::Image,uint32_t,uint32_t,uint32_t)){
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
//     // Eigen::MatrixXd imageMatrix = Eigen::MatrixXd::Zero(width + boxSize - 1, height + boxSize - 1);
//     // for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
//     // for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++)
//     //     imageMatrix(j,i) = image.getPixel(j - int(boxSize/2),i - int(boxSize/2)).r;
//     for(unsigned int i = dimension.top + int(boxSize/2) ;i < height + int(boxSize/2); i++)
//     for(unsigned int j = dimension.left + int(boxSize/2) ; j < width + int(boxSize/2) ; j++){
//         image.setPixel(i,j,filter(image,boxSize,i,j));


//     // unsigned int t = imageMatrix.block(j - int(boxSize/2), i - int(boxSize/2),boxSize,boxSize)
//     //                                     .sum()/float(boxSize*boxSize);
//     //     image.setPixel(j - int(boxSize/2),i - int(boxSize/2) , 
//     //                     sf::Color(t,t,t,255));
//     }   
// }