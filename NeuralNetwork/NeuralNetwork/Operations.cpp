#include "Operations.h"

//this file contains class operations which is basically the whole structure 
//where we are training the net or testing
double good;
int dataNum;
int step;
long int i;
std::queue <double> average;
std::queue <double> n_EpochError;//big container for errors
std::queue <std::string> line;
std::vector < std::vector <std::string> > partLines;//data valid
size_t sizeOfVec;//data valid
size_t sizeSmallVec;//data valid



void Operations::createNeuralNetwork(std::vector < std::vector <Neuron> > &NeuralNetwork, std::vector <unsigned short> &netStructure) {

	std::cout << "Creating the whole net with given layer and neuron sizes..." << std::endl;

	for (unsigned short i = 0; i < netStructure.size(); ++i) {
		//here i'm letting know the user of the amount of neurons and layers created
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

	step = 0;
	while (step < (partLines.size() - 1)) {
		std::cout << "Vector of data: " << std::endl;
		i = (long int)0;

		while (i < partLines[step].size()) {
			//queues for input and output values
			std::queue <double> inputValues;
			std::queue <double> targetValues;
			//reading from the data file
			if (!FileR::readDataFromQueue(inputValues, targetValues, partLines[step][i])) break;

			std::cout << "Pass in one vector no.: " << i+1 << "." << std::endl;
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
		
		Operations::n_EpochErrorOperations();
		

		++step;
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
	//adding the file path
	std::string filePath;
	filePath.append("C:\\Users\\£ukasz\\Desktop\\Repozytoria\\-\\NeuralNetwork\\");
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
	Operations::crossDataValidation();//setting up few vectors including data from testing file

	//closing after reading to the vector
	if (!Operations::process(NeuralNetwork, net)) {
		//when some error occured
		return false;
	}
	//return error average of training
	Operations::showEpochErrors();
	//testing the net
	Operations::testNet(NeuralNetwork, net);

	//what user wants to do further
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
	size_t size = n_EpochError.size();
	double avg = 0;
	while (!n_EpochError.empty()) {
		avg += n_EpochError.front();
		n_EpochError.pop();
	}
	avg /= (double)size;
	average.push(avg);
}



void Operations::showEpochErrors(void) {
	int i = 1;
	while (!average.empty()) {
		std::cout << "Average error of " << i << " vector of data is equal to: "
			<< average.front() << "." << std::endl;
		average.pop();
		++i;
	}
}



void Operations::crossDataValidation(void) {

	sizeOfVec = 4;//minimum amount of small data vectors
	while (true) {
		if (line.size() % sizeOfVec == 0) {
			sizeSmallVec = line.size() / sizeOfVec;
			break;
		}
		++sizeOfVec;
	}
	std::cout << line.size() << "Size of big vector: " << sizeOfVec 
		<< ", size of small vectors: " 
		<< sizeSmallVec << std::endl;
	size_t helpSize = sizeSmallVec;
	size_t j = 0;
	for (size_t i = 0; i < sizeOfVec; ++i) {
		partLines.push_back(std::vector <std::string>());
		for (true; j < sizeSmallVec; ++j) {
			partLines.back().push_back(line.front());
			line.pop();
		}
		sizeSmallVec += helpSize;
	}

	std::vector < std::vector <std::string> >::iterator itr;
	std::vector <std::string>::iterator i;

	for (itr = partLines.begin(); itr != partLines.end(); ++itr) {
		for (i = itr->begin(); i != itr->end(); ++i) {
			std::cout << "Text in vec: " << *i << std::endl;
		}
		std::cout << std::endl;
	}

}



bool Operations::testNet(std::vector < std::vector <Neuron> > &NeuralNetwork, Net &net) {
	std::cout << "\n\nNow the neural net will be tested." << std::endl;
	int i = 0;
	good = 0;
	while (i < partLines[step].size()) {

		std::queue <double> inputValues;
		std::queue <double> targetValues;

		if (!FileR::readDataFromQueue(inputValues, targetValues, partLines[step][i])) break;

		std::cout << "Pass in test vector no.: " << i + 1 << "." << std::endl;
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

		//show the result of one test

		std::vector <Neuron>::iterator i_;
		double result = NeuralNetwork.back()[0].returnOutputValue();
		int counter = 1;
		for (i_ = NeuralNetwork.back().begin(); i_ != NeuralNetwork.back().end(); ++i_) {
			std::cout << "Output value: " << i_->returnOutputValue() << "." << std::endl;
			if (result < i_->returnOutputValue()) {
				result = i_->returnOutputValue();
				++counter;
			}
		}
		std::cout << "Net predicted this result: " << result << "." << std::endl;
		std::cout << "This is the biggest value, which indicates the answer." << std::endl;
		std::cout << "Net predicted " << counter << " flower." << std::endl;
		std::cout << "Flowe that should be precicted: " << dataNum << "." << std::endl;
		if (counter == dataNum) ++good;
		++i;
	}
	std::cout << "Precentage of corretness of the net: " 
		<< (good/(double)i)*(double)100 << "." << std::endl;
	return true;
}