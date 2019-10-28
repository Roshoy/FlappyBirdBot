#pragma once
#include <vector>
#include "Neuron.h"

class NeuralBot
{
public:
	NeuralBot(const std::vector<int> & layersCount);
	NeuralBot CreateNewBot(const NeuralBot& other) const;
	void RandomizeAll();
	bool Jump(double px, double ox, double oy1, double oy2) const;
	int Points{0};
	int ObstaclesPassed{0};
	static int MutationRate;
	bool operator > (const NeuralBot& str) const
	{
		return (Points > str.Points);
	}

	Neuron GetNeuron(int layer, int ind)const;
	void Mutate(double);
private:
	NeuralBot() = default;
	std::vector<std::vector<Neuron>> _layers;

	//double Normalize(double value);
};

