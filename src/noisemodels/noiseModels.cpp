#include <vector>
#include <random>
#include "noisemodels.hpp"
std::vector<float> gaussianNoise(float mean,float stddev,uint32_t _sz){
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::normal_distribution<float> nd{mean,stddev};
    std::vector<float> nums(_sz);
    for(long long i = 0; i < _sz;i++)
        nums[i] = nd(mt);
    return nums;
}


std::vector<float> rayleighNoise(float stddev,uint32_t _sz){
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::normal_distribution<float> nd{0,stddev};
    std::vector<float> nums(_sz);
    for(uint32_t i = 0; i < _sz;i++)
        nums[i] = nd(mt);
    return nums;
}
std::vector<int> uniformNoise(uint32_t _sz){
    std::vector<int> res(_sz);
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<> ud(0,256);
    for(size_t i =0;i <_sz;i++) res.push_back(ud(mt));
    return res;
}
// std::vector<float> erlangNoise(){}
