//
// Created by fokus on 24.05.2021.
//

#ifndef TREE_FROMSTRINGTOTREE_H
#define TREE_FROMSTRINGTOTREE_H

#endif //TREE_FROMSTRINGTOTREE_H
#include "BinTree.h"
#include <iostream>

template<typename _Tp>
inline _GLIBCXX_CONSTEXPR bool
operator<(const complex<_Tp>& __x, const complex<_Tp>& __y) {
    if (pow(__x.real(),2)+pow(__x.imag(),2) < pow(__y.real(),2)+pow(__y.imag(),2)) {
        return true;
    }
    else {
        return false;
    }
}

template<typename _Tp>
inline _GLIBCXX_CONSTEXPR bool
operator>(const complex<_Tp>& __x, const complex<_Tp>& __y) {
    if (pow(__x.real(),2)+pow(__x.imag(),2) > pow(__y.real(),2)+pow(__y.imag(),2)) {
        return true;
    }
    else {
        return false;
    }
}

//TO STRING
template <typename T>
bool compare(T a, T b)
{
    if (a < b) return true;
    else return false;
}

inline vector<string> split(const string str, const string delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

template <typename T>
vector<T> convert_to_array(string str) {
    vector<string> array = split(str, " ");
    vector<T> new_array;
    for (int i = 0; i<array.size(); i++) {
        string element = array[i];
        std::stringstream ss;
        ss<<element;
        T num;
        ss>>num;
        new_array.push_back(num);
    }
    return new_array;
}


template <typename T>
BinTree<T> toTree(string str, string method) {
    vector<T> array = convert_to_array<T>(str);
    BinTree<T>* tree =new BinTree<T>();
    if (method == "LNR" || method == "RNL") {
        Inorder(tree, array, 0, array.size() - 1);
    }
    else if (method == "NRL" || method == "NLR") {
        Preorder(tree, array);
    }
    else if (method == "RLN" || method == "LRN") {
        Postorder(tree, array);
    }
    return *tree;
}



template <typename T>
void Inorder(BinTree<T>* tree, vector<T> array, int left, int right) {
    if (left>right) return;
    int j = (left+right)/2;
    tree->Add(array[j]);
    Inorder(tree, array, left, j - 1);
    Inorder(tree, array, j + 1, right);
}

template <typename T>
void Preorder(BinTree<T>* tree, vector<T> array) {
    for (int i=0; i<array.size(); i++){
        tree->Add(array[i]);
    }
}

template <typename T>
void Postorder(BinTree<T>* tree, vector<T> array) {
    for (int i = array.size()-1; i>=0; i--) {
        tree->Add(array[i]);
    }
}



//MAP
template<typename T> BinTree<T> BinTree<T>::Map(T (*func)(T)) {
    BinTree<T>* binTree = new BinTree();
    vector<T>* array = new vector<T>();
    mapp(array, root, func);
    sort(array->хbegin(), array->end(), compare<T>);
    array->erase(unique(array->begin(), array->end()),array->end());
    Inorder(binTree, *array, 0, array->size() - 1);
    return *binTree;
}


