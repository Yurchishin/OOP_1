using namespace std;

#include "TreeNode.h"

class BinTree {
    TreeNode *ROOT;

    void printNode(TreeNode *node, int page);

    TreeNode *findLeast(TreeNode *treePtr);

    void printNode(TreeNode *node);

public:
    BinTree();

    BinTree(string path);//?explicit

    ~BinTree();

    void initBinTree(string path);

    void addTreeNode(TreeNode *node);

    bool removeTreeNode(string eng);

    void printBinTree();

    void printBinTree(int page);

    TreeNode *findBinTree(string eng);
};