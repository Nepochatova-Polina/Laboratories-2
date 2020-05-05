#ifndef LAB5_TREE_H
#define LAB5_TREE_H

#include "string"

using namespace std;

struct tree {
    string english;
    string russian;
    int amount;
    tree *left, *right;
};

struct Node {
    tree *x;
    Node *Next, *Prev;
};

class List {

public:
    Node *Head{}, *Tail{};
    int count;

    List();

    ~List();

    void ShowFromEnd() const;

    void ShowFromBeg() const ;

    void Add(tree *x, List listA);

    void Del(int x);
};


class Tree {

public:
    static tree *newNode(tree *node, Node *ptr);

    static int findMax(Node *Head, int count);

    static void treeprint(tree *node);

    static void writeInBin(Node *Head, int count, List listA);

    static bool checkWord(string word);

};


#endif //LAB5_TREE_H

