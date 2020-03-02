#include <iostream>
#include <utility>
#include "cstring"
#include "cmath"
#include <sstream>
#include <bitset>

using namespace std;
struct Jegalkin {
    string element;
    Jegalkin *next;
};

void push(string term);
void multipl(int term);
void plusCut();
void Bin(unsigned n);

Jegalkin *head(nullptr), *last(nullptr);
int static numberOfVariables;
unsigned int n = 0;

int main() {
    int pos, length;
    string polinom, term;
    cout << "Enter numberOfVariables of variables" << endl;
    cin >> numberOfVariables;
    cout << "Enter polinom:" << endl;
    cin.ignore();
    getline(cin, polinom);
    do {
        pos = polinom.find('+');
        term = polinom.substr(0, pos);
        push(term);
        length = polinom.length() - pos;
        polinom = polinom.substr(pos + 1, length);
    } while (pos != -1);
    plusCut();
    Bin(n);
    return 0;
}

void push(string term) {
    auto *temp = new Jegalkin;
    temp->next = nullptr;
    temp->element = std::move(term);
    if (head != nullptr) {
        last->next = temp;
        last = temp;
    } else {
        head = last = temp;
    }
}



void plusCut() {
    string x;
    int term;
    int pos, length;
    Jegalkin *temp = head;
    while ( temp->next != nullptr ) {
        temp = temp->next;
        x = temp->element;
        do {
            pos = x.find('*');
            term = atoi(x.substr(1, pos).c_str());;
            multipl(term);
            length = x.length() - pos;
            x = x.substr(pos + 1, length);
        } while (pos != -1);
    }
}

void multipl(int term) {
    unsigned int x = 0;
    int i = 0, k = 0;
    if (term > numberOfVariables - 2) {
        if (x == numberOfVariables - 1) {
            do {
                x += 0x3 * pow(16, i);
                i++;
            } while (i != pow(2, numberOfVariables - 2));
        } else {
            do {
                x += 0x5 * pow(16, i);
                i++;
            } while (i != pow(2, numberOfVariables - 2));
        }
    } else {
        if (term == 1) {
            do {
                x += 0xF * pow(16, i);
                i++;
            } while (i <= pow(2, numberOfVariables - 3));
        } else {
            do {
                do {
                    x += 0xF * pow(16, i);
                    i++;
                } while (i < numberOfVariables / term);
                do {
                    k += numberOfVariables / term;
                    x += 0x0 * pow(16, i);
                    i++;
                } while (i < numberOfVariables / term);
                k += numberOfVariables / term;
            } while (k < pow(2, numberOfVariables - 1));
        }
    }
    n += x;
}

void Bin(unsigned n) {

    if (n > 1) {
        Bin(n / 2);
    }
    cout << n % 2;
}


