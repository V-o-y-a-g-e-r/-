#pragma once



#include "Libraries.h"



class FileR {

public:
	FileR() = default;
	~FileR() = default;
	void closeFile();
	void openFile(std::string location);
	bool readToTheString(std::queue <std::string> &line);
	static bool readDataFromQueue(std::queue <double> &inputValues,
		std::queue <double> &outputValues, std::string lineFromVec);

private:

	std::ifstream file;

};


