//
// Created by fokus on 31.05.2021.
//

#ifndef TREE_TRIARYTREE_H
#define TREE_TRIARYTREE_H

#endif //TREE_TRIARYTREE_H



#include <complex>
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Heap {

private:
    static const int SIZE = 100;
    T *elems;
    int size;

public:

    Heap() {
        elems = new T[SIZE];
        size=0;
    }


     void printHeap() {
         cout<<"Your heap:"<<endl;
         for(int i=0; i< size; i++) {
             cout << elems[i] << " "; }
         cout << endl;
        int countOfGaps = 32;
        int itemsPerRow = 1;
        int columnNumber = 0; // element number in this string
        string lines = "___________________________________________________________________";

        cout<<lines<<endl;
        for (int i = 0; i < size; i++) {
            if (columnNumber == 0) {  // checks if the element is first in this string
                for (int k = 0; k < countOfGaps; k++) { // add spaces
                    cout<<' ';
                }
            }
            cout<<elems[i];

            if (++columnNumber == itemsPerRow) { // checks if the element is last
                countOfGaps /= 2; // cut spaces for the next string
                itemsPerRow *= 2; // multuply number elements by 2
                columnNumber = 0; // reset the counter
                cout<<endl;
            }
            else {
                for (int k = 0; k < countOfGaps * 2 - 2; k++) {
                    cout<<' '; // add spaces
                }
            }
        }
        cout<<"\n"<<lines<<endl;
    }

    void PrintArray() {
        for(int i=0; i< size; i++) {
            cout << elems[i] << " "; }
        cout << endl;
    }


     void insertNode(T value) {
        if (size == SIZE) {
            return;
        }

        elems[size] = value;// add item to the array's end
        displaceUp(size++);// lifting the item up
        return;
    }

    T removeByNumber(T item) {
        int index = this->GetIndex(item);
        if(index >= 0 && size > index) {
            T root = elems[index];
            elems[index] = elems[--size]; // set given item index to the last item
            elems[size] = T(0);
            displaceDown(index);// push down the element
            //return root;
        }
        //return 0;
    }

    T removeByIndex(int index) {
        if(index >= 0 && size > index) {
            T root = elems[index];
            elems[index] = elems[--size];
            elems[size] = T(0);
            displaceDown(index);
            //return root;
        }
        //return 0;
    }

     void displaceUp(int index) {
        int parentIndex = (index - 1) / 2; // get parent index
        T bottom = elems[index]; // get element
        while (index > 0 && elems[parentIndex] < bottom) {//
            elems[index] = elems[parentIndex];// change out elem and parent
            index = parentIndex;
            parentIndex = (parentIndex - 1) / 2;// set new parent
        }
        elems[index] = bottom;
    }

    void displaceDown(int index) {//
        int largerChild;
        T top = elems[index]; //
        while (index < size / 2) {// if true then element is on the bottom
            int leftChild = 2 * index + 1; // get index for the left child
            int rightChild = leftChild + 1;//  for the right

            if (rightChild < size && elems[leftChild] < elems[rightChild]) {
                largerChild = rightChild;
            }
            else {
                largerChild = leftChild;
            }

            if (top >= elems[largerChild]) {

                break;
            }

            elems[index] = elems[largerChild];//
            index = largerChild; //
        }
        elems[index] = top; //
    }

    int GetIndex(T item) {
         for (int i=0; i<size; i++) {
             if (elems[i] == item) return i;
         }
        return NULL;
     }

    int find_array(int index) {
         if (index<size) return elems[index];
         else return NULL;
    }

    bool find_bool(T item) {
        for (int i=0; i<size; i++) {
            if (elems[i] == item) return true;
        }
        return false;
    }

    ~Heap(){};
};






