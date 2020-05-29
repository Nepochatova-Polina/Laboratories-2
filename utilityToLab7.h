#ifndef LABORATORIES_2_UTILITYTOLAB7_H
#define LABORATORIES_2_UTILITYTOLAB7_H


struct Node {
    char peek;
    Node *Next, *Prev;
};
struct list {
    int x;
    list *Next, *Prev;
    Node *adjacent;

};




class BigList {

public:
    list *Head, *Tail;

    BigList() : Head(nullptr), Tail(nullptr) {};


    void Add(Node *mass, int i);

    static int size(Node *list);

    Node * adjacentPeaks(int i);

    void ChangeNodes(int first, int second);

    void Show() const;
};



class List {

public:
    Node *Head{}, *Tail{};

    List() : Head(nullptr), Tail(nullptr) {};

    void ShowfromBeg() const;

    Node *Add(char x);


};



#endif //LABORATORIES_2_UTILITYTOLAB7_H
