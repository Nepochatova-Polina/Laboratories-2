# pragma once
#include "Admin.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "struct.h"

using namespace std;

void writeIntoFile(Book &newBook);

void AdminMenu::GetMenuView() {
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

void AdminMenu::AddMenuItem(string itemTitle, void (*procLink)()) {
    menuItems.push_back(*(new MenuItem(std::move(itemTitle), procLink)));
}

void AdminMenu::ShowMenu() {
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


void Create() {
    Book newBook;
    string author, name;
    cout << " Enter multiple number" << endl;
    cin >> newBook.id;
    cout << "Enter name of book:" << endl;
    cin.ignore();
    getline(cin,name);
    newBook.name = name;
    cout << "Enter name of author:" << endl;
    cin.ignore();
    getline(cin,author);
    newBook.author = author;
    cout << "Enter number of books:" << endl;
    cin >> newBook.numberOfBooks;
    forAdmin::writeIntoFile(newBook);
    cout << "Book are in your library" << endl;
}

void Read() {
    ifstream f("library.data", ios::binary | ios::out);
    if (!f.is_open())
        perror("error while opening file");
    if (f.bad())
        perror("error while reading file");
    Book bookArr[3];
    f.read((char *) &bookArr, sizeof(bookArr));

    f.close();
    for (int i = 0; i < 3; i++) {
        cout << "id:" << bookArr[i].id << endl;
        cout << "Book's name:" << bookArr[i].name << endl;
        cout << "Author:" << bookArr[i].author << endl;
        cout << "Number of books in library:" << bookArr[i].numberOfBooks << endl;

    }

}

void Update() {

}

void forAdmin::writeIntoFile(Book &newBook) {
    ofstream f("library.data", ios::binary|ios::in);
    if (!f.is_open())
        perror("error while opening file");

    if (f.bad())
        perror("error while reading file");

    f.write((char *) &newBook, sizeof(newBook));
    f.close();

}


AdminMenu forAdmin::initUserMenu() {
    AdminMenu adminMenu("Admin menu");
    adminMenu.AddMenuItem("Create new book", Create);
    adminMenu.AddMenuItem("Read library", Read);
    adminMenu.AddMenuItem("Update information", Update);
    adminMenu.ShowMenu();

    return adminMenu;
}
