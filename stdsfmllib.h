#ifndef STDSFMLLIB_H
    #define STDSFMLLIB_H
    #ifndef SFML_GRAPHICS_HPP
        #define SFML_GRAPHICS_HPP
        #include <SFML/Graphics.hpp>
    #endif
    bool rgbToGray(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
    bool grayToMono(sf::Image& ,unsigned int = 127, sf::IntRect = {-1,-1,-1,-1});
    bool boxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool maxFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool minFilter(sf::Image& ,unsigned int =3,sf::IntRect = {-1,-1,-1,-1});
    bool medianFilter(sf::Image& , unsigned int = 3, sf::IntRect = {-1,-1,-1,-1});
#endif