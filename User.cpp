# pragma once
#include "User.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <ostream>
#include "struct.h"

using namespace std;


Book readFile(int *size);

void writeIntoFile(string book);

void giveBooks(string book);

void returnBooks(string book);


void UserMenu::GetMenuView() {
    std::system("clear");

    for (unsigned int i = 0; i < menuTitle.size() + 10; i++)
        cout << "=";
    cout << endl;
    cout << menuTitle << endl;
    for (unsigned int i = 0; i < menuTitle.size() + 10; i++)
        cout << "=";
    cout << endl;

    int ItemNumber = 1;
    for (auto it = menuItems.begin(); it != menuItems.end(); it++, ItemNumber++) {
        cout << ItemNumber << " ->) " << it->title << endl;
    }
    cout << endl << "Type \"0\" for Exit " << endl;

    cout << endl;
    cout << endl;

    cout << "Type item num..." << endl;
}

void UserMenu::AddMenuItem(string itemTitle, void (*procLink)()) {
    menuItems.push_back(*(new MenuItem(std::move(itemTitle), procLink)));
}

void UserMenu::ShowMenu() {
    bool errorCode = false;
    int itemN = 0;
    char choice[255];
    do {
        GetMenuView();

        if (errorCode) {
            cout << "[ERROR] Wrong input!" << endl;
            errorCode = false;
        }

        cin >> choice;
        itemN = atoi(choice);

        if (itemN > 0 && itemN <= (int) menuItems.size()) {
            std::system("clear");
            menuItems[itemN - 1].proc();
        } else
            errorCode = true;
    } while (strcmp(choice, "0") != 0);
    std::system("clear");
}

void chooseBook() {
    string book;
    fstream f("library.data", ios::binary | fstream::in | fstream::out | fstream::app);
    if (!f.is_open())
        perror("error while opening file");
    if (f.bad())
        perror("error while reading file");
    Book bookArr[20];
    while (!f.eof()) {
        f.read((char *) &bookArr, sizeof(bookArr));
    }
    cout << "Enter name of book" << endl;
    cin >> book;
    for (int i = 0; i < 20; i++) {
        if (bookArr[i].name == book) {
            For_User::writeIntoFile(book);
            For_User::giveBooks(book);
            cout << "Book are in your checklist" << endl;
            break;
        }
    }
    cout << "There are not such book in our library" << endl;
}

void returnBook() {
    string book;
    cout << "Enter name of book" << endl;
    cin >> book;
    bool result = For_User::returnBooks(book);
    if (result) {
        cout << "all right!" << endl;
    } else {
        cout << "There are no such book in our library" << endl;
    }

}

void showChecklist() {
    string line;
    ifstream f("Checklist.txt");
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");
    while (!f.eof()) {
        getline(f, line);
        cout << "You choose this books" << endl;
        cout << line << endl;
    }

    f.close();
}
void Confirm(){
    cout << "Pick up your books at the pick-up point" << endl;
}
UserMenu For_User::initUserMenu() {
    UserMenu someMenu("User menu");
    someMenu.AddMenuItem("Choose Book", chooseBook);
    someMenu.AddMenuItem("Return Book", returnBook);
    someMenu.AddMenuItem("Show my checklist", showChecklist);
    someMenu.AddMenuItem("Confirm my order", Confirm);

    someMenu.ShowMenu();
    return UserMenu();
}


void For_User::writeIntoFile(string book) {
    ofstream f("Checklist.txt");
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");

    f.write((char *) &book, book.size());

    f.close();

}

bool For_User::returnBooks(const string &book) {
    fstream f("library.data", ios::binary | fstream::in | fstream::out | fstream::app);
    if (!f.is_open())
        perror("error while opening file");
    if (f.bad())
        perror("error while reading file");
    Book bookArr[20];
    while (!f.eof()) {
        f.read((char *) &bookArr, sizeof(bookArr));
        f.close();

    }
    for (int i = 0; i < 20; i++) {
        if (book == bookArr[i].name) {
            bookArr[i].numberOfBooks++;
            f.write((char *) &bookArr, sizeof(bookArr));
            return true;
        } else {
            return false;
        }
    }
}

bool For_User::giveBooks(const string &book) {
    fstream f("library.data", ios::binary | fstream::in | fstream::out | fstream::app);
    if (!f.is_open())
        perror("error while opening file");
    if (f.bad())
        perror("error while reading file");
    Book bookArr[20];
    while (!f.eof()) {
        f.read((char *) &bookArr, sizeof(bookArr));
    }
    f.close();
    for (int i = 0; i < 20; i++) {
        if (book == bookArr[i].name) {
            bookArr[i].numberOfBooks--;
            f.write((char *) &bookArr, sizeof(bookArr));
            return true;
        } else {
            return false;
        }
    }
}


