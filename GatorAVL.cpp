#include "GatorAVL.h"
#include "nodes.h"
#include <iostream>
#include <vector>
#include <regex>

// Constructor for the AVL Tree with a nullptr root
AVLTree::AVLTree(){
    this->root = nullptr;
    std::unordered_map<std::string, std::string> person;
}

// Check if the name is valid
bool AVLTree::nameChecker(std::string name){
    // Use regex to see if the name is only letters and spaces
    std::regex obj = std::regex("^[a-zA-Z\\s]*$");
    if (!std::regex_match(name, obj)){
        return false;
    }
    return true;
}

// Check if the ID is valid
bool AVLTree::idChecker(std::string id){
    // Use regex to see if the ID is 8 numbers
    std::regex obj = std::regex("[0-9]{8,8}");
    if (id.size() != 8 || !std::regex_match(id, obj)){
        return false;
    }
    return true;
}

// Helper inorder function to traverse the AVL Tree
void AVLTree::helperInorder(Node* helpRoot, std::vector<std::string>& names) {
    if(helpRoot == nullptr)
        return;
    else
    {
        // Recursively call the left child, push the name, and then call the right child
        helperInorder(helpRoot->left, names);
        names.push_back(helpRoot->name);
        helperInorder(helpRoot->right, names);
    }
}

// Helper preorder function to traverse the AVL Tree
void AVLTree::helperPreorder(Node* helpRoot, std::vector<std::string>& names) {
    if(helpRoot == nullptr)
        return;
    else
    {
        // Recursively push the name, call the left child, and then the right child
        names.push_back(helpRoot->name);
        helperPreorder(helpRoot->left, names);
        helperPreorder(helpRoot->right, names);
    }
}

// Helper postorder function to traverse the AVL Tree
void AVLTree::helperPostorder(Node* helpRoot, std::vector<std::string>& names) {
    if(helpRoot == nullptr)
        return;
    else
    {
        // Recursively call the left child, right child, and then push the name
        helperPostorder(helpRoot->left, names);
        helperPostorder(helpRoot->right, names);
        names.push_back(helpRoot->name);
    }
}

// Rotate right method to balance the AVL Tree
Node* AVLTree::rotateRight(Node* helpRoot){
    Node* newParent = helpRoot->left;
    Node* grandchild = helpRoot->left->right;
    newParent->right = helpRoot;
    helpRoot->left = grandchild;
    // Adjust the height of the nodes
    helpRoot->height = 1 + std::max(getHeight(helpRoot->left), getHeight(helpRoot->right));
    newParent->height = 1 + std::max(getHeight(newParent->left), getHeight(newParent->right));
    return newParent;
}

// Rotate left method to balance the AVL Tree
Node* AVLTree::rotateLeft(Node* helpRoot){
    Node* newParent = helpRoot->right;
    Node* grandchild = helpRoot->right->left;
    newParent->left = helpRoot;
    helpRoot->right = grandchild;
    helpRoot->height = 1 + std::max(getHeight(helpRoot->left), getHeight(helpRoot->right));
    newParent->height = 1 + std::max(getHeight(newParent->left), getHeight(newParent->right));
    return newParent;
}

// Method to simply getting the height of the node
// This function makes sure that if the node is nullptr, it returns 0
int AVLTree::getHeight(Node* helpRoot){
    if (helpRoot == nullptr)
        return 0;
    else
        return helpRoot->height;
}

Node* AVLTree::helperInsert(Node* helpRoot, std::string studentID, std::string name){
    // If the root is nullptr, create a new node
    if (helpRoot == nullptr){
        return new Node(studentID, name);
    }
    // Recursively insert the node into the AVL Tree
    else if (std::stoi(studentID) < std::stoi(helpRoot->studentID)){
        helpRoot->left = helperInsert(helpRoot->left, studentID, name);
    }
    else if (std::stoi(studentID) > std::stoi(helpRoot->studentID)){
        helpRoot->right = helperInsert(helpRoot->right,studentID, name);
    }
    else {
        return helpRoot;
    }

    // Adjust the height of the nodes
    helpRoot->height = 1 + std::max(getHeight(helpRoot->left), getHeight(helpRoot->right));

    // If the tree is right heavy
    if (getHeight(helpRoot->left) - getHeight(helpRoot->right) < -1){
        // If the tree's right subtree is left heavy
        if (getHeight(helpRoot->right->left) - getHeight(helpRoot->right->right) > 0){
            helpRoot->right = rotateRight(helpRoot->right);
            return rotateLeft(helpRoot);
        }
        else{
            return rotateLeft(helpRoot);
        }
    }

    // If the tree is left heavy
    else if (getHeight(helpRoot->left) - getHeight(helpRoot->right) > 1){
        // If the tree's left subtree is right heavy
        if (getHeight(helpRoot->left->left) - getHeight(helpRoot->left->right) < 0){
            helpRoot->left = rotateLeft(helpRoot->left);
            return rotateRight(helpRoot);
        }
        else{
            return rotateRight(helpRoot);
        }
    }
    return helpRoot;
}

