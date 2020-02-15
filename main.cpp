#include <iostream>
#include <fstream>
#include <ostream>
#include "string"
#include <utility>
#include <vector>
#include "cmath"
#include "cstring"
#include "Menu_for_registration.h"
#include "User.h"
#include "Admin.h"


using namespace std;

class Menu {
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
    Menu() {
        menuTitle = "Main menu";
    }

    explicit Menu(string menuTitle) {
        this->menuTitle = std::move(menuTitle);
    }

    void AddMenuItem(string itemTitle, void (*procLink)());

    void ShowMenu();
};

Menu initMainMenu();

void Menu::GetMenuView() {
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

void Menu::AddMenuItem(string itemTitle, void (*procLink)()) {
    menuItems.push_back(*(new MenuItem(itemTitle, procLink)));
}

void Menu::ShowMenu() {
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
    } while (strcmp(choice, "0"));
    std::system("clear");
}

void entrance() {
    string login, password;
    int role;
    cout << "Enter your login" << endl;
    cin >> login;
    cout << "Enter your password" << endl;
    cin >> password;

    bool result = Menu_for_registration::entrance(login, password, role);
    if (result) {
        cout << "Hello dear Client" << endl;
        switch (role) {
            case 0:
                For_User::initUserMenu().ShowMenu();
            case 1:
                forAdmin::initUserMenu().ShowMenu();
        }
    } else{
        cout << " Sorry, You were not found" << endl;
    }
}

void registration() {
    int role;
    bool result = Menu_for_registration::wantToRegistrate(role);
    if (result) {
        cout << "registration is sucessful" << endl;
        switch (role) {
            case 0:
                For_User::initUserMenu().ShowMenu();
            case 1:
                forAdmin::initUserMenu().ShowMenu();
            default:
                cout << " Sorry, You were not found" << endl;
        }
    }
}

Menu initMainMenu() {
    Menu someMenu("Choose your next step");
    someMenu.AddMenuItem("entrance", entrance);
    someMenu.AddMenuItem("Do you want to register", registration);
    return someMenu;
}

int main() {
    initMainMenu().ShowMenu();
    return 0;
}



