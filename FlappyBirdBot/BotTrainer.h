#pragma once
#include <vector>
#include "NeuralBot.h"
#include "Engine.h"

class BotTrainer
{
public:
	BotTrainer(sf::RenderWindow & window);
	void TrainWithGenerations();
	void TrainBots();
private:
	Engine _engine;
	static int BotsNumber;
	static int BestBotsCount;
	int _generation = 0;
	static int TrainingMapsCount;
	std::vector<NeuralBot> _bots;
	std::vector<NeuralBot> _bestBots;
	std::vector<NeuralBot> _newBestBots;
	void NewGeneration();
	int _mutationRate{ 15 };
	int _generationsWithoutChange{ 1 };
	int _lastResult{ 0 };
	NeuralBot ChooseNextBotToReproduce(const int sumOfBestBots) const;
};

