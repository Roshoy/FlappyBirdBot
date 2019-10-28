#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.h"
#include "Player.h"
#include "NeuralBot.h"

class Engine
{
public:
	Engine(sf::RenderWindow& window);
	Engine(sf::RenderWindow& window, int playersCount);
	void RunEngine(std::vector<NeuralBot>& bots);
	void ResetSeed();
private:
	void ControlPlayer(Player & player, NeuralBot & bot);
	Map _map;
	std::vector<Player> _players;
	Player _player;
	int _numberOfGames;
	std::vector<sf::Rect<float>> _obstaclesToCollide;
	const sf::Vector2f StartingPosition;
	bool PlayerCollided(const Player & player);
	bool PlayerPassedObstacles(const Player & player);
	void ResetEngine();
	void Display();
	sf::RenderWindow&  _window;
	int _pointsScored;
	bool _show{ true };
	double _distance;
	int _alivePlayers;
	int _seed{ 100 };

};

