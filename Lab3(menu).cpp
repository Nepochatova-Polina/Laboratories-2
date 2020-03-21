#include "functions.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>

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


void Menu::GetMenuView() {
    std::system( "clear");

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
    cout << endl << "Type \"q\" for Exit " << endl;

    cout << endl;
    cout << endl;

    cout << "Type item num..." << endl;
}

void Menu::AddMenuItem(string itemTitle, void (*procLink)()) {
    menuItems.push_back(*(new MenuItem(std::move(itemTitle), procLink)));
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
            std::system( "clear");
            menuItems[itemN - 1].proc();
        } else
            errorCode = true;
    } while (strcmp(choice, "q") != 0);
    std::system( "clear");
}

void writeMatrix() {
    functions::writeFunction();
}
void AddMatrix(){
    functions::readFile();
    functions::additionMatrix();
}
void readFile(){
    functions::readFile();;
    functions::writeFunction();
}
void MultiMatrix(){
    functions::readFile();
    functions::multiMatrix();
}
void SaveMatrix(){
    functions::SaveMatrix();
}
void SaveFile(){
    functions::SaveFile();
}
int main() {
    Menu someMenu("Main menu");

    someMenu.AddMenuItem("Write matrix", writeMatrix);
    someMenu.AddMenuItem("Add matrix", AddMatrix);
    someMenu.AddMenuItem("multiplicate matrix", AddMatrix);
    someMenu.AddMenuItem("Read matrix from file", readFile);
    someMenu.AddMenuItem("Index matrix storage", SaveMatrix);
    someMenu.AddMenuItem("File storage", SaveFile);





    someMenu.ShowMenu();

    return 0;

