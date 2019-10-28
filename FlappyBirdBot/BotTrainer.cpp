#include "BotTrainer.h"
#include <ctime>
#include <iostream>
#include <algorithm>

int BotTrainer::_botsNumber = 2000;

BotTrainer::BotTrainer(sf::RenderWindow & window) :
	_engine(window, _botsNumber)
{
	srand(time(nullptr));
	NeuralBot::MutationRate = _mutationRate;
	for (int i = 0; i < _botsNumber; i++)
	{
		_bots.emplace_back(NeuralBot(std::vector<int>{4, 8, 1}));
	}
	for (auto & bot : _bots)
	{
		bot.RandomizeAll();
	}
}

void BotTrainer::TrainWithGenerations()
{
	for (_generation = 0; true; _generation++) {
		TrainBots();
		NewGeneration();
	}
}

void BotTrainer::TrainBots()
{
	_engine.ResetSeed();
	for(int i=0; i<3; i++)
	{
		_engine.RunEngine(_bots);
	}
	for (auto & bot : _bots)
	{
		_newBestBots.push_back(bot);
		std::sort(_newBestBots.begin(), _newBestBots.end(), std::greater<>());
		if (_newBestBots.size() > 20)_newBestBots.pop_back();
	}

	NeuralBot::MutationRate = _mutationRate = (((_lastResult == _newBestBots[0].Points) ? ++_generationsWithoutChange : _generationsWithoutChange) > 3 ? 50 : 10);
	_generationsWithoutChange = (_lastResult == _newBestBots[0].Points) ? _generationsWithoutChange : 1;
	_lastResult = _newBestBots[0].Points;

	std::cout << "\nBest of Generation " << _generation << " :" << std::endl;
	for (auto & bot : _newBestBots)
	{
		//std::cout << bot.Points << " ";
	}
	//std::cout << std::endl;
	for (auto & bot : _newBestBots)
	{
		std::cout << bot.ObstaclesPassed << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "Mutation rate for generation " << _generation << ": " << NeuralBot::MutationRate << std::endl;
}

void BotTrainer::NewGeneration()
{
	srand(time(nullptr));
	auto _newBots = std::vector<NeuralBot>();
	for (int i = 0; i < _botsNumber; i++)
	{
		auto newBot = _newBestBots[rand() % _newBestBots.size()].CreateNewBot(_newBestBots[rand() % _newBestBots.size()]);
		_newBots.push_back(newBot);
	}

	_bots.clear();
	_newBestBots.clear();
	_bots = _newBots;
}


