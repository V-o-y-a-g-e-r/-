#pragma once



#include "Libraries.h"
#include "FileR.h"
#include "Net.h"



class Operations {

public:
	static bool testNet(std::vector < std::vector <Neuron> > &NeuralNetwork, Net &net);
	static void showEpochErrors(void);
	static void n_EpochErrorOperations(void);
	static unsigned short net_Layer_Creator(void);
	static std::vector <unsigned short> net_Neuron_Cerator(unsigned short numberOfLayers);
	static void createNeuralNetwork(std::vector < std::vector <Neuron> > &NeuralNetwork, std::vector <unsigned short> &netStructure);
	static bool netOperations(void);
	static bool process(std::vector < std::vector <Neuron> > &NeuralNetwork, Net &net);
	static void crossDataValidation(void);
};
