#include "Operations.h"



long int i;
std::vector <double> n_EpochError;
std::vector < std::vector <double> > n_Shuffle;
std::vector <double> epochAvrg;
size_t sizeOfBigVector;
size_t sizeOfSmallVector;
std::queue <std::string> line;



void Operations::createNeuralNetwork(std::vector < std::vector <Neuron> > &NeuralNetwork, std::vector <unsigned short> &netStructure) {

	std::cout << "Creating the whole net with given layer and neuron sizes..." << std::endl;

	for (unsigned short i = 0; i < netStructure.size(); ++i) {

		NeuralNetwork.push_back(std::vector <Neuron>());
		std::cout << "Layer was created!" << std::endl;

		if (i != (netStructure.size() - 1)) {
			//creating neurons in all layers but output layer

			for (unsigned short j = 0; j <= netStructure[i]; ++j) {

				NeuralNetwork[i].push_back(Neuron(j, netStructure[i + 1]));
				std::cout << "Neuron in net was created!" << std::endl;
			}

			NeuralNetwork.back().back().setOutputValue(1);

		}

		else {
			//creating neurons in last layer, here there is no place for bias neuron 

			for (unsigned short j = 0; j < netStructure[i]; ++j) {

				NeuralNetwork[i].push_back(Neuron(j, unsigned short(0)));

				std::cout << "Neuron in last layer was created!" << std::endl;
			}

		}
	}
}



std::vector <unsigned short> Operations::net_Neuron_Cerator(unsigned short numberOfLayers) {

	std::vector <unsigned short> netStructure;

	std::cout << "Please, pass number of neurons respectively to the layer number, beginning from the first layer." << std::endl;

	for (unsigned short i = 0; i < numberOfLayers; ++i) {

		std::cout << "Please, pass the number of neurons in " << (i + 1) << " layer:" << std::endl;

		unsigned short n;
		std::cin >> n;
		netStructure.push_back(n);

	}

	std::cout << "Structue of the net is as follows." << std::endl;
	std::cout << "The number of layers is equal to: " << netStructure.size() << "." << std::endl;

	for (unsigned short i = 0; i < numberOfLayers; ++i) {

		if (i == (numberOfLayers - 1)) {

			std::cout << "Number of neurons in last layer is equal to: " << netStructure[i] << "." << std::endl;
		}

		else {

			std::cout << "Number of neurons in " << (i + 1) << " layer is equal to: " << (netStructure[i] + 1) << "." << std::endl;
		}

	}


	return netStructure;

}



unsigned short Operations::net_Layer_Creator(void) {

	std::cout << "How many layers the net should have? (Including input and output layer)." << std::endl;

	unsigned short numberOfLayers;
	std::cin >> numberOfLayers;

	std::cout << "Number of layers the Net has: " << numberOfLayers << "." << std::endl;

	return numberOfLayers;
}



bool Operations::process(std::vector < std::vector <Neuron> > &NeuralNetwork, Net &net) {

	srand((unsigned int)time(NULL));

	i = (long int)1;

	while (true) {
		//queues for input and output values
		std::queue <double> inputValues;
		std::queue <double> targetValues;
		//reading from the data file
		if (!FileR::readDataFromQueue(inputValues, targetValues, line)) break;

		std::cout << "Pass no.: " << i << "." << std::endl;
		//checking if the input data size is the same as number of
		//neurons in the input layer of the net
		if (!(net.feedFirstLayer(inputValues, NeuralNetwork[0]))) {

			std::cout << "Input values number shuld be the same as the number of neurons in input layer."
				<< std::endl;
			system("Pause");
			return false;
		}

		//forward propagation
		net.frowardPropagation(NeuralNetwork);

		//calculating the error for the output layer neurons
		if (!(net.calculateOutputError(targetValues, NeuralNetwork.back()))) {

			std::cout << "Target values should be the same size as the number of neurons in the output layer of the net." << std::endl;
			system("Pause");
			return false;
		}

		//back propagation
		net.backwardPropagation(NeuralNetwork);


		//now we need to update the weights of connections respectively to the errors calculated before
		net.updateWeightsOfConnections(NeuralNetwork);

		++i;
	}
	//if everything went good we return true
	return true;
}



