#pragma once
#include <random>

class Random
{
public:
    std::random_device rd;
    sf::Color colors[6] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan , sf::Color::Yellow };

    Random() {

    }

    int generate(int min, int max)
    {
        std::mt19937 generate(rd());
        std::uniform_int_distribution<> distribute(min, max);
        //std::cout << " RANDOM = " << i << std::endl;
        return distribute(generate);
    }

    sf::Color generataRandomColor()
    {
        std::mt19937 generate(rd());
        std::uniform_int_distribution<> distribute(0, 5);
        return colors[distribute(generate)];
    }
};

