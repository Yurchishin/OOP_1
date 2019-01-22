#include <iostream>
#include "include/BinTree.h"

using namespace std;

/*
 *Project Structure (change "../lab4.csv" on "lab4.csv" in "main.cpp", or build a project in my):
     * lab4 {
     *     CMakeLists.txt,
     *     main.cpp,
     *     lab4.csv,
     *     include {
     *         BinTree.h,
     *         TreeNode.h
     *     },
     *     src {
     *         BinTree.cpp,
     *         TreeNode.cpp
     *     }
     * }
*/

void dialog(BinTree tree);

int main() {
    BinTree tree("../lab4.csv");
    dialog(tree);
    return 0;
}

void dialog(BinTree tree) {
    cout << "Enter method (print, add, findWord, findPage, remove, exit):" << endl;
    string input;
    cin >> input;
    if (input == "print") {
        tree.printBinTree();
        dialog(tree);
    } else if (input == "add") {
        string input_eng, input_ital;
        int input_page;

        cout << "Enter english word:" << endl;
        cin >> input_eng;

        cout << "Enter italian word:" << endl;
        cin >> input_ital;
        cout << "Enter page(number):" << endl;
        cin >> input_page;//error if not number

        TreeNode *node = new TreeNode(input_eng, input_ital, input_page);
        tree.addTreeNode(node);

        dialog(tree);
    } else if (input == "findWord") {
        string input_eng;

        cout << "Enter english word:" << endl;
        cin >> input_eng;

        TreeNode *node = tree.findBinTree(input_eng);

        if (node != nullptr) {
            node->print();
        } else {
            cout << "Word not found." << endl;
            dialog(tree);
        }

        dialog(tree);
    } else if (input == "findPage") {
        int input_page;

        cout << "Enter page(number):" << endl;
        cin >> input_page;

        tree.printBinTree(input_page);//error if not number

        dialog(tree);
    } else if (input == "remove") {
        string input_eng;

        cout << "Enter english word:" << endl;
        cin >> input_eng;

        TreeNode *node = tree.findBinTree(input_eng);

        if (node != nullptr) {
            tree.removeTreeNode(input_eng);
            delete node;
        } else {
            cout << "Word not found." << endl;
            delete node;
        }

        dialog(tree);
    } else if (input == "exit") {
        cout << "Exit program." << endl;
        return;
    } else {
        cout << "ERROR input." << endl;
        dialog(tree);
    }
}
