#pragma once
#include <utility>
#include "struct.h"
#include "string"
#ifndef LAB1_USER_H
#define LAB1_USER_H


using namespace std;

class UserMenu {
    struct MenuItem {
        string title;

        void (*proc)();

        MenuItem(string aTitle, void (*procLink)()) {
            title = std::move(aTitle);
            proc = procLink;

        };
    };

    string menuTitle;
    vector<MenuItem> menuItems;

    void GetMenuView();

public:

    UserMenu() {
        menuTitle = "Main menu";
    }

    explicit UserMenu(string menuTitle) {
        this->menuTitle = std::move(menuTitle);
    }

    void AddMenuItem(string itemTitle, void (*procLink)());

    void ShowMenu();
};

class For_User {
public:
    Book static *readFile(long &size);

    void static writeIntoFile(string book);

    bool static returnBooks(const string &book);

    bool static giveBooks(const string &book);

    UserMenu static initUserMenu();

};



#endif //LAB1_USER_H
