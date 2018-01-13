#include "FileR.h"



void FileR::closeFile() {
	this->file.close();
	if(!file.is_open()) std::cout << "File closed!" << std::endl;
}



void FileR::openFile(std::string location) {

	this->file.open(location, std::ifstream::in);
	if (file.is_open()) std::cout << "File opened!" << std::endl;

}



bool FileR::readToTheString(std::queue <std::string> &line) {
	std::string line_;
	//reading from data file to queue of lines of string
	while (true) {
		std::getline(this->file, line_);
		if (!line_.compare("")) break;
		line.push(line_);
	}
	return true;
}



bool FileR::readDataFromQueue(std::queue <double> &inputValues,
	std::queue <double> &outputValues, std::queue <std::string> &line) {

	if (line.empty()) return false;//when queue is empty return false
	//and this way break while in Operations.cpp

	std::string line_ = line.front();
	line.pop();
	//pushing line to the stringstream variable
	std::stringstream ss(line_);
	std::string part;
	double val;
	int i = 0;//the number of data separated by ','
	while (i < 4) {
		std::getline(ss, part, ',');
		val = std::stod(part);
		inputValues.push(val);
		++i;
	}
	ss >> part;//the last data paramete, in this case name of flower
	//it is for the output values of course
	if (!part.compare("Iris-virginica")) {
		std::cout << std::endl << "Iris-virginica 0 1 0." << std::endl;
		outputValues.push((double)0);
		outputValues.push((double)1);
		outputValues.push((double)0);
	}
	else if (!part.compare("Iris-setosa")) {
		std::cout << std::endl << "Iris-setosa 1 0 0." << std::endl;
		outputValues.push((double)1);
		outputValues.push((double)0);
		outputValues.push((double)0);
	}
	else if (!part.compare("Iris-versicolor")) {
		std::cout << std::endl << "Iris-versicolor 0 0 1." << std::endl;
		outputValues.push((double)0);
		outputValues.push((double)0);
		outputValues.push((double)1);
	}
	return true;
}