#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Engine.h"

int main()
{
	srand(time(nullptr));
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	//window.setFramerateLimit(80);
	Engine engine(window);
	engine.TrainWithGenerations();
	system("PAUSE");
	return 0;
}
