//
// Created by fokus on 23.05.2021.
//
#include "Menu.h"
#include "BinTree.h"

template<typename T>
T fmap(T x) {
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
BinTree<T> UI(bool child) {
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
            cout << "	n - Create new tree from string\n";
            cout << "	0 - exit\n";

            sep();
        }
        //----------------------------------------------------------
        char command;
        std::cin >> command;
        if (command == '0') {
            break;
        }
        if (command == 's' || command == 'S') {
            bintree.Print();
        }
        if (command == '1') {
            int count;
            cout<<"How many adds do you want?: ";
            cin>>count;
            for (int i=0; i<count; i++) {
                T key;
                std::cout << "input key: ";
                std::cin >> key;
                bintree.Add(key);
            }
        }
        if (command == '2') {
            T key;
            std::cout << "input key: ";
            std::cin >> key;
            bintree.Remove(key);
        }
        if (command == '3') {
            T key;
            std::cout << "input key: ";
            std::cin >> key;
            if (bintree.Find(key)==1) cout<<"Branch exist"<<endl;
            else cout<<"Branch DO NOT exist"<<endl;
        }

        if (command == '4') {
            cout<<"MAP: multiplying data by 2"<<endl;
            bintree = bintree.Map(fmap);
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
            T key;
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

        if (command == 'n' || command == 'N') {
            string method;
            cout << "Insert method - N(Node) R(Right) L(Left) or any combination of these letters" << endl;
            cin >> method;
            string str;
            cout << "Insert your string:"<<endl;
            getchar();
            getline ( std::cin, str );
            bintree = toTree<T>(str, method);
        }

        if (command == 'b' || command == 'B') {
            if (bintree.IsBalanced()==true) {
                cout<<"Tree is already balanced"<<endl;
            }
            else
                bintree.newBalancing();
        }
    }
    return bintree;
}





void MenuTree() {
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
        UI<string>();
    }

    if (command == '4') {
        UI<complex<double>>();
    }

}



template<typename T>
Heap<T> UI_H(bool child) {
    Heap<T> heap = Heap<T>();
    while (true) {
        //----------------------------------------------------------
        {
            sep();
            cout << "Commands:\n";
            cout << "	s - Show Heap\n";
            cout << "	p - Show array\n";
            cout << "	1 - Add\n";
            cout << "	2 - Remove by number\n";
            cout << "	3 - Remove by index\n";
            cout << "	4 - Find\n";
            cout << "	0 - exit\n";

            sep();
        }
        //----------------------------------------------------------
        char command;
        std::cin >> command;
        if (command == '0') {
            break;
        }
        if (command == 's' || command == 'S') {
            heap.printHeap();
        }

        if (command == 'p' || command == 'P') {
            heap.PrintArray();
        }
        if (command == '1') {
            int count;
            cout<<"How many adds do you want?: ";
            cin>>count;
            for (int i=0; i<count; i++) {
                T key;
                std::cout << "input key: ";
                std::cin >> key;
                heap.insertNode(key);
            }
        }
        if (command == '2') {
            T key;
            std::cout << "input element: ";
            std::cin >> key;
            heap.removeByNumber(key);
        }
        if (command == '3') {
            int key;
            std::cout << "input key: ";
            std::cin >> key;
            heap.removeByIndex(key);
        }
        if (command == '4') {
            T key;
            std::cout << "input key: ";
            std::cin >> key;
            if (heap.find_bool(key)==1) cout<<"Branch exist"<<endl;
            else cout<<"Branch DO NOT exist"<<endl;
        }
    }
    return heap;
}




void MenuHeap() {
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
        UI_H<int>(false);
    }
    if (command == '2') {
        UI_H<double>(false);
    }

    if (command == '3') {
        UI_H<string>(false);
    }

    if (command == '4') {
        UI_H<complex<double>>(false);
    }

}


void Choose() {
    cout<<"Heap - 1 or Tree - 0?"<<endl;
    cout<<"Your choice: ";
    char choice;
    cin>>choice;
    if (choice == '1') {
        MenuHeap();
    }
    if (choice == '0') {
        MenuTree();
    }

}