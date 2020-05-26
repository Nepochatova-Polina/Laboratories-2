#include <iostream>
#include "cmath"
#include "stack"
#include "vector"
using namespace std;
struct tree {
    int x;
    tree *left, *right, *parent;
};

struct Node {
    char x;
    Node *left, *right;
};

tree *exchange(tree *root);

tree *Add(tree *root, int element);

void Show(tree *root);

int HeightOfTree(tree *root);

tree *FindNode(tree *root, int max);

tree *Delete(tree *root);

tree *getMaxNode(tree *root);

Node *StackFunk(string task);

Node *newNode(char x);

bool isOperator(char x);

char diff(char left_element, char right_element, char op);

int main() {
    int num, element;
    cout << "Enter number of elements" << endl;
    cin >> num;
    tree *root = nullptr;
    for (int i = 0; i < num; i++) {
        cout << "Enter element" << endl;
        cin >> element;
        root = Add(root, element);
    }
    root = exchange(root);
    string task;
    cout << "Enter your task in Postfix form:" << endl;
    getline(cin, task);
    Node *Head = nullptr;
    Node *r = StackFunk(task);
}

tree *Add(tree *root, int element) {
    if (root == nullptr) {
        root = new tree;
        root->x = element;
        root->right = nullptr;
        root->left = nullptr;
        root->parent = root;
        return root;
    } else if (element < root->x)
        root->left = Add(root->left, element);
    else if (element > root->x)
        root->right = Add(root->right, element);
    return root;
}

// Дано покажчик на корінь бінарного дерева. Для всіх вершин дерева поміняти місцями їх ліві і праві дочірні вершини.
tree *exchange(tree *root) {
    if (root) {
        exchange(root->left);
        exchange(root->right);
        swap(root->left, root->right);
    }
    return root;
}

// 2 Дано бінарне дерево пошуку. Знайти його висоту h.
// Серед всіх вершин на рівні [h/2] видалити всі вершини, у яких висота лівого піддерева та висота правого піддерева однакові.
int HeightOfTree(tree *root) {
    int l, r;
    if (root->left != nullptr) {
        l = HeightOfTree(root->left);
    } else
        l = -1;
    if (root->right != nullptr) {
        r = HeightOfTree(root->right);
    } else
        r = -1;
    int max = l > r ? l : r;
    return max + 1;
}

tree *FindNode(tree *root, int max) {
    int i = 0;
    if (root && i < max - 1 / 2) {
        i++;
        root = FindNode(root->left, max);
    } else if (root == nullptr && i < max) {
        i++;
        root = FindNode(root->right, max);
    }
    if (HeightOfTree(root->left) == HeightOfTree(root->right)) {
        Delete(root->parent);
    }
}

tree *Delete(tree *root) {
    if (root->left && root->right) {
        tree *localMax = getMaxNode(root->left);
        root->x = localMax->x;
        Delete(localMax);
    } else if (root->left) {
        if (root == root->parent->left) {
            root->parent->left = root->left;
        } else {
            root->parent->right = root->left;
        }
    } else if (root->right) {
        if (root == root->parent->right) {
            root->parent->right = root->right;
        } else {
            root->parent->left = root->right;
        }
    } else {
        if (root == root->parent->left) {
            root->parent->left = nullptr;
        } else {
            root->parent->right = nullptr;
        }
    }
    free(root);
    return root;
}

tree *fun(tree *root, int max) {
    if (max / 2 <= 0) {
        return root;
    }
    int i = 0;
    if (root && i < max / 2)
        i++;
    fun(root->left, max);
    fun(root->right, max);
    return root;
}

tree *getMaxNode(tree *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}


//3 Дано вираз, у якому присутні змінні, логічні константи «0» та «1», а також дужки.
// Допустимі операції – логічне «і» (&), логічне «або» (|), логічне заперечення (-).
// Представити вираз у вигляді дерева. Спростити вираз. Вивести на екран таблицю значень виразу (перебрати усі кортежі змінних)
Node *StackFunk(string task) {
    stack<Node *> NumberStack;
    Node *dad, *child1, *child2;
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

bool isOperator(char x) {
    return x == '&' || x == '|' || x == '-';
}

Node *newNode(char x) {
    Node *temp = new Node;
    temp->left = temp->right = nullptr;
    temp->x = x;
    return temp;

}

bool isVariable(char x) {
    return 'a' <= x <= 'z';

}

char Show(Node *node) {
    char right_element, left_element, op;

    if (isOperator(node->left->x)) {
        left_element = Show(node->left);
    }
    if (isOperator(node->right->x)) {
        right_element = Show(node->right);
    }
    op = node->x;
    left_element = node->left->x;
    right_element = node->right->x;
    return diff(left_element, right_element, op);
}


char diff(char left_element, char right_element, char op) {

    switch (op) {
        case '&':
            if (!isVariable(left_element) && isVariable(right_element) ||
                !isVariable(right_element) && isVariable(left_element)) {
                left_element = left_element & right_element;
            } else if (!isVariable(left_element) && !isVariable(right_element)) {
                left_element = 0;
            }
            break;
        case '-':
            if (!isVariable(left_element) && isVariable(right_element) ||
                !isVariable(right_element) && isVariable(left_element)) {
                left_element = 1;
            } else if (!isVariable(left_element) && !isVariable(right_element)) {
                left_element = 0;
            }
            break;
        case '|':
            if (!isVariable(left_element) && isVariable(right_element)) {
                return left_element | right_element;
            } else if (!isVariable(right_element) && isVariable(left_element)) {
                if (right_element == '0') {
                    left_element = 0;
                } else {
                    left_element = 1;
                }
            } else if (!isVariable(left_element) && !isVariable(right_element)) {
                left_element = left_element | right_element;
            }
            break;
    }
    return left_element;
}

// 4 Написати функцію, яка перевіряє ациклічність орієнтованого графа
void cycle(int start, vector<int> & color, const vector <vector <int> >& g){
    bool found;
    color[start] = 1;
    for (auto u : g[start])
        if (color[u] == 0)
            cycle(u, color, g);
        else if (color[start] == 1)
            found = true;
    color[start] = 2;
}
