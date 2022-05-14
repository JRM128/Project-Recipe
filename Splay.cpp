#include "Splay.h"
#Written by Jacob

//Insertion Function (Time Complexity: Worst = O(n) / Average = O(log(n))
Node* Splay::insert(Node* root, vector<string> values) {//New node and its parent
    Node* temp = root;
    Node* Parent = nullptr;

    //Loop to find where the new node's values will go into the tree, while following BST rules
    while (temp) {
        Parent = temp;
        if (temp->values[0] > values[0]) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }

    //Create the new node and set its parent
    temp = new Node(values);
    temp->parent = Parent;

    //Test if the new node is the root or to make sure the Parent points to the correct node for its left or right node
    if (Parent == nullptr) {
        root = temp;
    }
    else if (Parent->values[0] > temp->values[0]) {
        Parent->left = temp;
    }
    else {
        Parent->right = temp;
    }

    //Splay the tree so the new node becomes the root
    splay(temp);
    return temp;
}

//Search Function (Time Complexity: Worst = O(n) / Average = O(log(n))
Node* Splay::search(Node* root, string value) {
    Node* temp = root;
    clock_t start = clock();

    //Loop through the tree until the current node's value[1] equals the wanted value
    while(temp) {
        if (value.compare(temp->values[0]) < 0) {
            temp = temp->left;
        }
        else if(value.compare(temp->values[0]) > 0) {
            temp = temp->right;
        }
        else {
            //Once the node is found, splay the tree so the node becomes the root
            splay(temp);
            
            //Calculate time of function
            clock_t end = clock();
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            times += cpu_time_used;
            count++;

            return temp;
        }
    }

    return nullptr; //If the node does not exist
}

void Splay::preOrder(Node* root){
    if (root != nullptr){
        cout << root->values[0] << endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}
