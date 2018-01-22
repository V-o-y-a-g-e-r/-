#include "FileR.h"

//this file has nothing to do with the net itself
//it must be changed to feed other data type
extern int dataNum;

//for now it is set to feed, train and test iris data - file

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


//this is the only method that should be changed by user to read varius data files
bool FileR::readDataFromQueue(std::queue <double> &inputValues,
	std::queue <double> &outputValues, std::string lineFromVec) {
	std::string part;
	double var;
	std::stringstream ss(lineFromVec);
	//#1,
	std::getline(ss, part, ',');
	var = std::stod(part);
	inputValues.push(var);
	//#2,
	std::getline(ss, part, ',');
	var = std::stod(part);
	inputValues.push(var);
	//#3,
	std::getline(ss, part, ',');
	var = std::stod(part);
	inputValues.push(var);
	//#4,
	std::getline(ss, part, ',');
	var = std::stod(part);
	inputValues.push(var);
	//output flower name
	ss >> part;
	//conditions for output layer data setting
	if (!part.compare("Iris-virginica")) {
		std::cout << std::endl << "Iris-virginica 0 1 0." << std::endl;
		outputValues.push((double)0);
		outputValues.push((double)1);
		outputValues.push((double)0);
		dataNum = 2;
	}
	else if (!part.compare("Iris-setosa")) {
		std::cout << std::endl << "Iris-setosa 1 0 0." << std::endl;
		outputValues.push((double)1);
		outputValues.push((double)0);
		outputValues.push((double)0);
		dataNum = 1;
	}
	else if (!part.compare("Iris-versicolor")) {
		std::cout << std::endl << "Iris-versicolor 0 0 1." << std::endl;
		outputValues.push((double)0);
		outputValues.push((double)0);
		outputValues.push((double)1);
		dataNum = 3;
	}
	return true;
}