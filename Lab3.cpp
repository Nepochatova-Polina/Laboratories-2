#include "Lab3.h"
#include "functions.h"
#include <iostream>
#include "fstream"
#include "sstream"
#include "vector"
#include "queue"

#define MAX_TREE_HT 100


struct List {
    int index;
    List *Next;
};
List *head(nullptr), *last(nullptr);

const int size = 100;
int firstMatrix[size][size];
int secondMatrix[size][size];
int newMatrix[size][size];

using namespace std;
void functions::writeFunction() {
    for (auto &i : firstMatrix) {
        for (int j : i) {
            cout << j;
        }
        cout << endl;
    }
}

void functions::additionMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
        }
    }
    for (auto &i : newMatrix) {
        for (int j : i) {
            cout << j;
        }
        cout << endl;
    }
}

void functions::addToList(int x) {
    auto *temp = new List;
    temp->Next = nullptr;
    temp->index = x;
    if (head != nullptr) {
        last->Next = temp;
        last = temp;
    } else {
        head = last = temp;
    }
}

void functions::multiMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = 0;
            for (int k = 0; k <= size + 1; k++) {
                newMatrix[i][j] += (firstMatrix[i][k] * secondMatrix[k][j]);

            }
        }
    }

    for (auto &i : newMatrix) {
        for (int j : i) {
            cout << j;
        }
        cout << endl;
    }
}


void functions::readFile() {
    ifstream f("Matrix.txt");
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");
    while (!f.eof()) {
        for (auto &i : firstMatrix) {
            for (int &j : i)
                f >> j;
        }
        f.close();
    }
    ifstream file("Matrix2.txt");
    if (!file.is_open())
        perror("error while opening file");

    if (file.bad())
        perror("error while reading file");
    while (!file.eof()) {
        for (auto &i : firstMatrix) {
            for (int &j : i)
                file >> j;
        }
        file.close();
        functions::writeFunction();
    }
}

void functions::SaveMatrix() {
    int compactMatrix[3][size];

    int k = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (firstMatrix[i][j] != 0) {
                compactMatrix[0][k] = i;
                compactMatrix[1][k] = j;
                compactMatrix[2][k] = firstMatrix[i][j];
                k++;
            }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", compactMatrix[i][j]);

        printf("\n");
    }

}


struct Node {
    string value, code;
    unsigned amount;
    Node *left;
    Node *right;

    bool operator()(const Node &x, const Node &y) const {
        return x.amount > y.amount;
    }

    explicit Node(const string &value = "", unsigned amount = 0, Node *left = 0, Node *right = 0) {
        this->value = value;
        this->code = "";
        this->amount = amount;
        this->left = left;
        this->right = right;
    }

    string to_str() {
        ostringstream x;
        if (left != nullptr || right != nullptr) {
            x << "\t\"" << code << ": " << value << "[" << amount << "]\" -> \"" << left->code << ": " << left->value
              << "[" << left->amount << "]\";\n";
            x << left->to_str();
            x << "\t\"" << code << ": " << value << "[" << amount << "]\" -> \"" << right->code << ": " << right->value
              << "[" << right->amount << "]\";\n";
            x << right->to_str();
        } else {
            x << "\t\"" << code << ": " << value << "[" << amount
              << "]\" [shape=box, style=filled, fillcolor=green];\n";
        }
        return x.str();
    }

    Node *join(const Node& x) {
        return new Node(x.value + value, x.amount + amount, new Node(x), this);
    }

    void traversal_code(string code) {
        this->code = code;
        if (left != 0 || right != nullptr) {
            left->traversal_code(code + "1");
            right->traversal_code(code + "0");
        }
    }

    static Node *builder(priority_queue<Node, vector<Node>, Node> graph) {
        while (graph.size() > 1) {
            Node *n = new Node(graph.top());
            graph.pop();
            graph.push(*n->join(*new Node(graph.top())));
            graph.pop();
        }
        return new Node(graph.top());
    }
};

unsigned amounts[256];

void functions::SaveFile() {
    string s;
    ifstream f("Matrix.txt");
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");
    while (!f.eof()) {
        getline(f,s);
    }
    f.close();

    for (auto i: s) amounts[i]++;
    priority_queue<Node, vector<Node>, Node> graph;
    for (int i = 0; i <= 1; i++)
        if (amounts[i] > 0) graph.emplace(s = (char) i, amounts[i]);
    Node *n = Node::builder(graph);
    n->traversal_code("");
}