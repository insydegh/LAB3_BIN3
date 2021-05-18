//
// Created by fokus on 17.05.2021.
//

#ifndef TREE_MENU_H
#define TREE_MENU_H

#endif //TREE_MENU_H
#include "BinTree.h"
#include <string>
#include <complex>
template<typename T>
T f(T x) {
    return x + x;
}

template<typename T>
T red(T x, T y) {
    return x + y;
}

template<typename T>
int a_where(T x) {

    return x>20.0000 ? 1: 0;
}

int a_where(string x) {

    return x.size()>4 ? 1 : 0;
}

int a_where (complex<double> number) {

    return number.real()>3? 1:0;
}

void sep() {
    std::cout << "-----------------------------------------------------------\n";
}


template<typename T>
BinTree<T> UI(bool child = false) {
    BinTree<T> bintree = BinTree<T>();
    while (true) {
        //----------------------------------------------------------
        {
            sep();
            cout << "Commands:\n";
            cout << "	s - Show tree keys and data\n";
            cout << "	1 - Add\n";
            cout << "	2 - Remove\n";
            cout << "	3 - Find\n";
            cout << "	4 - Map\n";
            cout << "	5 - Reduce\n";
            cout << "	6 - Where\n";
            cout << "	7 - Get Sub tree\n";
            cout << "	8 - Find Sub Tree\n";
            cout << "	9 - Threading + to String\n";
            cout << "	b - Balancing\n";
            cout << "	0 - exit\n";

            sep();
        }
        //----------------------------------------------------------
        char command;
        std::cin >> command;
        if (command == '0') {
            break;
        }
        if (command == 's') {
            bintree.Print();
        }
        if (command == '1') {
            int count;
            cout<<"How many adds do you want?: ";
            cin>>count;
            for (int i=0; i<count; i++) {
                T obj;
                int key;
                std::cout << "input value: ";
                std::cin >> obj;
                std::cout << "input key: ";
                std::cin >> key;
                bintree.Add(obj, key);
            }
        }
        if (command == '2') {
            int key;
            std::cout << "input key: ";
            std::cin >> key;
            bintree.Remove(key);
        }
        if (command == '3') {
            int key;
            std::cout << "input key: ";
            std::cin >> key;
            std::cout << "value: " << bintree.Find(key) << std::endl;
        }
        if (command == '4') {
            cout<<"MAP: multiplying data by 2"<<endl;
            bintree = bintree.Map(&f);
        }
        if (command == '5') {
            T start;
            cout<<"summing start and all trees elements"<<endl;
            std::cout << "Input start value: ";
            std::cin >> start;
            std::cout << bintree.Reduce(&red, start) << std::endl;
        }
        if (command == '6') {
            cout<<"WHERE: checks if data > of some number;"<<endl;

            bintree = bintree.Where(&a_where);
        }
        if (command == '7') {
            int key;
            std::cout << "Input key: ";
            std::cin >> key;
            bintree = bintree.GetSubTree(key);
        }
        if (command == '8') {
            std::cout << "Subtree creation, press 0 when you finished\n";
            BinTree<T> subtree = UI<T>(true);
            if (bintree.FindSubTree(subtree)) {
                std::cout << " it is a subtree\n";
            } else std::cout << "it is NOT a subtree\n";
        }
        if (command == '9') {
            string str;
            cout << "Insert method - N(Node) R(Right) L(Left) or any combination of these letters" << endl;
            cin >> str;
            cout << bintree.toString(str) << endl;
        }

        if (command == 'b') {
            bintree.Balancing();
        }
    }
    return bintree;
}





void Menu() {
    char command;
    //----------------------------------------------------------
    sep();
    std::cout << "Choose your type:\n";
    std::cout << "	1 - int\n";
    std::cout << "	2 - double\n";
    std::cout << "	3 - string\n";
    std::cout << "	4 - complex\n";
    std::cout << "	0 - exit\n";
    sep();
    //----------------------------------------------------------

    std::cin >> command;

    if (command == '0') {
        exit;
    }
    if (command == '1') {
        UI<int>();
    }
    if (command == '2') {
        UI<double>();
    }
    if (command == '3') {
        UI<std::string>();
    }
    if (command == '4') {
        UI<std::complex<double>>();
    }
}