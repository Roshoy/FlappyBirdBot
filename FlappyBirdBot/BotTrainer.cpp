#include "BotTrainer.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <numeric>

int BotTrainer::BotsNumber = 3000;
int BotTrainer::TrainingMapsCount = 20;
int BotTrainer::BestBotsCount = 20;

BotTrainer::BotTrainer(sf::RenderWindow & window) :
	_engine(window, BotsNumber)
{
	srand(time(nullptr));
	NeuralBot::MutationRate = _mutationRate;
	for (int i = 0; i < BotsNumber; i++)
	{
		_bots.emplace_back(NeuralBot(std::vector<int>{5, 6, 1}));
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
	for(int i=0; i< TrainingMapsCount; i++)
	{
		_engine.RunEngine(_bots);
	}
	
	std::sort(_bots.begin(), _bots.end(), std::greater<>());

	for(auto i = 0; i<BestBotsCount; i++)
	{
		_newBestBots.push_back(_bots[i]);
	}
	//for (auto & bot : _bots)
	//{
	//	_newBestBots.push_back(bot);
	//	std::sort(_newBestBots.begin(), _newBestBots.end(), std::greater<>());
	//	if (_newBestBots.size() > BestBotsCount)_newBestBots.pop_back();
	//}

	NeuralBot::MutationRate = _mutationRate = (((_lastResult == _newBestBots[0].Points) ? ++_generationsWithoutChange : _generationsWithoutChange) > 3 ? 50 : 15);
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
		std::cout << bot.ObstaclesPassed << "(" << bot.AllObstaclePassed/TrainingMapsCount <<") ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "Mutation rate for generation " << _generation << ": " << NeuralBot::MutationRate << std::endl;
}

void BotTrainer::NewGeneration()
{
	srand(time(nullptr));
	auto _newBots = std::vector<NeuralBot>();
	const auto sumOfBestPoints = std::accumulate(_newBestBots.begin(), _newBestBots.end(), 0, 
		[](int &a, const NeuralBot &b)->int {return a += b.AllObstaclePassed*b.AllObstaclePassed; });
	for (int i = 0; i < BotsNumber; i++)
	{
		auto newBot = _newBestBots[0].CreateNewBot(ChooseNextBotToReproduce(sumOfBestPoints));
		_newBots.push_back(newBot);
	}

	_bots.clear();
	_newBestBots.clear();
	_bots = _newBots;
}

NeuralBot BotTrainer::ChooseNextBotToReproduce(const int sumOfBestBots) const
{
	int randomIndicator = rand() % sumOfBestBots;
	for(const auto & bot : _newBestBots)
	{
		if(randomIndicator < bot.AllObstaclePassed*bot.AllObstaclePassed)
		{
			return bot;
		}
		else
		{
			randomIndicator -= bot.AllObstaclePassed*bot.AllObstaclePassed;
		}
	}
	return _newBestBots[0];
}

