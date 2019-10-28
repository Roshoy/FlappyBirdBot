#include "NeuralBot.h"
#include <iostream>
#include <tuple>


int NeuralBot::MutationRate = 10;

NeuralBot::NeuralBot(const std::vector<int>& layersCount)
{
	int neuronIndex = 0;
	for(int i=0; i<layersCount.size(); i++)
	{
		const int input = i == 0 ? 1 : layersCount[i - 1] + 1;

		auto layer = std::vector<Neuron>();
		for(int j = 0; j<layersCount[i]; j++)
		{
			layer.emplace_back(Neuron(neuronIndex, input));
			neuronIndex++;
		}
		_layers.emplace_back(layer);
	}
}

NeuralBot NeuralBot::CreateNewBot(const NeuralBot& other) const
{
	auto newBot = NeuralBot();

	const auto getNeuron = [this, &other](unsigned int i, unsigned int j) {
		return (this->Points + other.Points == 0) || rand() % (this->Points + other.Points) < other.Points ? other.GetNeuron(i, j) : this->GetNeuron(i, j);
	};
	for (unsigned int i = 0; i < _layers.size(); i++)
	{
		const int input = i == 0 ? 1 : _layers[i-1].size();

		auto layer = std::vector<Neuron>();
		for (unsigned int j = 0; j < _layers[i].size(); j++)
		{
			layer.emplace_back(getNeuron(i, j));
		}
		newBot._layers.emplace_back(layer);
	}
	newBot.Mutate(MutationRate);
	return newBot;
}

void NeuralBot::RandomizeAll()
{
	for (auto & layer : _layers)
	{
		for (auto & neuron : layer)
		{
			neuron.RandomizeAll();
		}
	}
}

bool NeuralBot::Jump(double py, double ox, double oy1, double oy2) const
{
	std::vector<double> signals1, signals2;
	bool readFrom1 = false;
	signals1.push_back(py);
	signals1.push_back(ox);
	signals1.push_back(oy1);
	signals1.push_back(oy2);

	for(int recInd = 0; recInd < signals1.size(); ++recInd)
	{
		signals2.push_back(_layers[0][recInd].Calculate(std::vector<double>{signals1[recInd]}));
	}

	for(int layerInd = 1; layerInd < _layers.size(); ++layerInd)
	{
		for(auto & neuron : _layers[layerInd])
		{
			if(readFrom1)
			{
				signals2.push_back(neuron.Calculate(signals1));
			}else
			{
				signals1.push_back(neuron.Calculate(signals2));
			}
		}
		if (readFrom1)
		{
			signals1.clear();
		}
		else
		{
			signals2.clear();
		}
		readFrom1 = !readFrom1;
	}

	//std::cout << "Input: " << py << ", " << ox << ", " << oy1 << ", " << oy2 << "Jumping: " << (0 < readFrom1 ? signals1[0] : signals2[0]) << std::endl;

	return 0 < (readFrom1 ? signals1[0] : signals2[0]);
}

Neuron NeuralBot::GetNeuron(int layer, int ind) const
{
	return _layers[layer][ind];
}

void NeuralBot::Mutate(double mutationPercent)
{
	for (auto & layer : _layers)
	{
		for (auto & neuron : layer)
		{
			neuron.Mutate(mutationPercent);
		}
	}
}