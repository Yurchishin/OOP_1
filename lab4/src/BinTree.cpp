#include <utility>

#include "../include/BinTree.h"
#include <iostream>
#include <fstream>

using namespace std;

void deleteNodeRec(TreeNode *node);

BinTree::BinTree() {
    ROOT = nullptr;
}

BinTree::BinTree(string path) {
    ROOT = nullptr;
    initBinTree(move(path));
}

BinTree::~BinTree() {
    deleteNodeRec(this->ROOT);
}

void BinTree::initBinTree(string path) {
    ifstream csv(path);

    if (!csv) {
        cout << "ERROR opening file." << endl;
        exit(1);
    }

    string eng, ital;
    int page;

    while (true) {
        getline(csv, eng, ';');
        if (csv.eof()) break;
        getline(csv, ital, ';');

        csv >> page;

        addTreeNode(new TreeNode(eng, ital, page));
        getline(csv, eng);
    }

    csv.close();
}

void BinTree::addTreeNode(TreeNode *node) {
    if (ROOT == nullptr) {
        ROOT = node;
        return;
    }

    TreeNode *NODE = ROOT, *PARENT;

    while (NODE != nullptr) {
        PARENT = NODE;

        if (node->getEngWord() < NODE->getEngWord()) {
            NODE = NODE->getLeft();
            if (NODE == nullptr) PARENT->setLeft(node);
        } else if (node->getEngWord() > NODE->getEngWord()) {
            NODE = NODE->getRight();
            if (NODE == nullptr) PARENT->setRight(node);
        } else {
            NODE->setItalWord(node->getItaWord());
            NODE->setPage(node->getPage());
            break;
        }
    }
}

TreeNode *BinTree::findBinTree(string eng) {
    TreeNode *NODE = ROOT;

    if (NODE == nullptr) return nullptr;

    while (NODE != nullptr) {
        if (eng == NODE->getEngWord()) return NODE;
        else if (eng < NODE->getEngWord()) NODE = NODE->getLeft();
        else NODE = NODE->getRight();
    }

    return nullptr;
}

void BinTree::printBinTree() {
    printNode(ROOT);
}

void BinTree::printBinTree(int page) {
    printNode(ROOT, page);
}

void BinTree::printNode(TreeNode *node) {
    if (node != nullptr) {
        printNode(node->getLeft());
        node->print();
        printNode(node->getRight());
    }
}

void BinTree::printNode(TreeNode *node, int page) {
    if (node != nullptr) {
        printNode(node->getLeft(), page);

        if (node->getPage() == page) node->print();

        printNode(node->getRight(), page);
    }
}

bool BinTree::removeTreeNode(string eng) {
    if (ROOT == nullptr) return false;

    TreeNode *NODE = ROOT, *PARENT = ROOT;

    while (eng != NODE->getEngWord()) {
        PARENT = NODE;

        if (eng < NODE->getEngWord()) NODE = NODE->getLeft();
        else NODE = NODE->getRight();
        if (NODE == nullptr) return false;
    }

    if (NODE->getLeft() == nullptr && NODE->getRight() == nullptr) {

        if (NODE == ROOT) ROOT = nullptr;
        else if (PARENT->getLeft() == NODE) PARENT->setLeft(nullptr);
        else PARENT->setRight(nullptr);

        delete NODE;
    } else if (NODE->getLeft() == nullptr) {
        TreeNode *tmp = NODE;

        if (NODE == PARENT->getRight()) PARENT->setRight(NODE->getRight());
        else PARENT->setLeft(NODE->getRight());

        delete tmp;
    } else if (NODE->getRight() == nullptr) {
        TreeNode *tmp = NODE;

        if (NODE == PARENT->getRight()) PARENT->setRight(NODE->getLeft());
        else PARENT->setLeft(NODE->getLeft());

        delete tmp;
    } else {
        TreeNode *tmp = findLeast(NODE->getRight());
        string tmpEng = tmp->getEngWord();
        NODE->setItalWord(tmp->getItaWord());
        NODE->setPage(tmp->getPage());
        removeTreeNode(tmpEng);
        NODE->setEngWord(tmpEng);
    }

    return true;
}

TreeNode *BinTree::findLeast(TreeNode *treePtr) {
    TreeNode *NODE = treePtr;
    while (NODE->getLeft() != nullptr) NODE = NODE->getLeft();
    return NODE;
}

void deleteNodeRec(TreeNode *node) {
    if (node != nullptr) {
        deleteNodeRec(node->getLeft());
        deleteNodeRec(node->getRight());
        delete node;
    }
}