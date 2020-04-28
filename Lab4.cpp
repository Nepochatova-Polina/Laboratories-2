#include <iostream>
#include "string"
#include "stack"

using namespace std;
struct tree {
    char element;
    tree *left, *right;
};

tree *StackFunk(string task);

tree *newNode(char x);

bool isOperator(char x);

char diff(char left_element, char right_element, char op);

char Show(tree *node);

void InfixTask(tree *node);

int main() {
    string task;
    cout << "Enter your task in Postfix form:" << endl;
    getline(cin, task);
    tree *r = StackFunk(task);
    InfixTask(r);
    char x = Show(r);
    cout << endl;
    cout << x;
}

tree *StackFunk(string task) {
    stack < tree * > NumberStack;
    tree *dad, *child1, *child2;
    for (int i = 0; i <= task.length() - 1; i++) {
        if (!isOperator(task[i])) {
            dad = newNode(task[i]);
            NumberStack.push(dad);
        } else if (isOperator(task[i])) {
            dad = newNode(task[i]);
            child1 = NumberStack.top();
            NumberStack.pop();
            child2 = NumberStack.top();
            NumberStack.pop();

            dad->right = child1;
            dad->left = child2;
            NumberStack.push(dad);
        }

    }
    dad = NumberStack.top();
    NumberStack.pop();

    return dad;
}

tree *newNode(char x) {
    tree *temp = new tree;
    temp->left = temp->right = nullptr;
    temp->element = x;
    return temp;

}

char Show(tree *node) {
    char right_element, left_element, op;

    if (isOperator(node->left->element)) {
        left_element = Show(node->left);
    }
    if (isOperator(node->right->element)) {
        right_element = Show(node->right);
    }

    op = node->element;
    left_element = node->left->element;
    right_element = node->right->element;
    return diff(left_element, right_element, op);
}


bool isOperator(char x) {
    return x == '*' || x == '+' || x == '-';
}

char diff(char left_element, char right_element, char op) {

    switch (op) {
        case '+':
            if (left_element != 'x' && right_element == 'x' || right_element != 'x' && left_element == 'x') {
                left_element = 1;
            } else if (left_element != 'x' && right_element != 'x') {
                left_element = 0;
            }
            break;
        case '-':
            if (left_element != 'x' && right_element == 'x' || right_element != 'x' && left_element == 'x') {
                left_element = 1;
            } else if (left_element != 'x' && right_element != 'x') {
                left_element = 0;
            }
            break;
        case '*':
            if (left_element != 'x' && right_element == 'x') {

            } else if (right_element != 'x' && left_element == 'x') {
                left_element = right_element;
            } else if (left_element != 'x' && right_element != 'x') {
                left_element = 0;
            }
            break;
    }
    return left_element;
}

void Delete(tree *temp) {

    if (temp != nullptr) {
        Delete(temp->left);
        Delete(temp->right);
        delete temp;
    }
}


void InfixTask(tree *node) {
    if (node) {
        InfixTask(node->left);
        cout << node->element;
        InfixTask(node->right);
    }
}
