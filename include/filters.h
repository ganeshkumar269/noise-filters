#ifndef SFML_GRAPHICS_HPP
        #define SFML_GRAPHICS_HPP
        #include <SFML/Graphics.hpp>
#endif
    bool boxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool maxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool minFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool meanFilter(sf::Image&, uint32_t = 3,sf::IntRect = {-1,-1,-1,-1});
    bool medianFilter(sf::Image& , unsigned int = 3, sf::IntRect = {-1,-1,-1,-1});
    bool gaussianNoiseAdder(sf::Image& ,float , float  , sf::IntRect = {-1,-1,-1,-1});