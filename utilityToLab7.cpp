#include "utilityToLab7.h"
#include "iostream"
#include "utility.h"

using namespace std;

//list
Node *List::Add(char x) {
    Node *temp = new Node;
    temp->Next = nullptr;
    temp->peek = x;

    if (Head != nullptr) {
        temp->Prev = Tail;
        Tail->Next = temp;
        Tail = temp;
    } else {
        temp->Prev = nullptr;
        Head = Tail = temp;
    }
    return temp;
}

void List::ShowfromBeg() const {
    Node *temp = Head;
    while (temp != nullptr) {
        cout << temp->peek << " ";
        temp = temp->Next;
    }
    cout << "\n";
}


//List with lists

void BigList::Add(Node *mass, int i) {
    list *temp = new list;
    temp->x = i;
    temp->Next = nullptr;
    temp->adjacent = mass;

    if (Head != nullptr) {
        temp->Prev = Tail;
        Tail->Next = temp;
        Tail = temp;
    } else {
        temp->Prev = nullptr;
        Head = Tail = temp;
    }

}

void BigList::Show() const {
    list *temp = Head;
    while (temp != nullptr) {
        cout << temp->x << " ";
        temp = temp->Next;
    }
    cout << "\n";
}


int BigList::size(Node *list) {
    int i = 0;
    while (list != nullptr) {
        i++;
        list = list->Next;
    }

    return i;
}

Node *BigList::adjacentPeaks(int i) {
    while (Head != nullptr) {
        if (Head->x != i) {
            Head = Head->Next;
        }
        return Head->adjacent;
    }
}

void BigList::ChangeNodes(int first, int second) {
    int i = 0;
    list *temp = Head;
    list *A, *B;
    while (i <= first) {
        if (Head != nullptr) {
            A = Head;
            i++;
            Head = Head->Next;
        } else {
            break;
        }
    }
    i = 0;
    while (i <= second) {
        if (Head != nullptr) {
            B = temp;
            i++;
            temp = temp->Next;
        } else {
            break;
        }
    }
    list *ANext, *APrev, *BNext, *BPrev, *sometp;
    ANext = A->Next;
    APrev = A->Prev;
    BNext = B->Next;
    BPrev = B->Prev;
    sometp = APrev;
    if (sometp != nullptr) {
        sometp->Next = B;
    }
    sometp = ANext;
    if (sometp != nullptr) {
        sometp->Prev = B;
    }
    sometp = BPrev;
    if (sometp != nullptr) {
        sometp->Next = A;
    }
    sometp = BNext;
    if (sometp != nullptr) {
        sometp->Prev = A;
    }

    A->Next = BNext;
    A->Prev = BPrev;
    B->Next = ANext;
    B->Prev = APrev;

}
