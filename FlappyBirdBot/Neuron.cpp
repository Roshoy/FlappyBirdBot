#include "Neuron.h"
#include <cstdlib>
#include <utility>

int Neuron::RandRadius = 1000;

Neuron::Neuron(int id, int weightCount):
	_id(id), _weightCount(weightCount), _weightsSet(0)
{
	_weights = new double[_weightCount];
}

Neuron::Neuron(const Neuron& other):
	_id(other._id), _weightCount(other._weightCount), _weightsSet(other._weightsSet)
{
	_weights = new double[_weightCount];
	std::memcpy(_weights, other._weights, sizeof(double)*_weightCount);
}

Neuron::Neuron(Neuron&& other) noexcept:
	_id(other._id), _weightCount(other._weightCount), _weightsSet(other._weightsSet)
{
	delete[] _weights;
	_weights = other._weights;
	other._weights = nullptr;
}

Neuron& Neuron::operator=(Neuron&& other) noexcept
{
	if (this != &other) {
		_id = other._id;
		_weightsSet = other._weightsSet;
		_weightCount = other._weightCount;
		delete[] _weights;
		_weights = other._weights;
		other._weights = nullptr;
	}
	return *this;
}

Neuron& Neuron::operator=(const Neuron & other)
{
	_id = other._id;
	_weightsSet = other._weightsSet;
	_weightCount = other._weightCount;
	delete[] _weights;
	_weights = new double[_weightCount];
	std::memcpy(_weights, other._weights, sizeof(double)*_weightCount);
	return *this;
}

int Neuron::GetWeightCount() const
{
	return _weightCount;
}

bool Neuron::SetWeight(double w)
{
	if(_weightsSet < _weightCount)
	{
		_weights[_weightsSet++] = w;
		return true;
	}
	return false;
}

double Neuron::Calculate(double input[])
{
	double result = _weights[_weightCount-1];
	for(int i=0; i<_weightCount-1 ; i++)
	{
		result += input[i] * _weights[i];
	}
	delete[] input;
	return result;
}

void Neuron::RandomizeAll()
{
	for (int i = 0; i < _weightCount; i++)
	{
		_weights[i] = 2 * float((rand() % RandRadius)) / RandRadius - 1;
	}
}

void Neuron::RandomizeALittle()
{
	_weights[rand() % _weightCount] = 2 * float((rand() % RandRadius))/RandRadius - 1;
	
}

double Neuron::GetWeight(int w) const
{
	return _weights[w];
}


Neuron::~Neuron()
{
	delete[] _weights;
}