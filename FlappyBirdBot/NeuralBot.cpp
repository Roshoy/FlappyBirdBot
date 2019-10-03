#include "NeuralBot.h"
#include <iostream>


NeuralBot::NeuralBot():
	_output(5, 3)
{
	_receptors.emplace_back(0, 2);
	_receptors.emplace_back(1, 2);
	_receptors.emplace_back(2, 2);
	_receptors.emplace_back(3, 2);

	_computingNeurons.emplace_back(4, 5);
	_computingNeurons.emplace_back(5, 5);	
}

void NeuralBot::RandomizeAll()
{
	for (auto& n : _receptors)
	{
		n.RandomizeAll();
	}
	for (auto& n : _computingNeurons)
	{
		n.RandomizeAll();
	}
	_output.RandomizeAll();
}

void NeuralBot::SetWeights(double weights[])
{
	_receptors[0].SetWeight(weights[0]);
	_receptors[0].SetWeight(weights[1]);
	_receptors[1].SetWeight(weights[2]);
	_receptors[1].SetWeight(weights[3]);
	_receptors[2].SetWeight(weights[4]);
	_receptors[2].SetWeight(weights[5]);
	_receptors[3].SetWeight(weights[6]);
	_receptors[3].SetWeight(weights[7]);
	_computingNeurons[0].SetWeight(weights[8]);
	_computingNeurons[0].SetWeight(weights[9]);
	_computingNeurons[0].SetWeight(weights[10]);
	_computingNeurons[0].SetWeight(weights[11]);
	_computingNeurons[0].SetWeight(weights[12]);
	_computingNeurons[1].SetWeight(weights[13]);
	_computingNeurons[1].SetWeight(weights[14]);
	_computingNeurons[1].SetWeight(weights[15]);
	_computingNeurons[1].SetWeight(weights[16]);
	_computingNeurons[1].SetWeight(weights[17]);
	_output.SetWeight(weights[18]);
	_output.SetWeight(weights[19]);
	_output.SetWeight(weights[20]);

	for (auto& n : _receptors)
	{
		n.RandomizeALittle();
	}
	for (auto& n : _computingNeurons)
	{
		n.RandomizeALittle();
	}
	_output.RandomizeALittle();
}

bool NeuralBot::Jump(double px, double ox, double oy1, double oy2)
{
	double a = _receptors[0].Calculate(new double[1] { px });
	double b = _receptors[1].Calculate(new double[1] { ox });
	double c = _receptors[2].Calculate(new double[1] { oy1 });
	double d = _receptors[3].Calculate(new double[1] { oy2 });
	double e = _computingNeurons[0].Calculate(new double[4] { a, b, c, d});
	double f = _computingNeurons[1].Calculate(new double[4] { a, b, c, d});
	double g = _output.Calculate(new double[2]{ e, f });
	//std::cout << a << " " <<  b << " " << c << " " << d << " " << e << " " << f << std::endl;
	return 0 < g;
}


NeuralBot::~NeuralBot()
{
}

double NeuralBot::GetReceptorWeight(int i, int w) const
{
	return _receptors[i].GetWeight(w);
}

double NeuralBot::GetComputingWeight(int i, int w) const
{
	return _computingNeurons[i].GetWeight(w);
}

double NeuralBot::GetOutputWeight(int w) const
{
	return _output.GetWeight(w);
}

void NeuralBot::RandomizeALittle()
{
	int r = rand() % 6;
	if(r<3)
	{
		_receptors[r].RandomizeALittle();
	}
	else if(r<5)
	{
		_computingNeurons[r - 3].RandomizeALittle();
	}else
	{
		_output.RandomizeALittle();
	}
}

double NeuralBot::Normalize(double value)
{
	return 1 / (1 + exp(-value));
}
