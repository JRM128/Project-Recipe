#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#Written by Stuti

using namespace std;
using std::istringstream;
using std::ifstream; using std::ostringstream;
using std::cout; using std::cerr;
using std::endl; using std::string;

struct node {
    string  name;
    int     id{};
    string  CookTime;
    string  PrepTime;
    string  TotalTime;
    float   Calories;
    float   Fat;
    float   Cholesterol;
    float   Sodium;
    float   Carbohydrate;
    float   Sugar;
    float   Protein;
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
    bool    color;
};

class RED_BLACK_TREE {
    int count1;
    node* root;

public:
    RED_BLACK_TREE() : root(NULL), count1(0) {}

    node* GetRoot() { return root; }

    double times = 0;
    int count = 0;

    // Create a node with recipe details

    void InsertNode(vector<string> rows) {
        if (root == NULL) {
            root = new node();
            root->color = true;
            root->parent = NULL;
            root->name = rows[0]; // reci_name
            root->id = stoi(rows[1]); // id
            root->CookTime = rows[2]; // CookTime
            root->PrepTime = rows[3]; // PrepTime
            root->TotalTime = rows[4]; //TotalTime
            root->Calories = stof(rows[5]); // Calories
            root->Fat = stof(rows[6]); //Fat
            root->Cholesterol = stof(rows[7]); //Cholesterol
            root->Sodium = stof(rows[8]); // Sodium
            root->Carbohydrate = stof(rows[9]); //Carbohydrate
            root->Sugar = stof(rows[10]); // Sugar
            root->Protein = stof(rows[11]); //Protein
            count1++;
        }
        else {
            auto linker = GetRoot();
            node* newnode = new node();
            newnode->name = rows[0];
            newnode->id = stoi(rows[1]);
            newnode->CookTime = rows[2];
            newnode->PrepTime = rows[3];
            newnode->TotalTime = rows[4];
            newnode->Calories = stof(rows[5]);
            newnode->Fat = stof(rows[6]);
            newnode->Cholesterol = stof(rows[7]);
            newnode->Sodium = stof(rows[8]);
            newnode->Carbohydrate = stof(rows[9]);
            newnode->Sugar = stof(rows[10]);
            newnode->Protein = stof(rows[11]);
            while (linker != NULL) {
                if (((linker->name).compare(rows[0])) > 0) {
                    if (linker->left == NULL) {
                        linker->left = newnode;
                        newnode->color = false;
                        newnode->parent = linker;
                        count1++;
                        break;
                    }
                    else { linker = linker->left; }
                }
                else {
                    if (linker->right == NULL) {
                        linker->right = newnode;
                        newnode->color = false;
                        newnode->parent = linker;
                        count1++;
                        break;
                    }
                    else { linker = linker->right; }
                }
            }
            RB_rearrange_insert(newnode);
        }
    }

    // Perform respective rotations to maintain a red-black tree
    void RB_rearrange_insert(node* nn) {
        while (nn->parent->color == false) {
            auto grandparent = nn->parent->parent;
            auto uncle = GetRoot();
            if (nn->parent == grandparent->left) {
                if (grandparent->right) { uncle = grandparent->right; }
                if (uncle->color == false) {
                    nn->parent->color = true;
                    uncle->color = true;
                    grandparent->color = false;
                    if ((grandparent->name).compare(root->name) != 0) { nn = grandparent; }
                    else { break; }
                }
                else if (nn == grandparent->left->right) {
                    RB_LR(nn->parent);
                }
                else {
                    nn->parent->color = true;
                    grandparent->color = false;
                    RB_RR(grandparent);
                    if ((grandparent->name).compare(root->name) != 0) { nn = grandparent; }
                    else { break; }
                }
            }
            else {
                if (grandparent->left) { uncle = grandparent->left; }
                if (uncle->color == false) {
                    nn->parent->color = true;
                    uncle->color = false;
                    grandparent->color = false;
                    if ((grandparent->name).compare(root->name) != 0) { nn = grandparent; }
                    else { break; }
                }
                else if (nn == grandparent->right->left) {
                    RB_RR(nn->parent);
                }
                else {
                    nn->parent->color = true;
                    grandparent->color = false;
                    RB_LR(grandparent);
                    if ((grandparent->name).compare(root->name) != 0) { nn = grandparent; }
                    else { break; }
                }
            }
        }
        root->color = true;
    }

