#pragma once
#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#include "Cell.h"
#include <iterator>
#include <iostream>

class Map
{
private:
	int x = MAP_WIDTH;
	int y = MAP_HEIGHT;
	float localTime = 0;
	int localFood = 0;
	int localIteration = 0;
	int maxIteration = 1;
	int requiredEnergyForDevision = 100;
	int energyPerPhotos = 1;
	int decreaseEnergy = 1;
	std::vector<Entity> map;
	std::list<Cell*> cells;
	sf::Image mapImage;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	Random random;
public:
	Map()
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if ((i == 0 || i == MAP_HEIGHT - 1) || (j == 0 || j == MAP_WIDTH - 1))
				{
					Entity wall(j, i);
					wall.setName("wall");
					map.push_back(wall);
				}
				else
				{
					Entity undefined(j, i);
					map.push_back(undefined);
				}
			}
		mapImage.loadFromFile("textures/textures.png");
		mapTexture.loadFromImage(mapImage);
		mapSprite.setTexture(mapTexture);
	}

	void generateFood(int maxFood)
	{
		int tempI = random.generate(0, MAP_HEIGHT - 1);
		int tempJ = random.generate(0, MAP_WIDTH - 1);

		for (int i = 0; i < maxFood; i++)
			if (map.at(tempI * MAP_WIDTH + tempJ).getName() == "undefined")
			{
				map.at(tempI * MAP_WIDTH + tempJ).setName("food");
				map.at(tempI * MAP_WIDTH + tempJ).setColor(sf::Color::Red);
			}
	}

	void update(int iteration)
	{
		auto i = cells.begin();
		
		for (i = cells.begin(); i != cells.end(); i++)
			(*i)->setEnergy((*i)->getEnergy() - decreaseEnergy);
		for (i = cells.begin(); i != cells.end();)
		{
			if ((*i)->getEnergy() <= 0)
			{
				map.at((*i)->getPosY() * MAP_WIDTH + (*i)->getPosX()).setName("meat");
				i = cells.erase(i);
			}
			else
				i++;
		}
		for (i = cells.begin(); i != cells.end(); i++)
		{
			int posX = (*i)->getPosX();
			int posY = (*i)->getPosY();
			int seeX = (*i)->getSeeX();
			int seeY = (*i)->getSeeY();
			std::string tempName = map.at(seeY * MAP_WIDTH + seeX).getName();
			if (tempName == "undefined")
				switch ((*i)->getGen(iteration).none)
				{
				case 0:
				{
					(*i)->facingTurnRight();
					map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
					break;
				}
				case 1:
				{
					(*i)->facingTurnLeft();
					map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
					break;
				}
				case 4:
				{
					if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
						(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
				}
				case 5:
				{
					(*i)->go();
					map.at(seeY * MAP_WIDTH + seeX).setName("cell");
					map.at(seeY * MAP_WIDTH + seeX).setColor((*i)->getColor());
					if ((*i)->getEnergy() > requiredEnergyForDevision && random.generate(0, 1) == 0)
					{
						map.at(posY * MAP_WIDTH + posX).setName("cell");
						cells.push_back(new Cell(posX, posY));
						for (int k = 0; k < 5; k++)
						{
							cells.back()->setGen((*i)->getGen(k), k);
						}
						cells.back()->getGen(iteration).mutate();
						if (!((*i)->getGen(iteration) == cells.back()->getGen(iteration)))
						{
							cells.back()->setColor(random.generataRandomColor());
							map.at(posY * MAP_WIDTH + posX).setColor(cells.back()->getColor());
						}
						else
						{
							cells.back()->setColor((*i)->getColor());
							map.at(posY * MAP_WIDTH + posX).setColor(cells.back()->getColor());
						}
						(*i)->setEnergy((*i)->getEnergy() / 2);
						cells.back()->setEnergy((*i)->getEnergy() / 2);
						map.at(posY * MAP_WIDTH + posX).setRotation(cells.back()->getFacing());
					}
					else
						map.at(posY * MAP_WIDTH + posX).setName("undefined");
					break;
				}
				}
				else if (tempName == "food")
				{
					switch ((*i)->getGen(iteration).food)
					{
					case 0:
					{
						(*i)->facingTurnRight();
						map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 1:
					{
						(*i)->facingTurnLeft();
						map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 2:
					{
						map.at(seeY * MAP_WIDTH + seeX).setName("undefined");
						(*i)->setEnergy((*i)->getEnergy() + 100);
						break;
					}
					case 4:
					{
						if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
							(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
					}
					}
				}
				else if (tempName == "meat")
				{
					switch ((*i)->getGen(iteration).meat)
					{
					case 0:
					{
						(*i)->facingTurnRight();
						map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 1:
					{
						(*i)->facingTurnLeft();
						map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 2:
					{
						map.at(seeY * MAP_WIDTH + seeX).setName("undefined");
						(*i)->setEnergy((*i)->getEnergy() + 100);
						break;
					}
					case 4:
					{
						if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
							(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
					}
					}
				}
				else if (tempName == "cell")
				{
					auto j = cells.begin();
					for (; j != cells.end(); j++)
						if ((*j)->getPosX() == seeX && (*j)->getPosY() == seeY)
							break;
					if ((*j)->getColor() == (*i)->getColor() && (*j)->getGen(iteration) == (*i)->getGen(iteration))
						switch ((*i)->getGen(iteration).sameCell)
						{
						case 0:
						{
							(*i)->facingTurnRight();
							map.at(posY * MAP_WIDTH + posX).setRotation((*i)->getFacing());
							break;
						}
						case 1:
						{
							(*i)->facingTurnLeft();
							map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
							break;
						}
						case 3:
						{
							(*j)->setEnergy((*j)->getEnergy()-100);
							break;
						}
						case 4:
						{
							if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
								(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
						}
						}
					else
						switch ((*i)->getGen(iteration).otherCell)
						{
						case 0:
						{
							(*i)->facingTurnRight();
							map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
							break;
						}
						case 1:
						{
							(*i)->facingTurnLeft();
							map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
							break;
						}
						case 3:
						{
							(*j)->setEnergy((*j)->getEnergy() - 100);
							break;
						}
						case 4:
						{
							if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
								(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
						}
						}
				}
				else if (tempName == "wall")
				{
					switch ((*i)->getGen(iteration).wall)
					{
					case 0:
					{
						(*i)->facingTurnRight();
						map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 1:
					{
						(*i)->facingTurnLeft();
						map.at(posY* MAP_WIDTH + posX).setRotation((*i)->getFacing());
						break;
					}
					case 4:
					{
						if ((*i)->getGen(iteration).sameCell != 3 && (*i)->getGen(iteration).otherCell != 3)
							(*i)->setEnergy((*i)->getEnergy() + energyPerPhotos);
					}
					}
				}
		}
	}
	void draw(sf::RenderWindow& window, float speed, sf::Clock time, int foodCounter, bool pause)
	{
		if (!pause)
		{
			localTime += time.getElapsedTime().asMicroseconds();
			if (localTime * speed > 1500)
			{
				if (localFood > 5)
				{
					generateFood(1);
					localFood = 0;
				}
				localFood += foodCounter;
				localIteration++;
				if (localIteration >= maxIteration)
					localIteration = 0;
				update(localIteration);
				localTime = 0;
			}
		}
		//Drawing sprites
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if ((map.at(i * MAP_WIDTH + j)).getName() == "undefined")
					mapSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				else if ((map.at(i * MAP_WIDTH + j)).getName() == "wall")
					mapSprite.setTextureRect(sf::IntRect(176, 0, 16, 16));
				else if ((map.at(i * MAP_WIDTH + j)).getName() == "food")
					mapSprite.setTextureRect(sf::IntRect(144, 0, 16, 16));
				else if ((map.at(i * MAP_WIDTH + j)).getName() == "meat")
					mapSprite.setTextureRect(sf::IntRect(160, 0, 16, 16));
				else if ((map.at(i * MAP_WIDTH + j)).getName() == "cell")
				{
					switch ((map.at(i * MAP_WIDTH + j)).getRotation())
					{
					case 1: {mapSprite.setTextureRect(sf::IntRect(16, 0, 16, 16)); break; }
					case 2: {mapSprite.setTextureRect(sf::IntRect(32, 0, 16, 16)); break; }
					case 3: {mapSprite.setTextureRect(sf::IntRect(48, 0, 16, 16)); break; }
					case 4: {mapSprite.setTextureRect(sf::IntRect(64, 0, 16, 16)); break; }
					case 5: {mapSprite.setTextureRect(sf::IntRect(80, 0, 16, 16)); break; }
					case 6: {mapSprite.setTextureRect(sf::IntRect(96, 0, 16, 16)); break; }
					case 7: {mapSprite.setTextureRect(sf::IntRect(112, 0, 16, 16)); break; }
					case 8: {mapSprite.setTextureRect(sf::IntRect(128, 0, 16, 16)); break; }
					}
					mapSprite.setColor((map.at(i * MAP_WIDTH + j)).getColor());
				}

				mapSprite.setPosition(j * 16, i * 16);
				window.draw(mapSprite);
				mapSprite.setColor(sf::Color::White);
			}
	}

	void spawnCell(int posX, int posY)
	{
		if (posX < MAP_WIDTH && posY < MAP_HEIGHT)
			if (map.at(posY * MAP_WIDTH + posX).getName() == "undefined")
			{
				cells.push_back(new Cell(posX, posY));
				map.at(posY * MAP_WIDTH + posX).setName("cell");
				map.at(posY * MAP_WIDTH + posX).setColor(cells.back()->getColor());
				map.at(posY * MAP_WIDTH + posX).setRotation(cells.back()->getFacing());
			}
	}
	void clearMap()
	{

		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
				if ((i == 0 || i == MAP_HEIGHT - 1) || (j == 0 || j == MAP_WIDTH - 1))
					map.at(i * MAP_WIDTH + j).setName("wall");
				else
					map.at(i * MAP_WIDTH + j).setName("undefined");
		cells.clear();
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	std::string getNumberOfCells()
	{
		return std::to_string(cells.size());
	}
	std::string getCellInfo(int posX, int posY)
	{
		std::string info = "";
		for (auto i = cells.begin(); i != cells.end(); i++)
			if ((*i)->getPosX() == posX && (*i)->getPosY() == posY)
			{
				info += "COLOR: ";
				if ((*i)->getColor() == sf::Color::Red)
					info += "Red\n";
				else if ((*i)->getColor() == sf::Color::Green)
					info  += "Green\n";
				else if ((*i)->getColor() == sf::Color::Blue)
					info += "Blue\n";
				else if ((*i)->getColor() == sf::Color::Magenta)
					info += "Magenta\n";
				else if ((*i)->getColor() == sf::Color::Cyan)
					info += "Cyan\n";
				else if ((*i)->getColor() == sf::Color::Yellow)
					info += "Yellow\n";
				else
					info += "White\n";
				info += ("NONE:       SAME CELL:  OTHER CELL: FOOD:       DEAD CELL:  WALL:\n\n");
				for (int j = 0; j < maxIteration; j++)
				{
					info += ((*i)->getGen(j).getStringReactionNone() + " ");
					info += ((*i)->getGen(j).getStringReactionSameCell() + " ");
					info += ((*i)->getGen(j).getStringReactionOtherCell() + " ");
					info += ((*i)->getGen(j).getStringReactionFood() + " ");
					info += ((*i)->getGen(j).getStringReactionMeat() + " ");
					info += ((*i)->getGen(j).getStringReactionWall() + "\n");
				}
			}
		return(info);
	}
	void setMaxIteration(int myMaxIteration)
	{
		maxIteration = myMaxIteration;
	}
	int getMaxIteration()
	{
		return maxIteration;
	}
	void setRequiredEnergyForDevision(int myRequiredEnergyForDevision)
	{
		requiredEnergyForDevision = myRequiredEnergyForDevision;
	}
	void setEnergyPerPhotos(int myEnergyPerPhotos)
	{
		energyPerPhotos = myEnergyPerPhotos;
	}
	void setDecreaseEnergy(int myDecreaseEnergy)
	{
		decreaseEnergy = myDecreaseEnergy;
	}
};

