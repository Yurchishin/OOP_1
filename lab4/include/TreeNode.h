using namespace std;

#include <string>

class TreeNode {
    TreeNode *RIGHT;
    TreeNode *LEFT;
    string ENG_WORD;
    string ITAL_WORD;
    int PAGE;
public:
    TreeNode();

    TreeNode(string eng, string ital, int page);

    ~TreeNode() = default;

    void setLeft(TreeNode *node);

    void setRight(TreeNode *node);

    void setEngWord(string eng);

    void setItalWord(string ital);

    void setPage(int page);

    TreeNode *getLeft() const;

    TreeNode *getRight() const;

    string getEngWord() const;

    string getItaWord() const;

    int getPage() const;

    void print();
};