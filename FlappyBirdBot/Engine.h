#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.h"
#include "Player.h"
#include "NeuralBot.h"

class Engine
{
public:
	
	Engine(sf::RenderWindow& window);
	void TrainWithGenerations();
	void TrainBots();
	void RunEngine(NeuralBot& bot);
private:
	Map _map;
	Player _player;
	int _numberOfGames;
	std::vector<sf::Rect<float>> _obstaclesToCollide;
	const sf::Vector2f StartingPosition;
	bool PlayerCollided();
	bool PlayerPassedObstacles();
	void ResetEngine();
	void Display();
	sf::RenderWindow&  _window;
	int _pointsScored;
	int _botsNumber = 2000;
	int _generation = 0;
	std::vector<NeuralBot> _bots;
	std::vector<NeuralBot> _bestBots;
	std::vector<NeuralBot> _newBestBots;
	void NewGeneration();
	int RandomBestBotIndex();
};

