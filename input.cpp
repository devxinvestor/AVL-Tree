#include "input.h"
#include <regex>
#include <iostream>
#include <sstream>

// Constructor for the Input class
Input::Input(){
    function = std::string("");
    name = std::string("");
    id = std::string("");
}

// Function to read the command from the input stream and call the appropriate function
void Input::readCommand(std::istringstream& in, AVLTree& myTree){
    
    in >> function;

    if (function == "insert") {
        getline(in, name, '"');
        getline(in, name, '"');

        in >> id;

        myTree.insert(id, name);
        return;
    }

    else if (function == "search"){
        in >> std::ws;
        if (in.peek() != '"'){
            in >> id;
            myTree.searchID(id);
            return;
        }
        else {
            getline(in, name, '"');
            getline(in, name, '"');
            myTree.searchName(name);
            return;
        }
    }

    else if (function == "remove"){
        in >> id;
        myTree.removeID(id);
        return;
    }

    else if (function == "printInorder"){
        myTree.inorder();
        return;
    }

    else if (function == "printPreorder"){
        myTree.preorder();
        return;
    }

    else if (function == "printPostorder"){
        myTree.postorder();
    }

    else if (function == "printLevelCount"){
        std::cout << myTree.levelCount() << std::endl;
        return;
    }

    else if (function == "removeInorder"){
        in >> id;
        myTree.removeInorder(std::stoi(id));
        return;
    }

    else {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
}