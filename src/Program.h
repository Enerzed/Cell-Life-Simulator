#include <iostream>
#include <random>
#include "Controls.h"
#include "Map.h"

class Program
{
private:
	static Program* p_instance;
	sf::Clock clock;
	sf::Font font;
	int speed;
	int x;
	int y;
	bool clickedCell;
	Controls controls;
	Map map;
	Program()
	{
		clickedCell = false;
		speed = 1;
	}
public:
	static Program* getInstance()
	{
		if (!p_instance)
			p_instance = new Program();
		return p_instance;
	}
	void run()
	{
		font.loadFromFile("Consolas.ttf");
		sf::Text numberOfCells("", font, 14);
		sf::Text cellInfo("", font, 14);
		sf::Vector2i position = sf::Mouse::getPosition();
		sf::RenderWindow window(sf::VideoMode(1240, 640), "Simulator", sf::Style::Close);
		controls.init(window);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;
			sf::Event event;
			while (window.pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					map.spawnCell(int(x / 16), int(y / 16));
				}
				if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					cellInfo.setString(map.getCellInfo(x / 16, y / 16));
				}
				if (event.type == sf::Event::MouseMoved)
				{
					x = event.mouseMove.x;
					y = event.mouseMove.y;
				}
				if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					window.close();
				}
			}

			controls.process(window, clock);
			if (controls.getClearMap() == true)
			{
				map.clearMap();
				controls.setClearMap(false);
			}
			if (controls.getGenSlider() != map.getMaxIteration())
				map.setMaxIteration(controls.getGenSlider());
			map.setRequiredEnergyForDevision(controls.getRequiredEnergyForDevision());
			map.setEnergyPerPhotos(controls.getPhotosSlider());
			map.setDecreaseEnergy(controls.getDecreaseEnergy());
			numberOfCells.setString("Number of Cells: " + map.getNumberOfCells());
			numberOfCells.setPosition(660, 340);
			cellInfo.setPosition(660, 400);

			window.clear(sf::Color(0, 0, 0));
			window.draw(numberOfCells);
			window.draw(cellInfo);
			map.draw(window, controls.getSpeedSlider(), clock, controls.getFoodSlider(), controls.getIsPause());
			ImGui::SFML::Render(window);
			window.display();
		}
		ImGui::SFML::Shutdown();
	}
};