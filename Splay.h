#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

//Node class
struct Node {
	vector<string> values; //Containes every recipes' information
	Node* left, * right, * parent; //Every other node connected to the current node
	Node() : values(0), left(nullptr), right(nullptr), parent(nullptr) {}
	Node(vector<string> theValues) : values(theValues), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Splay {

    //General Rotation Functions
    void rotateLeft(Node* node) {
        Node* parent = node->right;
        node->right = parent->left;
        if (parent->left) {
            parent->left->parent = node;
        }
        parent->parent = node->parent;
        if (!parent->parent) {
            this->root = parent;
        }
        else if (node->parent->right == node) {
            node->parent->right = parent;
        }
        else {
            node->parent->left = parent;
        }
        parent->left = node;
        node->parent = parent;
    }

    void rotateRight(Node* node) {
        Node* parent = node->left;
        node->left = parent->right;
        if (parent->right) {
            parent->right->parent = node;
        }
        parent->parent = node->parent;
        if (!parent->parent) {
            this->root = parent;
        }
        else if (node->parent->left == node) {
            node->parent->left = parent;
        }
        else {
            node->parent->right = parent;
        }
        parent->right = node;
        node->parent = parent;
    }

    //Splay Function
    void splay(Node* node) {
        //Rotate nodes until the current node is the root
        while (node->parent) {
            //Zig Rotations
            if (node->parent->parent == nullptr) {
                //Zig Rotation
                if (node->parent->left == node) {
                    rotateRight(node->parent);
                }
                //Zag Rotation
                else {
                    rotateLeft(node->parent);
                }
            }
            //Zig Zig Rotation
            else if (node->parent->left == node && node->parent->parent->left == node->parent) {
                rotateRight(node->parent->parent);
                rotateRight(node->parent);
            }
            //Zag Zag Rotation
            else if (node->parent->right == node && node->parent->parent->right == node->parent) {
                rotateLeft(node->parent->parent);
                rotateLeft(node->parent);
            }
            //Zig Zag Rotation
            else if (node->parent->right == node && node->parent->parent->left == node->parent) {
                rotateLeft(node->parent);
                rotateRight(node->parent);
            }
            //Zag Zig Rotation
            else {
                rotateRight(node->parent);
                rotateLeft(node->parent);
            }
        }
    }

    public:
        Node* root;
        double times = 0;
        int count = 0;
        Node* insert(Node* root, vector<string> values);
        Node* search(Node* root, string value);
        void preOrder(Node* root);
        Splay() : root(nullptr) {}

};