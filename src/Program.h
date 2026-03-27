#pragma once

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
        font.openFromFile("fonts/consolas.ttf");
        sf::Text numberOfCells(font, "", 14);
        sf::Text cellInfo(font, "", 14);

        // In SFML 3, VideoMode takes unsigned ints, and Style is an enum class
        sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1240, 640)), "Simulator", sf::Style::Close);
        controls.init(window);

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        while (window.isOpen())
        {
            // Update delta time
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            // Process events using SFML 3's variant-based event system
            while (const std::optional<sf::Event> event = window.pollEvent())
            {
				ImGui::SFML::ProcessEvent(window, *event);
                // Handle close event
                if (event->is<sf::Event::Closed>())
                    window.close();

                // Handle mouse button press
                if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseBtn->button == sf::Mouse::Button::Left)
                    {
                        // Spawn cell at the clicked tile (tile size 16)
                        map.spawnCell(mouseBtn->position.x / 16, mouseBtn->position.y / 16);
                    }
                    else if (mouseBtn->button == sf::Mouse::Button::Right)
                    {
                        // Show info about the cell under the mouse
                        cellInfo.setString(map.getCellInfo(mouseBtn->position.x / 16, mouseBtn->position.y / 16));
                    }
                }

                // Handle mouse move
                if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>())
                {
                    x = mouseMove->position.x;
                    y = mouseMove->position.y;
                }

                // Handle key press
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->code == sf::Keyboard::Key::R)
                        window.close();
                }
            }

            // Update controls (pass window reference if needed)
            controls.process(window, clock);

            // Apply control values
            if (controls.getClearMap())
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
            numberOfCells.setPosition({660, 340});
            cellInfo.setPosition({660, 400});

            // Drawing
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