#include "utility.h"
#include "iostream"
#include "string"

using namespace std;

//list
Node *List::Add(int x) {
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


List::~List() {
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
}
//List with lists

list *BigList::Add(Node *mass, int i) {
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
    return temp;
}

BigList::~BigList() {
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
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
//Set

Set::~Set() {
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
}


void *Set::Add(int x) {
    if (Check(x)) {
        return Head;
    }
    set *temp = new set;
    temp->Next = nullptr;
    temp->x = x;
    if (Head != nullptr) {
        temp->Prev = Tail;
        Tail->Next = temp;
        Tail = temp;
    } else {
        temp->Prev = nullptr;
        Head = Tail = temp;
    }

    return Head;
}

bool Set::Check(int x) {
    while (Head != nullptr) {
        if (Head->x != x) {
            Head = Head->Next;
        } else {
            return true;
        }
    }
    return false;
}

void Set::Delete(int x) {
    while (Head != nullptr) {
        if (Head->x != x) {
            Head = Head->Next;
        } else {
            Head->Prev->Next = Head->Next;
            free(Head);

        }
    }

}

bool Set::empty() {
    int i = 0;
    while (Head != nullptr) {
        Head = Head->Next;
        i++;
    }
    return i == 0;
}

void Set::print() {
    while (Head != nullptr) {
        cout << Head->x << " ";
        Head = Head->Next;
    }
}

void Set::DeleteFromSet(Node *temp, Set *someSet) {
    Node *listOf;
    while (Head != nullptr) {
        for(listOf = temp; listOf != nullptr; listOf = listOf->Next){
            if (temp->peek != Head->x) {
                someSet->Delete(temp->peek);
            }
        }
        Head = Head->Next;
    }
}

Set Set::Union(Node *vertex,  Set someSet){
    Node *listOf;
    while (Head != nullptr) {
        for(listOf = vertex; listOf != nullptr; listOf = listOf->Next){
            if (listOf->peek != Head->x) {
                someSet.Add(listOf->peek);
            }
        }
        Head = Head->Next;
    }

    return someSet;
}

Set Set::Intersection(Node *vertex, Set someSet){
    Set NewSet;
    Node *listOf;
    while (Head != nullptr) {
        for(listOf = vertex; listOf != nullptr; listOf = listOf->Next){
            if (listOf->peek == Head->x) {
                NewSet.Add(listOf->peek);
            }
        }
        Head = Head->Next;
    }

    return NewSet;
}