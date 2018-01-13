#include "Libraries.h"
#include "Operations.h"



int main() {

	if (!Operations::netOperations()) {

		std::cout << "Some error occured..." << std::endl;

		return -1;

	}


	system("Pause");


	return 0;


}