#include<random>
#include<map>
#include<vector>
namespace mystdlib{
    std::vector<float> gaussian_distribution(float mean,float variance,long count){
        std::random_device rd{};
        std::mt19937 mt{rd()};
        std::normal_distribution<> nd{mean,variance};
        std::vector<float> nums(count,0);
        for(long long i = 0; i < count;i++)
            nums[i] = std::round(nd(mt));
        return nums;
    }
}