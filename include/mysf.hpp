#ifndef MYSF_HPP
    #define MYSF_HPP
    #include <SFML/Graphics.hpp>
    namespace mysf {
        void rgbToGray(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        void rgbToGray_MT(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        void grayToMono(sf::Image& ,unsigned int = 127, sf::IntRect = {-1,-1,-1,-1});
        void grayToMono_MT(sf::Image& ,unsigned int = 127, sf::IntRect = {-1,-1,-1,-1});
        double mean(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        double mean_MT(sf::Image& , sf::IntRect = {-1,-1,-1,-1});
        double variance(sf::Image& ,sf::IntRect = {-1,-1,-1,-1},double = -1);
        double variance_MT(sf::Image& ,sf::IntRect = {-1,-1,-1,-1});
    }
#endif