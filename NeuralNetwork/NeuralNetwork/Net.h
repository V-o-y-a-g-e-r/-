#pragma once



#include "Libraries.h"
#include "Neuron.h"



class Net {

public:

	Net() = default;
	//here we compute all global operations focused on neural network
	bool feedFirstLayer(std::queue <double> &inputValues, std::vector <Neuron> &firstLayer);
	void frowardPropagation(std::vector < std::vector <Neuron> > &NeuralNetwork);
	bool calculateOutputError(std::queue <double> &targetValues, std::vector <Neuron> &lastLayer);
	void backwardPropagation(std::vector < std::vector <Neuron> > &NeuralNetwork);
	void updateWeightsOfConnections(std::vector < std::vector <Neuron> > &NeuralNetwork);

};


