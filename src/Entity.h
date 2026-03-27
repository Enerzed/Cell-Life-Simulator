#pragma once
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp> 
#include "Gen.h"

class Entity
{
protected:
    Random random;
    sf::Color color;
	std::string name;
    int posX;
    int posY;
    int rotation;
public:
    Entity()
    {
        rotation = 0;
        name = "undefined";
        posX = 0;
        posY = 0;
        color = random.generataRandomColor();
    }

    Entity(int myPosX, int myPosY)
    {
        rotation = 0;
        name = "undefined";
        posX = myPosX;
        posY = myPosY;
        color = random.generataRandomColor();
    }

	std::string getName()
	{
		return name;
	}

	void setName(std::string myName)
	{
		name = myName;
	}

    int getPosX()
    {
        return posX;
    }

    int getPosY()
    {
        return posY;
    }

    void setPosX(int myPosX)
    {
        posX = myPosX;
    }

    void setPosY(int myPosY)
    {
        posY = myPosY;
    }

    sf::Color getColor()
    {
        return color;
    }

    void setColor(sf::Color myColor)
    {
        color = myColor;
    }

    int getRotation()
    {
        return rotation;
    }

    void setRotation(int myRotation)
    {
        rotation = myRotation;
    }

    Entity& operator=(const Entity& other)
    {
        if (this != &other)
        {
            name = other.name;
            posX = other.posX;
            posY = other.posY;
            color = other.color;
            rotation = other.rotation;
        }
        return *this;
    }

    Entity(const Entity& other)
    {
        name = other.name;
        posX = other.posX;
        posY = other.posY;
        color = other.color;
        rotation = other.rotation;
    }
};

