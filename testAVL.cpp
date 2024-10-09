
#include "AVL.h"
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>


void printAVL(AVL<int>& avl)
{
    
    typename BST<int>::Node *root = avl.getRoot();
    if(root == nullptr)
    {
        cout <<"No tree to be printed" <<endl;
    }
    else
    {
        cout << "PreOrder:";
        avl.printPreOrder(root);
        cout << endl << "InOrder:";
        avl.printInOrder(root);
    }
}

//gen a number from [10,60]
int getInputN()
{
    return rand() % 50 + 10;
}

//gen number for avl range (1000, 5000) where bracket represents not including
int getInputInts()
{
    return (rand() % 4000 + 1000) + 1;
}

//gen a file of numbers where the first line is the number of lines
void genInputFile(int n, const std::string& filename) 
{

    std::ofstream file(filename);

    if (file.is_open()) 
    {
        
        file << n << endl;
        for (int i = 0; i < n; i++) 
        {
            file << getInputInts() << endl;
        }
        file.close();
 
    } 
    else 
    {
        cerr << "file open error." << endl;
    }
}

//helper to match assign instructions to call insert
template <typename T>
void  InsertNodeAVL(AVL<T>& avl, T value) 
{
    avl. InsertNodeAVL(value);//call the insert in avl
}

//helper to match assign instructions to call del
template <typename T>
void DeleteNodeAVL(AVL<T>& avl, T value) 
{
    avl.DeleteNodeAVL(value);
}

int main() {

    AVL<int> *avl;

    srand(time(0));
    // declaration of your variables ...
    int n = getInputN(); // n is a non-negative integer that can be read from user or
    string fileName = "AVL_Input.txt";
    // generated randomly by computer
    genInputFile(n, fileName); //generates an input file as explained in part B


    avl = avl->BuildAVLTree(fileName);
    cout << "height of AVL tree is:" << avl->getHeight(avl->getRoot()) << endl << endl << endl;
    printAVL(*avl);

    cout << endl << endl << "Enter a value to insert: ";
    int nodeVal;
    cin >> nodeVal;
    InsertNodeAVL(*avl, nodeVal);
    cout << "height of AVL tree is:" << avl->getHeight(avl->getRoot()) << endl << endl << endl;
    printAVL(*avl);

    cout << endl << endl << "Enter a value to delete: " ;
    int node;
    cin >> node;
    DeleteNodeAVL(*avl, node);
    cout << "height of AVL tree is:" << avl->getHeight(avl->getRoot()) << endl << endl << endl;
    printAVL(*avl);
    cout << endl << endl;

    cout << "deleting tree" << endl << endl;
    avl->DeleteAVLTree();
    printAVL(*avl);
    
    return 0;
};



  