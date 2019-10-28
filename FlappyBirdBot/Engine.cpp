#include "Engine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <functional>


Engine::Engine(sf::RenderWindow& window) :
	_map(sf::Vector2f(window.getSize()), 4), _player(window.getSize().y / 20, sf::Vector2f(window.getSize().y / 10, window.getSize().y / 2)), _numberOfGames(0),
	StartingPosition(window.getSize().y / 10, window.getSize().y / 2),	_window(window)
{

}

Engine::Engine(sf::RenderWindow& window, int playersCount) :
	Engine(window)
{
	for(int i=0; i<playersCount; i++)
	{
		_players.emplace_back(Player(window.getSize().y / 20, sf::Vector2f(window.getSize().y / 10, window.getSize().y / 2)));
	}
}

void Engine::RunEngine(std::vector<NeuralBot>& bots)
{	
	ResetEngine();
	
	while(true)
	{
		//std::cout << "Wys : " << _player.GetRect().top << " norm : " << normalize(_player.GetRect().top, 0, _window.getSize().y - _player.GetRect().height) << std::endl;

		for(int i=0; i<_players.size(); i++)
		{
			if (_players[i].Alive)
			{
				ControlPlayer(_players[i], bots[i]);
			}
		}

		if (PlayerPassedObstacles(_players[0]))
		{
			_pointsScored++;
			if (_pointsScored > 10000) {
				return;
			}
		}
		if(_alivePlayers == 0)
		{
			return;
		}
		_map.Update();

		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				/*if(event.key.code == sf::Keyboard::Space)
				{
					_player.Jump();
				}*/
				if (event.key.code == sf::Keyboard::R)
				{
					_window.setFramerateLimit(300);
					_show = true;
				}
				else if (event.key.code == sf::Keyboard::T)
				{
					_window.setFramerateLimit(0);
					_show = false;
				}
			}
		}

		if(_show)
		{
			Display();
		}		
	}

	
	//while (_window.isOpen())
	//{
	//	sf::Event event;
	//	while (_window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			_window.close();
	//		else if(event.type == sf::Event::KeyPressed)
	//		{
	//			/*if(event.key.code == sf::Keyboard::Space)
	//			{
	//				_player.Jump();
	//			}*/
	//			if(event.key.code == sf::Keyboard::R)
	//			{
	//				ResetEngine();
	//			}
	//		}			
	//	}
	//	/*if (bot.Jump(_player.GetRect().left, _obstaclesToCollide[0].left - _player.GetRect().left,
	//		_obstaclesToCollide[1].top - _obstaclesToCollide[0].top + _obstaclesToCollide[0].height))
	//		_player.Jump();*/
	//	_player.Update();
	//	_map.Update();

	//	//Display();

	//	//_obstaclesToCollide = _map.GetObstacles(_player.GetRect().left - _map.Speed);
	//	if(PlayerPassedObstacles(_player))
	//	{  			
	//		_pointsScored++;
	//	}
	//	
	//}
	
}

void Engine::ResetSeed()
{
	_seed = 100;
}

void Engine::ControlPlayer(Player& player, NeuralBot& bot)
{
	const auto normalize = [](double v, double min, double max)
	{
		return (v - min) / (max - min);
	};

	if (bot.Jump(normalize(player.GetRect().top, 0, _window.getSize().y - player.GetRect().height),
		normalize(_obstaclesToCollide[0].left, player.GetRect().left, _window.getSize().x / 4),
		normalize(_obstaclesToCollide[0].top + _obstaclesToCollide[0].height, 0, _window.getSize().y),
		normalize(_obstaclesToCollide[1].top, 0, _window.getSize().y)))
	{
		player.Jump();
	}
	player.Update();

	_distance += _map.Speed;
	_obstaclesToCollide = _map.GetObstacles(player.GetRect().left - _map.Speed);



	if (PlayerCollided(player))
	{
		bot.Points += _pointsScored * 100 + _distance / 10.0;
		bot.ObstaclesPassed = std::max(_pointsScored, bot.ObstaclesPassed);
		player.Alive = false;
		_alivePlayers--;
	}
}

bool Engine::PlayerCollided(const Player & player)
{
	const auto& playerRect = player.GetRect();
	if(playerRect.top + playerRect.height > _window.getSize().y || playerRect.top < 0)
	{
		return true;
	}

	for (const auto & obstacle : _obstaclesToCollide)
	{
		if (obstacle.intersects(playerRect))
		{
			return true;
		}
	}
	
	return false;
}

bool Engine::PlayerPassedObstacles(const Player & player)
{
 	return _obstaclesToCollide[0].left + _obstaclesToCollide[0].width <= player.GetRect().left;
}

void Engine::ResetEngine()
{
	_seed++;
	srand(_seed);
	_map.Reset();
	//_player.Reset();
	for(auto & player : _players)
	{
		player.Reset();
	}
	_obstaclesToCollide = _map.GetObstacles(_players[0].GetRect().left);
	_pointsScored = 0;
	_distance = 0;
	_alivePlayers = _players.size();
}

void Engine::Display()
{
	_window.clear();
	_window.draw(_map);
	//_window.draw(_player);
	for(const Player & player : _players)
	{
		if (player.Alive) 
		{
			_window.draw(player);
		}
	}
	_window.display();
}