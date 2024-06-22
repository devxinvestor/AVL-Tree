#include "nodes.h"

// Constructor for the Node
Node::Node(std::string x, std::string y){
    // Initialize the tree height to 1
    height = 1;
    studentID = x;
    name = y;
    left = nullptr;
    right = nullptr;
}
