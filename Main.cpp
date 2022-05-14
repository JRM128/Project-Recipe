#include "Splay.h"
#include "RED_BLACK_TREE.cpp"
#Written by Jacob

int main() {
    Splay s; //Splay Tree Object
    RED_BLACK_TREE rb; //Red-Black Tree Object
    int first = true; //Title line check
    cout << "     Cooking Crew's Project Recipe" << endl << endl;

    //File data variables
    vector<string> row;
    vector<string> titles;
    string line, value = "";

    //Read the dataset file
    ifstream file("Recipes_Project3.csv");
    cout << "     Loading Recipe Information..." << endl << endl;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (first) {
                stringstream str(line);
                while (getline(str, value, ',')) { //Store every title in the file into this vector 
                    titles.push_back(value);
                }
                first = false;
                continue;
            }

            //Reset the row and stringstream for the new row in the file
            row.clear();
            stringstream str(line);

            while (getline(str, value, ',')) { //Store every cell into a string then push the entire row into the vector 
                row.push_back(value);
            }

            //Insert the new node into both trees
            rb.InsertNode(row);
            s.root = s.insert(s.root, row);
        }
    }
    file.close();

    //Program Variables
    int option = 0;
    string recipe = "";
    bool end = false;
    Node* curr;
    node* node1;

    while (!end) { //Until the user ends the program
        //Menu Print
        cout << "1. Search for a recipe." << endl;
        cout << "2. Average time spent searching in both trees." << endl;
        cout << "3. End program." << endl;
        cout << "Enter an option number: ";

        cin >> option;
        switch (option) {
            case 1: //Search for a recipe

                cin.ignore();
                cout << "Recipe Name: ";
                getline(cin, recipe);
                
                //Search for recipe in both trees
                curr = s.search(s.root, recipe);
                node1 = rb.RB_Searchtree(recipe);

                //Check if the recipe inputted exists in the trees
                if (!curr || !node1) {
                    cout << endl << "Recipe is not found within database." << endl << endl;
                    continue;
                }

                //Print recipe information in splay tree but can be changed to using the Red-Black tree if wanted by coder (Both trees contain the same information)
                for (int i = 0; i < curr->values.size(); ++i) {
                    cout << titles[i] << ": ";
                    cout << curr->values[i] << endl;
                }
                cout << endl;
                break;

            case 2: //Print the average time the program has spent searching in both trees

                if (s.count == 0 || rb.count == 0) {
                    cout << endl << "Both trees have not been searched yet." << endl << endl;
                    continue;
                }
                cout << endl;
                cout << "Overall time for each tree:" << endl;
                if (s.times / (double)s.count == 0) {
                    cout << "Splay Tree: Almost zero seconds" << endl;
                }
                else {
                    cout << "Splay Tree: " << s.times / (double)s.count << " seconds" << endl; //Splay Tree time
                }
                if (rb.times / (double)rb.count == 0) {
                    cout << "Red-Black Tree: Almost zero seconds" << endl << endl;
                }
                else {
                    cout << "Red-Black Tree: " << rb.times / (double)rb.count << " seconds" << endl << endl; //Red-Black Tree time
                }
                break;

            case 3: //End the program

                cout << endl;
                cout << "Have a great day!" << endl;
                end = true;
                break;

            default: //For when an option that does not fall in the menu is inputted

                cout << endl;
                cout << "Please enter an available option!" << endl << endl;
                break;

        }
    }
}