    // Search a recipe by name
    node* RB_Searchtree(string stuff) {
        auto temp = GetRoot();
        clock_t start = clock();
        if (temp == NULL) { return NULL; }
        while (temp) {
            string str = temp->name;
            if (stuff.compare(str) == 0) {
                cout << "\n";
                clock_t end = clock();
                double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                times += cpu_time_used;
                count++;
                return temp;
            }
            else if (stuff.compare(str) < 0) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return NULL;
    }

    //Perform LR rotation
    void RB_LR(node* in_node1) {
        node* new_node = new node();
        if (in_node1->right->left) { new_node->right = in_node1->right->left; }
        new_node->left = in_node1->left;
        new_node->name = in_node1->name;
        new_node->id = in_node1->id;
        new_node->CookTime = in_node1->CookTime;
        new_node->PrepTime = in_node1->PrepTime;
        new_node->TotalTime = in_node1->TotalTime;
        new_node->Calories = in_node1->Calories;
        new_node->Fat = in_node1->Fat;
        new_node->Cholesterol = in_node1->Cholesterol;
        new_node->Sodium = in_node1->Sodium;
        new_node->Carbohydrate = in_node1->Carbohydrate;
        new_node->Sugar = in_node1->Sugar;
        new_node->Protein = in_node1->Protein;
        new_node->color = in_node1->color;
        in_node1->name = in_node1->right->name;
        in_node1->id = in_node1->right->id;
        in_node1->CookTime = in_node1->right->CookTime;
        in_node1->PrepTime = in_node1->right->PrepTime;
        in_node1->TotalTime = in_node1->right->TotalTime;
        in_node1->Calories = in_node1->right->Calories;
        in_node1->Fat = in_node1->right->Fat;
        in_node1->Cholesterol = in_node1->right->Cholesterol;
        in_node1->Sodium = in_node1->right->Sodium;
        in_node1->Carbohydrate = in_node1->right->Carbohydrate;
        in_node1->Sugar = in_node1->right->Sugar;
        in_node1->Protein = in_node1->right->Protein;
        in_node1->color = in_node1->right->color;
        in_node1->left = new_node;
        if (new_node->left) { new_node->left->parent = new_node; }
        if (new_node->right) { new_node->right->parent = new_node; }
        new_node->parent = in_node1;

        if (in_node1->right->right) { in_node1->right = in_node1->right->right; }
        else { in_node1->right = NULL; }

        if (in_node1->right) { in_node1->right->parent = in_node1; }
    }

    // Perform RR rotation 
    void RB_RR(node* in_node2) {
        node* new_node1 = new node();
        if (in_node2->left->right) { new_node1->left = in_node2->left->right; }
        new_node1->right = in_node2->right;
        new_node1->name = in_node2->name;
        new_node1->id = in_node2->id;
        new_node1->color = in_node2->color;
        new_node1->CookTime = in_node2->CookTime;
        new_node1->PrepTime = in_node2->PrepTime;
        new_node1->TotalTime = in_node2->TotalTime;
        new_node1->Calories = in_node2->Calories;
        new_node1->Fat = in_node2->Fat;
        new_node1->Cholesterol = in_node2->Cholesterol;
        new_node1->Sodium = in_node2->Sodium;
        new_node1->Carbohydrate = in_node2->Carbohydrate;
        new_node1->Sugar = in_node2->Sugar;
        new_node1->Protein = in_node2->Protein;

        in_node2->name = in_node2->left->name;
        in_node2->id = in_node2->left->id;
        in_node2->color = in_node2->left->color;
        in_node2->CookTime = in_node2->left->CookTime;
        in_node2->PrepTime = in_node2->left->PrepTime;
        in_node2->TotalTime = in_node2->left->TotalTime;
        in_node2->Calories = in_node2->left->Calories;
        in_node2->Fat = in_node2->left->Fat;
        in_node2->Cholesterol = in_node2->left->Cholesterol;
        in_node2->Sodium = in_node2->left->Sodium;
        in_node2->Carbohydrate = in_node2->left->Carbohydrate;
        in_node2->Sugar = in_node2->left->Sugar;
        in_node2->Protein = in_node2->left->Protein;

        in_node2->right = new_node1;
        if (new_node1->left) { new_node1->left->parent = new_node1; }
        if (new_node1->right) { new_node1->right->parent = new_node1; }
        new_node1->parent = in_node2;

        if (in_node2->left->left) { in_node2->left = in_node2->left->left; }
        else { in_node2->left = NULL; }

        if (in_node2->left) { in_node2->left->parent = in_node2; }
    }

    void Preorder_Traverse(node* temp) {
        if (!temp) { return; }
        cout << "--> " << temp->name << "< temp id" << temp->id << temp->color << ">";
        Preorder_Traverse(temp->left);
        Preorder_Traverse(temp->right);
    }

};
