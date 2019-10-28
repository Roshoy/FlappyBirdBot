#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Engine.h"
#include "BotTrainer.h"

int main()
{
	srand(time(nullptr));
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	//window.setFramerateLimit(240);
	BotTrainer trainer(window);
	trainer.TrainWithGenerations();
	system("PAUSE");
	return 0;
}
