#ifndef FILTERS_H
    #define FILTERS_H
	#include <SFML/Graphics.hpp>
    bool boxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool maxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool minFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool meanFilter(sf::Image&, uint32_t = 3,sf::IntRect = {-1,-1,-1,-1});
    bool medianFilter(sf::Image& , unsigned int = 3, sf::IntRect = {-1,-1,-1,-1});
    bool gaussianNoiseAdder(sf::Image& ,float , float  , sf::IntRect = {-1,-1,-1,-1});
#endif