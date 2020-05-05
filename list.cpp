#include "iostream"
#include "tree.h"

using namespace std;


List::List() {
    count = 0;
}

List::~List() {
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
}

void List::Add(tree *x, List listA) {
    Node *temp = new Node;
    temp->Next = nullptr;
    temp->x = x;
    if (Head != nullptr) {
        temp->Prev = Tail;
        Tail->Next = temp;
        Tail = temp;
        listA.count++;
    } else {
        temp->Prev = nullptr;
        Head = Tail = temp;
        listA.count++;
    }
}

void List::ShowFromEnd() const {
    Node *temp = Tail;
    while (temp != nullptr) {
        cout << temp->x << " ";

        temp = temp->Prev;
    }
    cout << "\n";
}

void List::ShowFromBeg() const {
    Node *temp = Head;
    while (temp != nullptr) {
        cout << temp->x->english << " " << temp->x->russian << " " << temp->x->amount;
        temp = temp->Next;
    }
    cout << "\n";
}

void List::Del(int x) {
    Node *temp = Head;
    if (Head == nullptr)
        return;
    if (x == 0) {
        Head = temp->Next;
        free(temp);
        return;
    }
    for (int i = 0; temp != nullptr && i < x - 1; i++)
        temp = temp->Next;

    if (temp == nullptr || temp->Next == nullptr)
        return;
    Node *next = temp->Next->Next;
    free(temp->Next);
    temp->Next = next;
}
