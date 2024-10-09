// BST.h file
// Descriptions: This class is a template class for the Binary search tree
// Author: Grantley
// Creation date: June 15, 2023


#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class BST
{
    
    public:
        class Node
        {
            public:
                T data;
                Node* left;
                Node* right;
                int height;

                Node(T d)
                {
                    data = d;
                    left = nullptr;
                    right = nullptr;
                    height = 1;
                }


        };

        

        BST();

        BST(T d);
        
        Node* getRoot() const;

        void insertOLD(T d);

        int getHeight(const Node* root) const;

        // O(n)
        // pre-order print
        void printPreOrder(const Node* root)const;

        

        void insert(T d);
        
        // O(n)
        //prints in in-order 
        void printInOrder(const Node* root)const;

        
        Node* root;
        Node* insertR(Node* node, T d);
        
};

template <typename T>
// gives height of BST
int BST<T>::getHeight(const Node* root) const
{
    if(root == nullptr || root->left == nullptr && root->right == nullptr)
    {
        return 0;
    }

    int left = getHeight(root->left);
    
    int right = getHeight(root->right);

    if(left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }

    return -1;
}

template <typename T>
// O(n)
// pre-order print
void BST<T>::printPreOrder(const Node* root)const
{
    if(root == nullptr)
    {
        return;
    }

    cout << root->data<< " " ;
    printPreOrder(root->left);
    printPreOrder(root->right);
    // cout << endl;
}

template <typename T>
// O(n)
// In-order print
void BST<T>::printInOrder(const Node* root) const
{
    if(root == nullptr)
    {
        return; //return stack
    }
    
    printInOrder(root->left);
    cout << root->data<< " " ;
    printInOrder(root->right);
    // cout << endl;
}

template <typename T>
// return root.
typename BST<T>::Node* BST<T>::getRoot() const
{
    return root;
}

template <typename T>
// default cons
BST<T>::BST()
{
    root = nullptr;
}

template <typename T>
// const first node
BST<T>::BST(T d)
{
    root = new Node(d);

}

template <typename T>
// insert in bst
void BST<T>::insertOLD(T d)
{
    Node* curr;
    Node* node;
    if(root == nullptr)
    {
        root = new Node(d);
    }
    else
    {
        node = new Node(d);
        curr = root; 

        bool inserted = false;

        while(!inserted)
        {
            if(curr->data >= d)
            {
                if(curr->left == nullptr)
                {
                    curr->left = node;
                    inserted = true;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if(curr->right == nullptr)
                {
                    curr->right = node;
                    inserted = true;
                }
                else
                {
                    curr = curr->right;
                }
            }
            
        }    
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::insertR(Node* node, T d)
{
    // Base case: If the node is null, allocate a new node
    if(node == nullptr) 
    {
        return new Node(d);
    }

    // If data is less than the node's data, insert in the left subtree
    if(d < node->data)
    {
        node->left = insertR(node->left, d);
    }
    // If data is greater than the node's data, insert in the right subtree
    else if(d > node->data)
    {
        node->right = insertR(node->right, d);
    }
    // If data is equal to the node's data, don't insert it (assuming BST doesn't allow duplicates)

    return node;
}

template <typename T>
void BST<T>::insert(T d)
{
    root = insertR(root, d);
}


