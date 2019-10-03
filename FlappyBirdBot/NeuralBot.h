#pragma once
#include <vector>
#include "Neuron.h"

class NeuralBot
{
public:
	NeuralBot();
	void RandomizeAll();
	void SetWeights(double weights[]);
	bool Jump(double px, double ox, double oy1, double oy2);
	int Points;
	~NeuralBot();
	bool operator > (const NeuralBot& str) const
	{
		return (Points > str.Points);
	}
	double GetReceptorWeight(int i, int w) const;
	double GetComputingWeight(int i, int w) const;
	double GetOutputWeight(int w) const;
	void RandomizeALittle();
private:
	double Normalize(double value);
	std::vector<Neuron> _receptors;
	std::vector<Neuron> _computingNeurons;
	Neuron _output;
};

