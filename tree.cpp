

#include "tree.h"
#include <iostream>
#include "string"
#include <cstdlib>

using namespace std;

tree *Tree::newNode(tree *node, Node *ptr) {
    if (node == nullptr) {
        tree *node = new tree;
        node->english = ptr->x->english;
        node->russian = ptr->x->russian;
        node->amount = ptr->x->amount++;
        node->left = node->right = nullptr;
    } else if ((ptr->x->english == node->english))
        node->amount++;
    else if (ptr->x->english > node->english)
        node->left = newNode(node->left, ptr);
    else
        node->right = newNode(node->right, ptr);
    return node;
}


int Tree::findMax(Node *Head, int count) {
    int max = 0, index;
    Node *tmp = Head;
    for (int i = 0; i <= count; i++) {
        if (tmp->x->amount > max) {
            max = tmp->x->amount;
            index = i;
            tmp = tmp->Next;
        }
    }
    return index;
}


void Tree::treeprint(tree *node) {
    if (node != nullptr) {
        treeprint(node->left);
        cout << node->english << " " << node->russian;
        treeprint(node->right);
    }
}


void Tree::writeInBin(Node *Head, int count, List listA) {
    int index;
    tree *root = new tree;
    root = nullptr;
    Node *ptr = Head;
    while (ptr ->Next != nullptr) {
        index = Tree::findMax(Head, count);
        for (int i = 0; i < index; i++) {
            ptr = ptr->Next;
        }
        root = Tree::newNode(root, ptr);
        listA.Del(index);
    }

}

bool Tree::checkWord(string word) {
    for (char i : word) {
        if (isdigit(i))
            return false;
    }
    return true;
}

