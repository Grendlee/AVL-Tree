// AVL.h file
// Descriptions: This class is a template class for the AVL 
// Author: Grantley
// Creation date: June 15, 2023

#include "BST.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <typename T>
class AVL : public BST<T>
{
    public:

        AVL(); //default constructor

        AVL(T d); //constructor


        int checkBalance(typename BST<T>::Node* node);//check the balance of the node and perform rotations

        void  InsertNodeAVL(T d); //insert a node into the tree

        void DeleteAVLTree(); //delete 
        typename BST<T>::Node* DeleteAVLTree(typename BST<T>::Node* node);//helper 




        typename BST<T>::Node* leftRotation(typename BST<T>::Node* node); //left rotation up
        typename BST<T>::Node* rightRotation(typename BST<T>::Node* node); //right rotation up
        typename BST<T>::Node* getRoot(); //get the root of the avl
        typename BST<T>::Node* balanceTheNode(typename BST<T>::Node* node); //balance the node by performing rotations

        void DeleteNodeAVL(int target);//delete a target
        typename BST<T>::Node* DeleteNodeAVL(typename BST<T>::Node* root, int toDelete); //helper
        int getHeight(typename BST<T>::Node* node); //get the hight of the node
        AVL<T>* BuildAVLTree(string filename);//build a tree from a file
        
        
    private:
        void deleteByCopying(typename BST<T>::Node* &node);//delete the node and copy the tree
        void updateHeight(typename BST<T>::Node* node);//update the height of the node
        typename BST<T>::Node* root;//root
        typename BST<T>::Node* insertR_AVL(typename BST<T>::Node* root, T d);//helper
        
};


template <typename T>
void AVL<T>::DeleteNodeAVL(int target) //delete a node in the tree
{
    if(root == nullptr) //tree emty //nothing to delete
    {
        return;
    }   

    root = DeleteNodeAVL(root, target); //call helper 

    root = balanceTheNode(root);//balance the root
}

template <typename T>
AVL<T>* AVL<T>::BuildAVLTree(string filename) //build a tree from a txt file
{
    ifstream file(filename);

    if (!file.is_open()) 
    {
        return nullptr;
    }

    
    AVL<T>* avl = new AVL<T>(); //initialize

    string firstLine;
    getline(file, firstLine); //forget first line

    T data;

    while (file >> data) { //read the other lines
        avl-> InsertNodeAVL(data); //insert each number
    }

    file.close();

    return avl;
}

//delete a node in the tree
template <typename T>
typename BST<T>::Node* AVL<T>::DeleteNodeAVL(typename BST<T>::Node* node, int target) 
{
    if(node == nullptr)//no node to delete
    {
        return node;
    }
    else if(target < node->data)
    {
        node->left = DeleteNodeAVL(node->left, target); //recursively find the node to delete in the left
    }
    else if(target > node->data)
    {
        node->right = DeleteNodeAVL(node->right, target); //recursively find the node to delete in the right
    }
    else
    {
        deleteByCopying(node); //delete by copy, end recursive calls
    }

    //update the height of each node visited in the recusive call
    updateHeight(node);

    //balance the nodes if needed
    return balanceTheNode(node);
}

//delete by copy from bita class slides
template<class T>
void AVL<T>::deleteByCopying(typename BST<T>::Node* &node)
{
    typename BST<T>::Node* prev, *tmp = node;

    if(node->right == nullptr)
    {
        node = node->left;
    }
    else if(node->left == nullptr)
    {
        node = node->right;
    }
    else
    {

        tmp = node->left;
        prev = node;
        while (tmp->right != nullptr)
        {
            prev = tmp;
            tmp = tmp->right;
        }
        node->data = tmp->data;

        if(prev == node)
        {
            prev->left = tmp->left;
        }
        else
        {
            prev->right = tmp->left;
        }
    }

    delete tmp;
}



//default constructor
template <typename T>
AVL<T>::AVL()
{
    root = nullptr;
}

//constructor
template <typename T>
AVL<T>::AVL(T d)
{
    root = new typename BST<T>::Node(d);
}

// returns root
template <typename T>
typename BST<T>::Node* AVL<T>::getRoot()
{
    return root;
}

// checks the balance at a certain node O(1)
template <typename T>
int AVL<T>::checkBalance(typename BST<T>::Node* parent)
{
    
    int leftHeight = 0;
    int rightHeight = 0;

    if (parent->left != nullptr) //check the balance of the left tree
    {
        leftHeight = parent->left->height;
    }

    if (parent->right != nullptr) //check the balance of the left tree
    {
        rightHeight = parent->right->height;
    }

    return rightHeight - leftHeight; //return balance factor
}

