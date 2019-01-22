#include "../include/TreeNode.h"
#include <iostream>

using namespace std;

TreeNode::TreeNode() {
    LEFT = nullptr;
    RIGHT = nullptr;
    ENG_WORD = "";
    ITAL_WORD = "";
    PAGE = 0;
}

TreeNode::TreeNode(string eng, string ital, int page) {
    LEFT = nullptr;
    RIGHT = nullptr;
    ENG_WORD = move(eng);
    ITAL_WORD = move(ital);
    PAGE = page;
}

void TreeNode::setPage(int page) {
    PAGE = page;
}

void TreeNode::setEngWord(string eng) {
    ENG_WORD = move(eng);
}

void TreeNode::setItalWord(string ital) {
    ITAL_WORD = move(ital);
}

void TreeNode::setLeft(TreeNode *node) {
    LEFT = node;
}

void TreeNode::setRight(TreeNode *node) {
    RIGHT = node;
}

int TreeNode::getPage() const {
    return PAGE;
}

string TreeNode::getEngWord() const {
    return ENG_WORD;
}

string TreeNode::getItaWord() const {
    return ITAL_WORD;
}

TreeNode* TreeNode::getLeft() const {
    return LEFT;
}

TreeNode* TreeNode::getRight() const {
    return RIGHT;
}

void TreeNode::print() {
    cout << "English: " << ENG_WORD;
    cout << "\t\tItalian : " << ITAL_WORD;
    cout << "\t\tPage: " << PAGE << endl;
}