#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include "nodes.h"

class AVLTree{ // OnlineGDB Class Example
    private:
         // Initialize the root to nullptr
        Node* root = nullptr;
        // Initialize the IDs to an empty set
        std::unordered_map<std::string, std::string> person;
        // Included helper functions to not allow the user to see the internals of the code
        Node* helperInsert(Node* helpRoot, std::string studentID, std::string name);
        void helperInorder(Node* helpRoot, std::vector<std::string>& names); 
        void helperPreorder(Node* helpRoot, std::vector<std::string>& names); 
        void helperPostorder(Node* helpRoot, std::vector<std::string>& names);
        int getHeight(Node* helpRoot); 
        void helperSearchName(Node* helpRoot, std::string targetName, std::vector<std::string>& IDs);
        Node* helperRemoveID(Node* helpRoot, std::string studentID);
        Node* helperRemoveInorder(Node* rootNode, int number, int& count);
        void helperDestructor(Node* helpRoot);
    public:
        // Constructor for the AVLTree class
        AVLTree();
        bool nameChecker(std::string name);
        bool idChecker(std::string id);
        Node* rotateRight(Node* helpRoot);
        Node* rotateLeft(Node* helpRoot);
        void insert(std::string studentID, std::string name);
        std::vector<std::string> inorder(); 
        std::vector<std::string> preorder(); 
        std::vector<std::string> postorder();
        int levelCount(); 
        void searchID(std::string studentID);
        void searchName(std::string targetName);
        void removeID(std::string studentID);
        void removeInorder(int number);
        // Create a destructor
        ~AVLTree();
};
