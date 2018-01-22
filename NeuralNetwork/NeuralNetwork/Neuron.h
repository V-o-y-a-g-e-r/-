#pragma once



#include "Libraries.h"


//class neuron, all info and data for given neuron
class Neuron {

	friend class Net;

public:

	Neuron(unsigned short numberOfNeuron, unsigned short numberOfConnections);
	void setOutputValue(double value);
	double returnOutputValue();

private:

	void calcOutputLayerError(double valueOfError);
	void calcHiddenLayerErrorLast(std::vector <Neuron> &nextLayer);
	void calcHiddenLayerError(std::vector <Neuron> &nextLayer);
	unsigned short n_indexOfNeuron;
	void updateWeights(std::vector <Neuron> &nextLayer);
	

	//nested class for connections for neuron, new standard of C++
	class Connections {

		friend class Neuron;

	public:

		Connections();

	private:

		static double randomizeConnections();
		double weightOfConnection;
		double deltaOfPeviousWeightForMomentum;

	};
	


	double n_error{ (double)0 };
	double n_sigmaError{ (double)0 };
	std::vector <Connections> connections;
	double n_outputValue{ (double)0 };
	void feedForwardForNeuron(std::vector <Neuron> &prevLayer);
	static double activationFunction(double value);
	static double D_activationFunction(double value);
	static double learningRate;
	static double momentum;

};
