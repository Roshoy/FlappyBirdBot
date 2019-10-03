#pragma once

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
	double Calculate(double input[]);
	void RandomizeAll();
	void RandomizeALittle();
	double GetWeight(int w) const;
	~Neuron();
private:

	static int RandRadius;
	int _id;
	int _weightCount;
	int _weightsSet;
	double* _weights{nullptr};

};

