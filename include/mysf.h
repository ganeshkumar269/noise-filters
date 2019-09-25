#ifndef MYSF_H
    #define MYSF_H
    #ifndef SFML_GRAPHICS_HPP
        #define SFML_GRAPHICS_HPP
        #include <SFML/Graphics.hpp>
    #endif
    namespace mysf {
        bool rgbToGray(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        bool grayToMono(sf::Image& ,unsigned int = 127, sf::IntRect = {-1,-1,-1,-1});
        double mean(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        double variance(sf::Image& ,sf::IntRect = {-1,-1,-1,-1});
    }
#endif