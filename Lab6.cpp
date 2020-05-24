#include <iostream>
#include "fstream"
#include <cstdio>
#include "utility.h"
using namespace std;

void Kerbosh(Set possibleNode, Set possibleClique, Set noNodes, BigList *MainList);
int main() {
    Set possibleNode;
    Set possibleClique;
    Set noNodes;
    BigList MainList;
    int num = 7;
    Node *mass[num];
    ifstream file("note.txt");
    if (file.is_open())
        cout << "file is open" << endl;
    else {
        cout << "ERROR! File can't be open " << endl;
    }
    string s;
    int j = 0;
    while (!file.eof()) {
        getline(file, s);
        List adjList;
        for (char i : s) {
            if (i != ' ') {
                adjList.Add(i);
            }
        }
        mass[j] = adjList.Head;
        j++;
    }
    file.close();

    int x = 1;
    for (int i = 0; i < j; j++) {
        MainList.Add(mass[i], i);
        x++;
    }
    for(int i = 1; i < 8; i++) {
        possibleNode.Add(i);
    }
    Kerbosh( possibleNode,  possibleClique, noNodes, &MainList);
}

void Kerbosh(Set possibleNode, Set possibleClique, Set noNodes, BigList *MainList){
    if (possibleNode.empty() && noNodes.empty()) {
        cout << "Clique found: ";
        possibleClique.print();
    }else {
        for (int x = 0; x < 7; x++) {
            Node *temp = MainList->adjacentPeaks(x);
            Set NewpossibleNode = possibleClique.Union(temp, possibleClique);
            Set NewnoNodes = noNodes.Intersection(temp,noNodes);
            possibleClique.Add(x);
            Kerbosh( NewpossibleNode, possibleClique, NewnoNodes, MainList);
            possibleNode.Delete(x);
            noNodes.Add(x);
        }
    }
}
