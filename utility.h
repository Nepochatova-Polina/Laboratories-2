#ifndef LABORATORIES_2_UTILITY_H
#define LABORATORIES_2_UTILITY_H
using namespace std;
struct Node {
    int peek;
    Node *Next, *Prev;
};
struct list {
    int x;
    list *Next, *Prev;
    Node *adjacent;

};

struct set {
    int x;
    set *Next, *Prev;
};


class BigList {

public:
    list *Head, *Tail;

    BigList() : Head(nullptr), Tail(nullptr) {};

    ~BigList();

    list *Add(Node *mass, int i);

    static int size(Node *list);

    Node * adjacentPeaks(int i);
};



class List {

public:
    Node *Head{}, *Tail{};

    List() : Head(nullptr), Tail(nullptr) {};

    ~List();

    void ShowfromBeg() const;

    Node *Add(int x);


};



class Set {

public:
    set *Head{}, *Tail{};

    Set() : Head(nullptr), Tail(nullptr) {};

    ~Set();

    void *Add(int x);

    bool Check(int x);

    void Delete(int x);

    bool empty();

    void print();

    void DeleteFromSet(Node *temp,Set *someSet);

    Set Union(Node *vertex,  Set someSet);

    Set Intersection(Node *vertex, Set someSet);

};

#endif //LABORATORIES_2_UTILITY_H
