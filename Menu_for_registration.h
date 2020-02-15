#ifndef LAB1_MENU_FOR_REGISTRATION_H
#define LAB1_MENU_FOR_REGISTRATION_H
#include "string"

using namespace std;

 const int number = 50;

class Menu_for_registration {

    struct User{
        int id;
        string login;
        string password;
        int roles;
    };

public:
    static long MD5(const string& password);

    static bool entrance(const string& login, const string& password, int &role);

    static bool wantToRegistrate(int &role);

    static void writeNewUser(const User& registrate);

    static void readUsers();
};


#endif //LAB1_MENU_FOR_REGISTRATION_H
