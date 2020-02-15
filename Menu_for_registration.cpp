#include "Menu_for_registration.h"
#include "struct.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "string"
#include "cstring"


using namespace std;


int n = 1;
User newArr[50];

void Menu_for_registration::readUsers() {
    ifstream f("people.data", ios::binary);
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");
    while (!f.eof()) {

        f.read((char *) &newArr, sizeof(newArr));
        f.close();
    }
}

bool Menu_for_registration::entrance(const string& login, const string& password, int &role) {
    long result = MD5(password);
    readUsers();
    for (auto & i : newArr) {
        if (login == i.login) {
            long UsersResults = MD5(i.password);
            if (UsersResults == result) {
                role = i.roles;
                return true;
            }
        }
    }
}

bool Menu_for_registration::wantToRegistrate(int &role) {
    string password;
    User registrate;
    cout << "Create login" << endl;
    cin >> registrate.login;
    cout << "Create password" << endl;
    cin >> password;
    cout << "If you are a User press 0, else, press 1" << endl;
    cin >> registrate.roles;
    role = registrate.roles;
    long newPassword = MD5(password);
    registrate.password = newPassword;
    registrate.id = n++;
    writeNewUser(registrate);
    return true;
}

long Menu_for_registration::MD5(const string &password) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(password);
    long result = hash;

    return result;
}

void Menu_for_registration::writeNewUser(const Menu_for_registration::User &registrate) {
    ofstream f("people.data", ios::binary|ios::in);
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");
    f.write((char *) &registrate, sizeof(registrate));
    f.close();
}
