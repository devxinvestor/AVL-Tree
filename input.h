#pragma once
#include "GatorAVL.h"
#include <sstream>

// Class to read the input commands
class Input {
    private:
        std::string function;
        std::string name;
        std::string id;
    public:
        Input();
        void readCommand(std::istringstream& in, AVLTree& myTree);
};