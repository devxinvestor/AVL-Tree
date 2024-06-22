#pragma once
#include <iostream>

// Create a struct Node for the Tree
// https://www.onlinegdb.com/vWp_hhaQlC
struct Node{
    std::string studentID;
    int height;
    std::string name;
    Node* left;
    Node* right;
    Node(std::string x, std::string y);
};
