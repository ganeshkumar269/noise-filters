#ifndef NOISEFILTERS_HPP
    #define NOISEFILTERS_HPP
	#include <SFML/Graphics.hpp>
    #define uint uint32_t
    // void boxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    // sf::Color boxFilter(sf::Image& ,uint32_t,uint32_t,uint32_t);
    void boxFilterReducer(float&,uint32_t,uint32_t);
    void maxFilterReducer(float&,uint32_t,uint32_t);
    void minFilterReducer(float&,uint32_t,uint32_t);
    void apply_filter(sf::Image&,void (*)(float&,uint32_t,uint32_t),uint = 3,sf::IntRect={-1,-1,-1,-1});

    void maxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    void minFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    void medianFilter(sf::Image& , unsigned int = 3, sf::IntRect = {-1,-1,-1,-1});
    void gaussianNoiseAdder(sf::Image& ,float , float  , sf::IntRect = {-1,-1,-1,-1});
#endif