//
// Created by fokus on 23.05.2021.
//
#include "PerfomanceTest.h"

void Add_list_test() {
    fstream fs;
    fs.open("Add_tree.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 11000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        auto begin = std::chrono::steady_clock::now();
        for(int j = 0 ; j < i; j++)
            tree->Add(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}


void Add_tree_test() {
    fstream fs;
    fs.open("Add_tree.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 11000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()-std::chrono::steady_clock::now());
        for(int j = 0 ; j < i; j++) {
            auto begin = std::chrono::steady_clock::now();
            tree->Add(j);
            auto end = std::chrono::steady_clock::now();
            elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin) + elapsed_ms;
            tree->newBalancing();
        }
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}


void Balancing_old_test() {
    fstream fs;
    fs.open("Balancing_old.txt", fstream::in | fstream::out | fstream::app);
    for (int i = 0; i < 10000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = i ; j >0 ; j--) {
            tree->Add(j);
        }
        auto begin = std::chrono::steady_clock::now();
        tree->newBalancing();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i + 1 << endl;
    }
}


void Balancing_new_test() {
    fstream fs;
    fs.open("Balancing_new.txt", fstream::in | fstream::out | fstream::app);
    for (int i = 0; i < 9200; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = i ; j >0 ; j--) {
            tree->Add(j);
        }
        auto begin = std::chrono::steady_clock::now();
        tree->newBalancing();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i + 1 << endl;
    }
}


void Find_list_test() {
    fstream fs;
    fs.open("Find_list.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 50000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = 0 ; j < i; j++)
            tree->Add(j);
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j<i; j++)
            tree->Find(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}

void Find_tree_test() {
    fstream fs;
    fs.open("Find_tree.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 9700; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = 0 ; j < i; j++)
            tree->Add(j);
        tree->newBalancing();
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j<i; j++)
            tree->Find(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}

void Remove_list_teest() {
    fstream fs;
    fs.open("Remove_list.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 10000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = 0 ; j < i; j++)
            tree->Add(j);
        auto begin = std::chrono::steady_clock::now();
        for (int j = i; j>0; j--)
            tree->Remove(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}


void Remove_tree_test() {
    fstream fs;
    fs.open("Remove_tree.txt", fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < 10000; i++) {
        BinTree<int>* tree = new BinTree<int>();
        for(int j = 0 ; j < i; j++)
            tree->Add(j);
        tree->newBalancing();
        auto begin = std::chrono::steady_clock::now();
        for (int j = i; j>0; j--)
            tree->Remove(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        fs << elapsed_ms.count() << ',' << i+1 << endl;
    }
}