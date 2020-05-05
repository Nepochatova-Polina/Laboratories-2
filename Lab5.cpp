#include "tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
List listA = List();
class Menu {
    struct MenuItem {
        string title;

        void (*proc)();

        MenuItem(string aTitle, void (*procLink)()) {
            title = aTitle;
            proc = procLink;
        }
    };

    string menuTitle;
    vector<MenuItem> menuItems;


    void GetMenuView();

public:

    // Constructors
    Menu() {
        menuTitle = "Main menu";
    }

    Menu(string menuTitle) {
        this->menuTitle = menuTitle;
    }

    // Interface methods
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
    for (vector<MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++, ItemNumber++) {
        cout << ItemNumber << " ->) " << it->title << endl;
    }
    cout << endl << "Type \"q\" for Exit " << endl;

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
            std::system( "clear");
            menuItems[itemN - 1].proc();
        } else
            errorCode = true;
    } while (strcmp(choice, "q"));
    std::system( "clear");
}

void read() {
    int num;
    setlocale(LC_ALL, "Russian");
    cout << "Enter number of words in dictionary:" << endl;
    cin >> num;

    for (int i = 0; i < num; i++) {
        tree *temp = new tree;
        cout << "Enter english word:" << endl;
        cin >> temp->english;
        if (!Tree::checkWord(temp->english)) {
            cout << "Wrong word!";
            break;
        }
        cout << "Enter russian translate:" << endl;
        cin >> temp->russian;
        if (!Tree::checkWord(temp->russian)) {
            cout << "Wrong word!";
            break;
        }
        cout << "Enter number of calls to the word" << endl;
        cin >> temp->amount;
        listA.Add(temp, listA);
    }
}


void showList() {
    listA.ShowFromBeg();
}
void writeIntoBinaryTree() {
    Tree::writeInBin(listA.Head, listA.count,listA);
}
void showTree(){

}
int main() {
    Menu someMenu("Main menu");

    someMenu.AddMenuItem("To fill vocabulary", read);
    someMenu.AddMenuItem("Show first vocabulary", showList);
    someMenu.AddMenuItem("Write first vocabulary into binary tree", writeIntoBinaryTree);
    someMenu.AddMenuItem("Show second vocabulary", showTree);

    someMenu.ShowMenu();
    return 0;
}