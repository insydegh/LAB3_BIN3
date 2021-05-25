//
// Created by fokus on 17.05.2021.
//

#ifndef TREE_MENU_H
#define TREE_MENU_H

#endif //TREE_MENU_H
#include "FromStringToTree.h"

template<typename T>
T fmap(T x);

template<typename T>
T red(T x, T y);

template<typename T>
int a_where(T x);
int a_where(string x);
int a_where (complex<double> number);

void sep();

template<typename T>
BinTree<T> UI(bool child = false);

void Menu();