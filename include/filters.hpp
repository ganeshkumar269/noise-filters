#ifndef FILTERS_HPP
    #define FILTERS_HPP
	#include <SFML/Graphics.hpp>
    #define uint uint32_t
    void boxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    void maxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    void minFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    void meanFilter(sf::Image&, uint32_t = 3,sf::IntRect = {-1,-1,-1,-1});
    void medianFilter(sf::Image& , unsigned int = 3, sf::IntRect = {-1,-1,-1,-1});
    void gaussianNoiseAdder(sf::Image& ,float , float  , sf::IntRect = {-1,-1,-1,-1});
#endif