// updateHeight
template <typename T>
void AVL<T>::updateHeight(typename BST<T>::Node* root)
{
    
    if(root == nullptr) //no hieght to be updated
    {
        return;
    }

    int left = getHeight(root->left); //get the height of the left sub tree
    int right = getHeight(root->right); //get the height of the right sub tree

    if(left > right)
    {
        root->height = left + 1; //increase height by 1 more than the left
    }
    else
    {
        root->height = right + 1;//increase height by 1 more than the right
    }
}

// O(1) set/get height
template <typename T>
int AVL<T>::getHeight(typename BST<T>::Node* parent)
{
    if(parent == nullptr)
    {
        return 0;
    }

    return parent->height;
}


//insert to build avl
template <typename T>
void AVL<T>:: InsertNodeAVL(T d)  
{
    root = insertR_AVL(root, d);  // call the base insertR_AVL function to find a spot to insert d

    root = balanceTheNode(root); //balance the root after insertion
}

//left rotation
template <typename T>
typename BST<T>::Node* AVL<T>::leftRotation(typename BST<T>::Node* parent)
{
    typename BST<T>::Node* pivot = parent->right;//pivot is the value of parent right
    typename BST<T>::Node* tmp = pivot->left; //save the value of left of pivot

    pivot->left = parent; //pivot left is not the parent
    pivot->left->right = tmp; //pivot left right in the value saved in tmp

    updateHeight(parent);//update the height of the parent because it is now lower in the pivot tree
    updateHeight(pivot); //update the pivot height now with the correct hiehg of parent in the pivot tree

    return pivot;
}

//same logic as leftRotation but inverse
template <typename T>
typename BST<T>::Node* AVL<T>::rightRotation(typename BST<T>::Node* parent)
{
    typename BST<T>::Node* pivot = parent->left; 
    typename BST<T>::Node* tmp = pivot->right;

    pivot->right = parent;
    pivot->right->left = tmp;

    updateHeight(parent);
    updateHeight(pivot);
    return pivot;
}

//perform balancing on the node
template <typename T>
typename BST<T>::Node* AVL<T>::balanceTheNode(typename BST<T>::Node* node)
{
    if(node == nullptr) //no need to balance
    {
        return node;
    }
    
    int bal = checkBalance(node);//check the balance factor
    typename BST<T>::Node* balanced = node; //create a tmp variable to be balanced
    if(bal < -1)//left heavy
    {

        if(checkBalance(balanced->left) > 0)//left right //double rotation
        {
            balanced->left = leftRotation(balanced->left);//perform the left rotation balanced -left
            balanced = rightRotation(balanced);//perform the right rotationon balanced
        }
        else if(checkBalance(balanced->left) <= 0)//left left //single rotation
        {
            balanced = rightRotation(balanced);
        }
        // node = pivot; //assign complete pivot structure to node
        return balanced;
    }
    else if(bal > 1) //right heavy
    {
        //same as check_balance(node) < -1 but inverse
        if(checkBalance(balanced->right) >= 0)//right right //single rotation
        {
            balanced = leftRotation(balanced);
        }
        else if(checkBalance(balanced->right) < 0)//right left //double
        {

            balanced->right = rightRotation(balanced->right);

            balanced = leftRotation(balanced);
        }
        return balanced;
    }
    else
    {
        return balanced;
    }
}

//helper for  InsertNodeAVL
template <typename T>
typename BST<T>::Node* AVL<T>::insertR_AVL(typename BST<T>::Node* node, T d)
{

    if(node == nullptr) //tree empty //found correct spot to insert
    {
        return new typename BST<T>::Node(d);
    }

    if(d <= node->data)//recursive call to find correct spot
    {
        node->left = insertR_AVL(node->left, d);
    }
    else if(d > node->data)
    {
        node->right = insertR_AVL(node->right, d);
    }

    //node inserted
    //update height for each node visited
    updateHeight(node);

    node = balanceTheNode(node); //balance the node if needed

    //return the node at each recursive call 
    return node;
}


//delete the tree
template <typename T>
void AVL<T>::DeleteAVLTree()
{
    root = DeleteAVLTree(root); //delete the root
    root = nullptr; //assign root to nullptr to avoid dangling pointer undefined behaviour
}


template <typename T>
typename BST<T>::Node* AVL<T>::DeleteAVLTree(typename BST<T>::Node* node)
{

    if(node == nullptr) //no node to delete
    {
        return node;
    }

    if(node->left != nullptr)//find more nodes to delete
    {
        node->left = DeleteAVLTree(node->left);
    }

    if(node->right != nullptr) //find more nodes to delete
    {
        node->right = DeleteAVLTree(node->right);
    }


    delete node; //delete node visited
    return nullptr;
}