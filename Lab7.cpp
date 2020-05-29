#include <iostream>
#include "fstream"
#include "string"
#include "utility.h"

using namespace std;

void InsertSort(BigList *MainList, int number, int sizeArr[]);

void BubbleSort(BigList *Mainlist, int sizeArr[]);

void quicksort(int *mas, int first, int last, BigList *Mainlist);

void ShakerSort(int *arr, int size, BigList *Mainlist);

void ShellaSort(int sizeArr[], int n, BigList *Mainlist);

void merge(int *arr, int low, int high, int mid);

void mergeSort(int *arr, int low, int high);

int main() {
    int number = 7;
    BigList MainList;
    int sizeArr[number];
    Node *mass[number];
    ifstream file("note.txt");
    if (file.is_open())
        cout << "file is open" << endl;
    else {
        cout << "ERROR! File can't be open " << endl;
    }
    string s;
    int i = 1, size = 0, count = 0;
    while (!file.eof()) {
        getline(file, s);

        List adjList;
        for (char j : s) {
            if (j != ' ') {
                adjList.Add(j);
                size++;
            }
        }
        if (i == 8) {
            break;
        }
        sizeArr[count] = size;
        MainList.Add(adjList.Head, i);
        i++;
        count++;
        size = 0;
    }
    file.close();
//    InsertSort(&MainList, number, sizeArr);

//    BubbleSort(&MainList, sizeArr);

//    quicksort(sizeArr, sizeArr[0], sizeArr[6], &MainList);

//    ShellaSort(sizeArr, number, &MainList);

    ShakerSort(sizeArr, number, &MainList);

//    mergeSort( sizeArr, 0, number - 1);
}


void InsertSort(BigList *Mainlist, int number, int sizeArr[]) {
    int buff = 0;
    int i, j;
    for (i = 1; i < number; i++) {
        buff = sizeArr[i];
        for (j = i - 1; j >= 0 && sizeArr[j] > buff; j--)
            sizeArr[j + 1] = sizeArr[j];
        sizeArr[j + 1] = buff;
        Mainlist->ChangeNodes(j + 1, i);
    }
    for (int i = 0; i < number; i++)
        cout << sizeArr[i] << '\t';
    cout << endl;
}

void BubbleSort(BigList *Mainlist, int sizeArr[]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            if (sizeArr[j] > sizeArr[j + 1]) {
                swap(sizeArr[j], sizeArr[j + 1]);
                Mainlist->ChangeNodes(j, j + 1);
            }
        }
    }
}

void quicksort(int *mas, int first, int last, BigList *Mainlist) {
    int mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2];
    do {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        if (f <= l) {
            swap(mas[l], mas[f]);
            f++;
            l--;
            Mainlist->ChangeNodes(l, f);
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l, Mainlist);
    if (f < last) quicksort(mas, f, last, Mainlist);
}


void ShakerSort(int *arr, int size, BigList *Mainlist) {
    int leftMark = 1;
    int rightMark = size - 1;
    while (leftMark <= rightMark) {
        for (int i = rightMark; i >= leftMark; i--) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i], arr[i - 1]);
                Mainlist->ChangeNodes(i, i - 1);
                leftMark++;
            }
        }

        for (int i = leftMark; i <= rightMark; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i], arr[i - 1]);
                Mainlist->ChangeNodes(i, i - 1);
                rightMark--;
            }
        }
    }
}

void ShellaSort(int sizeArr[], int n, BigList *Mainlist) {
    int i, j;
    int d = n;
    d = d / 2;
    while (d > 0) {
        for (i = 0; i < n - d; i++) {
            j = i;
            while (j >= 0 && sizeArr[j] > sizeArr[j + d]) {
                swap(sizeArr[j], sizeArr[j + d]);
                Mainlist->ChangeNodes(j, j + d);
                j--;
            }
        }
        d = d / 2;
    }
}

void mergeSort(int *arr, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}

void merge(int *arr, int low, int high, int mid) {
    int i, j, k, c[10];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        } else {
            c[k] = arr[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
    }
}