// Method to search for the name in the AVL Tree
void AVLTree::helperSearchName(Node* helpRoot, std::string targetName, std::vector<std::string>& IDs){
    if (helpRoot == nullptr){
        return;
    }
    else {
        // Recursively search the left child, check if the name is the same, and then search the right child
        helperSearchName(helpRoot->left, targetName, IDs);
        if (helpRoot->name == targetName){
            IDs.push_back(helpRoot->studentID);
        }
        helperSearchName(helpRoot->right, targetName, IDs);
    }
}

// Method to remove the node with the student ID
Node* AVLTree::helperRemoveID(Node* helpRoot, std::string studentID){
    if (helpRoot == nullptr)
        return nullptr;

    // Recursively remove the node with the student ID
    else if (std::stoi(studentID) < std::stoi(helpRoot->studentID)) {
        helpRoot->left = helperRemoveID(helpRoot->left, studentID);
    }
    else if (std::stoi(studentID) > std::stoi(helpRoot->studentID)) {
        helpRoot->right = helperRemoveID(helpRoot->right, studentID);
    }
    else {
        // If the node has no children, delete the node
        if (helpRoot->left == nullptr && helpRoot->right == nullptr) {
            delete helpRoot;
            return nullptr;
        }
        // If the node has one child, replace the node with the child
        else if (helpRoot->left != nullptr && helpRoot->right == nullptr) {
            Node* newHelpRoot = helpRoot->left;
            delete helpRoot;
            return newHelpRoot;
        }
        else if (helpRoot->left == nullptr && helpRoot->right != nullptr) {
            Node* newHelpRoot = helpRoot->right;
            delete helpRoot;
            return newHelpRoot;
        }
        else {
            // If the node has two children, replace the node with the inorder successor
            Node* newHelpRoot = helpRoot->left;
            Node* parent = helpRoot;
            while (newHelpRoot->right != nullptr){
                parent = newHelpRoot;
                newHelpRoot = newHelpRoot->right;
            }
            // Recursively remove the inorder successor
            helpRoot->studentID = newHelpRoot->studentID;
            helpRoot->name = newHelpRoot->name;
            if(parent == helpRoot)
                parent->left = newHelpRoot->left;
            else
                parent->right = newHelpRoot->left;
            delete newHelpRoot;
        }
    }
    return helpRoot;
}

// Method to remove the node with the student ID
Node* AVLTree::helperRemoveInorder(Node* rootNode, int number, int& count) {
    if (rootNode == nullptr)
        return nullptr;

    // Recursively traverse the left subtree
    rootNode->left = helperRemoveInorder(rootNode->left, number, count);
    
    // Check if the current node is the Nth node
    if (count == number) {
        Node* newHelpRoot;
        if (rootNode->left == nullptr || rootNode->right == nullptr) {
            // Node with only one child or no child
            if (rootNode->left != nullptr) 
                newHelpRoot = rootNode->left;
            else
                newHelpRoot = rootNode->right;

            // No child case
            if (newHelpRoot == nullptr) {
                newHelpRoot = rootNode;
                rootNode = nullptr;
            } 
            // One child case
            else {
                if(rootNode->left == newHelpRoot) 
                    rootNode = rootNode->left;
                else
                    rootNode = rootNode->right;
            }
            delete newHelpRoot;
        } 
        else {
            // Node with two children
            Node* parent = rootNode;
            Node* nextNode = rootNode->right;
            while (nextNode->left != nullptr) {
                parent = nextNode;
                nextNode = nextNode->left;
            }

            rootNode->studentID = nextNode->studentID;

            // Delete the inorder successor
            if (parent->left == nextNode)
                parent->left = nextNode->right;
            else
                parent->right = nextNode->right;

            delete nextNode;
        }
        count++;
        return rootNode;
    }
    if (rootNode != nullptr) {
        count++;

        // Recursively traverse the right subtree
        rootNode->right = helperRemoveInorder(rootNode->right, number, count);
    }

    return rootNode;
}

