#include "nodes.h"

// Constructor for the Node
// https://www.onlinegdb.com/vWp_hhaQlC
Node::Node(std::string x, std::string y){
    // Initialize the tree height to 1
    height = 1;
    studentID = x;
    name = y;
    left = nullptr;
    right = nullptr;
}