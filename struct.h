#ifndef LAB1_STRUCT_H
#define LAB1_STRUCT_H
#include "string"

using namespace std;

struct User {
    int id;
    string login;
    string password;
    int roles;
};

struct Book {
    int id;
    string name;
    string author;
    int numberOfBooks;
};

#endif //LAB1_STRUCT_H
