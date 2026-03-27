#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

class Controls
{
private:
	bool isPause;
	int genSlider;
	int foodSlider;
	int speedSlider;
	int photosSlider;
	int requiredEnergyForDevision;
	int decreaseEnergy;
	bool clearMap;

public:
	Controls()
	{
		isPause = true;
		genSlider = 1;
		foodSlider = 1;
		speedSlider = 1;
		photosSlider = 1;
		decreaseEnergy = 1;
		requiredEnergyForDevision = 100;
		clearMap = false;
	}
	void init(sf::RenderWindow& window)
	{
		ImGui::SFML::Init(window);
	}
	void process(sf::RenderWindow& window, sf::Clock deltaClock)
	{

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Controls");
		ImGui::Checkbox("Pause Game", &isPause);
		ImGui::Spacing();
		if (ImGui::Button("Clear grid"))
			clearMap = true;
		ImGui::Spacing();
		ImGui::SliderInt("Game speed", &speedSlider, 1, 10);
		ImGui::SliderInt("Gen counter", &genSlider, 1, 5);
		ImGui::SliderInt("Food counter", &foodSlider, 1, 10);
		ImGui::SliderInt("Photosynthesis counter", &photosSlider, 1, 10);
		ImGui::SliderInt("Decrease energy counter", &decreaseEnergy, 1, 10);
		ImGui::SliderInt("Energy for devision", &requiredEnergyForDevision, 100, 500);
		ImGui::Spacing();
		ImGui::Text("1. Left click on the grid makes random Cell");
		ImGui::Text("2. Right click on the Cell gives you the information about the Cell");
		ImGui::Text("2. Mutation chance is 5 percents");
		ImGui::Text("4. Devision chance is 50 percents");
		ImGui::Spacing();
		ImGui::Text("Created by Nikita Oshurkov");
		ImGui::Text("Polzunov Altai State Technical University");
		ImGui::End();
	}
	bool getIsPause()
	{
		return isPause;
	}
	int getGenSlider()
	{
		return genSlider;
	}
	int getFoodSlider()
	{
		return foodSlider;
	}
	int getSpeedSlider()
	{
		return speedSlider;
	}
	int getPhotosSlider()
	{
		return photosSlider;
	}
	int getRequiredEnergyForDevision()
	{
		return requiredEnergyForDevision; 
	}
	int getDecreaseEnergy()
	{
		return decreaseEnergy;
	}
	bool getClearMap()
	{
		return clearMap;
	}
	void setClearMap(bool myClearMap)
	{
		clearMap = myClearMap;
	}
};

