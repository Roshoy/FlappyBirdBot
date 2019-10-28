#pragma once
#include <vector>

class Neuron
{
public:
	Neuron(int id, int weightCount);
	Neuron(const Neuron& other);
	Neuron(Neuron && other) noexcept;
	Neuron& operator=(Neuron && other) noexcept;
	Neuron& operator=(const Neuron & other);
	int GetWeightCount() const;
	bool SetWeight(double w);
	double Calculate(std::vector<double>) const;
	void RandomizeAll();
	void Mutate(double);
	double GetWeight(int w) const;
	~Neuron();
private:

	static int RandRadius;
	int _id;
	int _weightCount;
	int _weightsSet;
	double* _weights{nullptr};

};

