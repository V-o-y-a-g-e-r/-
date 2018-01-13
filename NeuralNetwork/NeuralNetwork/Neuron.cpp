#include "Neuron.h"



extern std::queue <double> n_EpochError;




double Neuron::momentum = (double)0.1623423;



double Neuron::learningRate = (double)0.243342;



double Neuron::D_activationFunction(double value) {
	return (double)((double)1 - (double)(tanh(value) * tanh(value)));
}



void Neuron::calcOutputLayerError(double valueOfError) {

	this->n_error = this->returnOutputValue() - valueOfError;

	n_EpochError.push(this->n_error);

	this->n_sigmaError = Neuron::D_activationFunction(this->returnOutputValue()) *
		this->n_error;

	std::cout << "Error of output Neurons in the output layer: " << this->n_error << std::endl;

}



double Neuron::activationFunction(double value) {

	return (double)tanh(value);

}



void Neuron::updateWeights(std::vector <Neuron> &previousLayer) {

	std::vector <Neuron>::iterator i_e;

	for (i_e = previousLayer.begin(); i_e != previousLayer.end(); ++i_e) {

		double deltaWeight = (double)0;

		deltaWeight = -(Neuron::learningRate * this->n_sigmaError *
			i_e->returnOutputValue()) + (Neuron::momentum *
				i_e->connections[this->n_indexOfNeuron].deltaOfPeviousWeightForMomentum);

		i_e->connections[this->n_indexOfNeuron].deltaOfPeviousWeightForMomentum = deltaWeight;

		i_e->connections[this->n_indexOfNeuron].weightOfConnection +=
			deltaWeight;

	}
}



void Neuron::feedForwardForNeuron(std::vector <Neuron> &prevLayer) {

	double productOfWeightsAndOutputs = (double)0;

	for (unsigned short i = 0; i < prevLayer.size(); ++i) {

		productOfWeightsAndOutputs += (prevLayer[i].returnOutputValue() *
			prevLayer[i].connections[this->n_indexOfNeuron].weightOfConnection);
	}

	productOfWeightsAndOutputs = Neuron::activationFunction(productOfWeightsAndOutputs);

	this->n_outputValue = productOfWeightsAndOutputs;

}



double Neuron::returnOutputValue() {

	return this->n_outputValue;

}



void Neuron::setOutputValue(double value) {

	this->n_outputValue = value;

}



double Neuron::Connections::randomizeConnections() {

	double val = ((double)(rand()) / (double)(RAND_MAX));

	return val;

}



Neuron::Connections::Connections() {

	this->weightOfConnection = Connections::randomizeConnections();
	this->deltaOfPeviousWeightForMomentum = (double)0;

}



Neuron::Neuron(unsigned short numberOfNeuron, unsigned short numberOfConnections) {

	this->n_indexOfNeuron = numberOfNeuron;

	for (unsigned short i = 0; i < numberOfConnections; ++i) {

		this->connections.push_back(Connections());

	}

}



void Neuron::calcHiddenLayerError(std::vector <Neuron> &nextLayer) {

	double outputDeriv = Neuron::D_activationFunction(this->returnOutputValue());

	double sumOfErrorInNextLayer = (double)0;

	std::vector <Neuron>::iterator n_itr;

	for (n_itr = nextLayer.begin(); n_itr != (--nextLayer.end()); ++n_itr) {

		//--nextlayer becouse neuron in previous layer has no connection with the bias in the next layer

		double errorOfNeuron = double(0);
		errorOfNeuron = n_itr->n_sigmaError * this->connections[n_itr->n_indexOfNeuron].weightOfConnection;
		sumOfErrorInNextLayer += errorOfNeuron;

	}

	this->n_sigmaError = sumOfErrorInNextLayer * outputDeriv;
	
}



void Neuron::calcHiddenLayerErrorLast(std::vector <Neuron> &nextLayer) {

	double outputDeriv = Neuron::D_activationFunction(this->returnOutputValue());

	double sumOfErrorInNextLayer = (double)0;

	std::vector <Neuron>::iterator n_itr;

	for (n_itr = nextLayer.begin(); n_itr != nextLayer.end(); ++n_itr) {


		double errorOfNeuron = double(0);

		errorOfNeuron = n_itr->n_sigmaError * this->connections[n_itr->n_indexOfNeuron].weightOfConnection;

		sumOfErrorInNextLayer += errorOfNeuron;

	}

	this->n_sigmaError = sumOfErrorInNextLayer * outputDeriv;
	
}