bool Operations::netOperations() {

	Net net;
	std::vector < std::vector <Neuron> > NeuralNetwork;

	//creating our net, get info from the user

	unsigned short numberOfLayers = Operations::net_Layer_Creator();
	//setting the structure
	std::vector <unsigned short> netStructure = Operations::net_Neuron_Cerator(numberOfLayers);
	//creating neural net
	Operations::createNeuralNetwork(NeuralNetwork, netStructure);

	std::string filePath;
	filePath.append("C:\\Users\\£ukasz\\Desktop\\Programs\\NeuralNetwork\\");
	std::cout << "Which training file would You like to choose?" << std::endl;
	std::cout << "Type 'dataXOR', 'dataOR', 'dataNAND', 'dataAND'." << std::endl;
	std::cout << "Type flower file data." << std::endl;
	std::string getc;
	std::cin >> getc;
	std::cout << "Now the net will feed forward choosen data." << std::endl;
	filePath.append(getc);//setting the path to the data file
	filePath.append(".txt");

	//reading to the vector
	FileR file;
	file.openFile(filePath);
	file.readToTheString(line);
	file.closeFile();
	//closing after reading to the vector
	if (!Operations::process(NeuralNetwork, net)) {
		//when some error occured
		return false;
	}

	Operations::n_EpochErrorOperations();
	Operations::showEpochErrors();
	//do u want to test the net?
	std::string todo;
	std::cout << "Would You like to exit or do another training?" << std::endl;
	std::cout << "Type Exit or Training to procede further." << std::endl;
	std::cin >> todo;

	if ((todo == "Exit") || (todo == "exit")) {
		return true;
	}

	else {
		//if the user wanted to repeat the process
		Operations::netOperations();
		return true;
	}
}



void Operations::n_EpochErrorOperations(void) {
	size_t intDivider = 10;//min value of epochs vectors
	size_t smallIntDivider;//size of epoch errror vector
	//program will create vectors of epoch errors when it
	//occurs a value (min 10) which is divider of the size of
	//the vector with errors created in neuron.cpp
	while (true) {
		if (n_EpochError.size() % intDivider == 0) {
			smallIntDivider = n_EpochError.size() / intDivider;
			break;
		}
		else {
			++intDivider;
			continue;
		}
	}
	std::cout << "Size of data: " <<n_EpochError.size()<< ", size of epochs: " << intDivider 
		<< " and size of probes: " << smallIntDivider << "." << std::endl;
	sizeOfBigVector = intDivider;
	sizeOfSmallVector = smallIntDivider;
	//creating the vector which contains smaller vectors of erros in one epoch
	size_t j = 0;
	for (size_t i = 0; i < sizeOfBigVector; ++i) {
		n_Shuffle.push_back(std::vector <double>());
		for (true; j < sizeOfSmallVector; ++j) {
			n_Shuffle.back().push_back(n_EpochError[j]);
		}
		sizeOfSmallVector += smallIntDivider;
	}
	//now we will create a vector which contains average error
	//of epochs, every element equals to one epoch
	std::vector < std::vector <double > >::iterator n_itr;
	std::vector <double>::iterator itr;
	double val = 0;
	for (n_itr = n_Shuffle.begin(); n_itr != n_Shuffle.end(); ++n_itr) {
		for (itr = n_itr->begin(); itr != n_itr->end(); ++itr) {
			val += *itr;
		}
		val /= n_itr->size();
		epochAvrg.push_back(val);
		val = 0;
	}
}



void Operations::showEpochErrors(void) {

	std::vector <double>::iterator itr;
	int i = 0;
	for (itr = epochAvrg.begin(); itr != epochAvrg.end(); ++itr) {
		++i;
		std::cout << "Average of " << i << " epoch is equal to: " << "." << *itr << std::endl;
	}
}