// Destructor to delete the AVL Tree
void AVLTree::helperDestructor(Node* helpRoot){
    if (helpRoot == nullptr)
        return;
    else {
        // Recursively delete the left child, right child, and then the root
        helperDestructor(helpRoot->left);
        helperDestructor(helpRoot->right);
        delete helpRoot;
    }
}

// Method to print the AVL Tree in Inorder Traversal
std::vector<std::string> AVLTree::inorder(){
    std::vector<std::string> names;
    // Call the helper inorder function to traverse the AVL Tree
    helperInorder(this->root, names);
    if (names.empty())
        std::cout << "unsuccessful" << std::endl;
    for (int i = 0; i < names.size(); ++i) {
        std::cout << names[i];
        if (i != names.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    return names;
}

// Method to print the AVL Tree in Preorder Traversal
std::vector<std::string> AVLTree::preorder(){
    std::vector<std::string> names;
    // Call the helper preorder function to traverse the AVL Tree
    helperPreorder(this->root, names);
    if (names.empty())
        std::cout << "unsuccessful" << std::endl;
    for (int i = 0; i < names.size(); ++i) {
        std::cout << names[i];
        if (i != names.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    return names;
}

// Method to print the AVL Tree in Postorder Traversal
std::vector<std::string> AVLTree::postorder(){
    std::vector<std::string> names;
    // Call the helper postorder function to traverse the AVL Tree
    helperPostorder(this->root, names);
    if (names.empty())
        std::cout << "unsuccessful" << std::endl;
    for (int i = 0; i < names.size(); ++i) {
        std::cout << names[i];
        if (i != names.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    return names;
}

// Method to insert the student ID and name into the AVL Tree
void AVLTree::insert(std::string studentID, std::string name){
    // If the student ID is already in the AVL Tree, the name is invalid, or the ID is invalid, return unsuccessful
    if (person.find(studentID) != person.end() || !nameChecker(name) || !idChecker(studentID)){
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    else {
        // Insert the student ID and name into the AVL Tree
        person[studentID] = name;
        this->root = helperInsert(this->root, studentID, name);
        std::cout << "successful" << std::endl;
        return;
    }
}

// Method to get the level count of the AVL Tree
int AVLTree::levelCount(){
    if (this->root == nullptr){
        return 0;
    }
    else {
        // Get the height of the AVL Tree
        int leftHeight = getHeight(this->root->left);
        int rightHeight = getHeight(this->root->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
}

// Method to search for the student ID in the AVL Tree
void AVLTree::searchID(std::string studentID){
    // If the student ID is in the AVL Tree and the ID is valid, print the name
    if (person.find(studentID) != person.end() && idChecker(studentID)){
        std::cout << person[studentID] << std::endl;
    }
    else {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Method to search for the name in the AVL Tree
void AVLTree::searchName(std::string targetName){
    std::vector<std::string> IDs;
    // Call the helper search name function to search for the name in the AVL Tree
    helperSearchName(root, targetName, IDs);
    if (IDs.empty() || !nameChecker(targetName)){
        std::cout << "unsuccessful" << std::endl;
    }
    else {
        for (int i = 0; i < IDs.size(); ++i) {
            std::cout << IDs[i] << std::endl;
        }
    }
}

// Method to remove the student ID from the AVL Tree
void AVLTree::removeID(std::string studentID){
    // If the student ID is in the AVL Tree and the ID is valid, remove the student ID
    if (person.find(studentID) != person.end() && idChecker(studentID)){
        person.erase(studentID);
        this->root = helperRemoveID(this->root, studentID);
        std::cout << "successful" << std::endl;
    }
    else {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Method to remove the student ID from the AVL Tree
void AVLTree::removeInorder(int number){
    if (number >= person.size()){
        std::cout << "unsuccessful" << std::endl;
    }
    else {
        int count = 0;
        // Call the helper remove inorder function to remove the student ID
        helperRemoveInorder(this->root, number, count);
        std::cout << "successful" << std::endl;
    }
}

// Destructor to delete the AVL Tree
AVLTree::~AVLTree(){
    // Call the helper destructor function to delete the AVL Tree
    helperDestructor(root);
}
