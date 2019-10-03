#include "Engine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <functional>


Engine::Engine(sf::RenderWindow& window) :
	_window(window), StartingPosition(window.getSize().y / 10, window.getSize().y / 2), _numberOfGames(0),
	_map(sf::Vector2f(window.getSize()), 4),	_player(window.getSize().y / 20, sf::Vector2f(window.getSize().y / 10, window.getSize().y / 2))
{
	srand(time(nullptr));
	for(int i = 0; i < _botsNumber; i++)
	{
		_bots.emplace_back(NeuralBot());
	}
	for(auto & bot : _bots)
	{
		bot.RandomizeAll();
	}
}

void Engine::TrainWithGenerations()
{
	for (_generation = 0; true; _generation++) {
		TrainBots();
		NewGeneration();
	}
}

void Engine::TrainBots()
{
	for(auto & bot : _bots)
	{
		RunEngine(bot);
		_bestBots.push_back(bot);
		std::sort(_bestBots.begin(), _bestBots.end(), std::greater<NeuralBot>());
		if(_bestBots.size() > 7)_bestBots.pop_back();
		_newBestBots.push_back(bot);
		std::sort(_newBestBots.begin(), _newBestBots.end(), std::greater<NeuralBot>());
		if (_newBestBots.size() > 7)_newBestBots.pop_back();
		//if(bot.Points > 0 )std::cout << "Points: " << bot.Points << std::endl;
	}
	std::cout << "Best of All:  " << std::endl;
	for (auto & bot : _bestBots)
	{
		std::cout << bot.Points << " ";
	}
	std::cout << "\nBest of Generation " << _generation << " :" << std::endl;
	for (auto & bot : _newBestBots)
	{
		std::cout << bot.Points << " ";
	}
	std::cout << std::endl<<std::endl;
}

void Engine::RunEngine(NeuralBot& bot)
{	
	ResetEngine();
	auto normalize = [](double v, double min, double max)
	{
		return (v - min) / (max - min);
	};
	while(true)
	{
		if (bot.Jump(normalize(_player.GetRect().top, 0, _window.getSize().y - _player.GetRect().height), 
			normalize(_obstaclesToCollide[0].left, _player.GetRect().left, _window.getSize().x/4),
			normalize(_obstaclesToCollide[0].top + _obstaclesToCollide[0].height, 0, _window.getSize().y),
			normalize(_obstaclesToCollide[1].top, 0, _window.getSize().y)))
			_player.Jump();
		_player.Update();
		_map.Update();

		//Display();

		_obstaclesToCollide = _map.GetObstacles(_player.GetRect().left - _map.Speed);
		if (PlayerPassedObstacles())
		{
			_pointsScored++;
			if (_pointsScored > 10000)return;
		}


		if (PlayerCollided())
		{
			bot.Points = _pointsScored * _pointsScored;
			return;
		}
	}


	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			else if(event.type == sf::Event::KeyPressed)
			{
				/*if(event.key.code == sf::Keyboard::Space)
				{
					_player.Jump();
				}*/
				if(event.key.code == sf::Keyboard::R)
				{
					ResetEngine();
				}
			}			
		}
		/*if (bot.Jump(_player.GetRect().left, _obstaclesToCollide[0].left - _player.GetRect().left,
			_obstaclesToCollide[1].top - _obstaclesToCollide[0].top + _obstaclesToCollide[0].height))
			_player.Jump();*/
		_player.Update();
		_map.Update();

		//Display();

		//_obstaclesToCollide = _map.GetObstacles(_player.GetRect().left - _map.Speed);
		if(PlayerPassedObstacles())
		{  			
			_pointsScored++;
		}

		
		if(PlayerCollided())
		{
			bot.Points = _pointsScored * _pointsScored;
			return;
			//ResetEngine();
		}

		
	}
}

bool Engine::PlayerCollided()
{
	const auto playerRect = _player.GetRect();
	if(playerRect.top + playerRect.height > _window.getSize().y)
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

bool Engine::PlayerPassedObstacles()
{
 	return _obstaclesToCollide[0].left + _obstaclesToCollide[0].width <= _player.GetRect().left;
}

void Engine::ResetEngine()
{
	int seed = 100;
	srand(seed);
	_map.Reset();
	_player.Reset();
	_obstaclesToCollide = _map.GetObstacles(_player.GetRect().left);
	_pointsScored = 0;
}

void Engine::Display()
{
	_window.clear();
	_window.draw(_map);
	_window.draw(_player);
	_window.display();
}

void Engine::NewGeneration()
{
	srand(time(nullptr));
	_bots.clear();
	for (int i = 0; i < _botsNumber; i++)
	{
		auto newBot = NeuralBot();
		double w[21]
		{
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(0,0),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(0,1),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(1,0),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(1,1),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(2,0),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(2,1),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(3,0),
			_newBestBots[rand() % _newBestBots.size()].GetReceptorWeight(2,1),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(0,0),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(0,1),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(0,2),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(0,3),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(0,4),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(1,0),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(1,1),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(1,2),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(1,3),
			_newBestBots[rand() % _newBestBots.size()].GetComputingWeight(1,4),
			_newBestBots[rand() % _newBestBots.size()].GetOutputWeight(0),
			_newBestBots[rand() % _newBestBots.size()].GetOutputWeight(1),
			_newBestBots[rand() % _newBestBots.size()].GetOutputWeight(2),
		};

		newBot.SetWeights(w);
		_bots.push_back(newBot);
	}
	_newBestBots.clear();
}

int Engine::RandomBestBotIndex()
{
	int sum = 0;
	for(const auto & bot:_bestBots)
	{
		sum += bot.Points;
	}
	int r = rand() % sum;
	for(int i=0; i<_bestBots.size(); i++)
	{
		if (_bestBots[i].Points < r)return i;
		r -= _bestBots[i].Points;
	}
	return 0;
}
