#include "Net.h"


//output layer error calculations
bool Net::calculateOutputError(std::queue <double> &targetValues, std::vector <Neuron> &lastLayer) {

	if (targetValues.size() != lastLayer.size()) {

		return false;

	}


	std::vector <Neuron>::iterator i;

	for (i = lastLayer.begin(); i != lastLayer.end(); ++i) {

		std::cout << "Output value: " << i->returnOutputValue() << " " << "Expected output value: " << targetValues.front() << std::endl;
		i->calcOutputLayerError(targetValues.front());
		targetValues.pop();

	}

	

	return true;

}


//here we are updating weights of connections after we have propagated backwards
void Net::updateWeightsOfConnections(std::vector < std::vector <Neuron> > &NeuralNetwork) {

	std::vector < std::vector <Neuron> >::iterator iterator;

	std::vector < std::vector <Neuron> >::iterator previousIterator;

	iterator = NeuralNetwork.end();
	--iterator;

	std::vector <Neuron>::iterator i_neuron;

	previousIterator = iterator;

	--previousIterator;

	for (i_neuron = iterator->begin(); i_neuron != iterator->end(); ++i_neuron) {

		i_neuron->updateWeights(*previousIterator);

	}

	for (--iterator; iterator != (++NeuralNetwork.begin()); --iterator) {

		--previousIterator;

		for (i_neuron = iterator->begin(); i_neuron != (--iterator->end()); ++i_neuron) {

			i_neuron->updateWeights(*previousIterator);

		}

	}

	--previousIterator;

	for (i_neuron = iterator->begin(); i_neuron != (--iterator->end()); ++i_neuron) {

		i_neuron->updateWeights(*previousIterator);
		std::cout << std::endl;

	}

}



void Net::backwardPropagation(std::vector < std::vector <Neuron> > &NeuralNetwork) {

	//now we need to calculate sum of n_sigmaerrors * weight of connections * D_actfunction
	//to do such thing, i'll make useful again the itarator

	std::vector < std::vector <Neuron> >::iterator iterator;
	std::vector < std::vector <Neuron> >::iterator nextIterator;

	iterator = NeuralNetwork.end();

	--iterator;

	--iterator;

	nextIterator = iterator;

	++nextIterator;

	std::vector <Neuron>::iterator i_neuron;


	for (i_neuron = iterator->begin(); i_neuron != iterator->end(); ++i_neuron) {

		i_neuron->calcHiddenLayerErrorLast(*nextIterator);

	}

	for (--iterator; iterator != NeuralNetwork.begin(); --iterator) {

		//iterating to the first layer where we do not want to calculate sigma of error

		--nextIterator;

		for (i_neuron = iterator->begin(); i_neuron != iterator->end(); ++i_neuron) {

			i_neuron->calcHiddenLayerError(*nextIterator);

		}

	}

}



bool Net::feedFirstLayer(std::queue <double> &inputValues, std::vector <Neuron> &firstLayer) {

	if (inputValues.size() != (firstLayer.size() - (unsigned short)1)) {

		return false;

	}

	for (unsigned short i = 0; i < (firstLayer.size() - (unsigned short)1); ++i) {

		firstLayer[i].setOutputValue(inputValues.front());
		inputValues.pop();

	}

	return true;
}



void Net::frowardPropagation(std::vector < std::vector <Neuron> > &NeuralNetwork) {


	//forward propagating to the end of the net, to the output layer

	std::vector < std::vector <Neuron> >::iterator iterator;

	std::vector < std::vector <Neuron> >::iterator prevIterator;

	for (iterator = (++NeuralNetwork.begin()); iterator != NeuralNetwork.end(); ++iterator) {

		prevIterator = iterator;

		--prevIterator;

		std::vector <Neuron>::iterator i_neuron;

		if (iterator == (--NeuralNetwork.end())) {

			for (i_neuron = iterator->begin(); i_neuron != iterator->end(); ++i_neuron) {

				i_neuron->feedForwardForNeuron(*prevIterator);

			}
		}
		else {

			for (i_neuron = iterator->begin(); i_neuron != (--iterator->end()); ++i_neuron) {

				i_neuron->feedForwardForNeuron(*prevIterator);

			}

		}

	}
}