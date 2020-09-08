#include <iostream>
#include "noisemodels.hpp"
#include <random>




void nextErlang(float k,float lambda){
    std::mt19937 mt;
    std::uniform_real_distribution<float> ud(0,1);
    float prod=1;
    for(int i =0;i<k;i++) prod *= ud(mt);
    return -std::log(prod)/lambda;
}
//To Remember mean = k/lambda
//            variance = k/(lambda^2)

void print(){
    float mean = 128;
    float variance = 40;
    float k = 
}