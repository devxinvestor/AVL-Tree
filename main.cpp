#include "GatorAVL.h"
#include "input.h"
#include <sstream>

int main(){
	//Create an instance of AVLTree
	AVLTree myTree;
	// Create an instance of Input
	Input text;

	int numCommands;
	std::cin >> numCommands;
	std::cin.ignore(2, '\n');

	for (int i = 0; i < numCommands; i++){
		std::string line;
		std::getline(std::cin, line);

		std::istringstream in(line);
		text.readCommand(in, myTree);
		in.ignore(2, '\n');
	}
	return 0;
}
