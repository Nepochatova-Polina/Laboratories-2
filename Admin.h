#pragma once

#include <utility>
#include "struct.h"
#include "string"

#ifndef LAB1_ADMIN_H
#define LAB1_ADMIN_H


using namespace std;

class AdminMenu {
    struct MenuItem {
        string title;

        void (*proc)();

        MenuItem(string aTitle, void (*procLink)()) {
            title = std::move(aTitle);
            proc = procLink;
        }
    };

    string menuTitle;
    vector<MenuItem> menuItems;

    void GetMenuView();

public:

    AdminMenu() {
        menuTitle = "Main menu";
    }

    explicit AdminMenu(string title) {
        title = std::move(title);
    }

    void AddMenuItem(string itemTitle, void (*procLink)());

    void ShowMenu();
};


class Admin {

public:
    void static writeIntoFile(Book &newBook);

    AdminMenu static initUserMenu();
};

#endif //LAB1_ADMIN_H
