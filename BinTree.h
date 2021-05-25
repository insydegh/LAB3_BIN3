
#ifndef TREE_BINTREE_H
#define TREE_BINTREE_H
#include "Branch.h"

template<typename T>
class BinTree {

    struct Trunk
    {
        Trunk *prev;
        string str;

        Trunk(Trunk *prev, string str) {
            this->prev = prev;
            this->str = str;
        }
    };

    void showTrunks(Trunk *p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        cout << p->str;

    }


    void printTree(Branch<T>* root, Trunk *prev, bool isLeft)
    {
        if (root == nullptr) {
            return;
        }

        string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);

        printTree(root->right, trunk, false);

        if (!prev) {
            trunk->str = "---";
        }
        else if (isLeft)
        {
            trunk->str = "`---";
            prev->str = prev_str;

        }
        else {
            trunk->str = ".---";
            prev_str = "   |";
        }

        showTrunks(trunk);
        cout << root->key<<endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, true);
    }


public:
    //Constructors
    BinTree(); //Create 0 tree
    BinTree(const T& key); //Create tree with only a root
    BinTree(const BinTree<T>& bintree);

    //Basic funcs
    void Add(const T key);
    void Remove(T key);
    bool Find(T key);

    //Map Where Reduce
    BinTree<T> Map(T(*func)(T));
    BinTree<T> Where(int(*func)(T));
    T Reduce(T(*func)(T, T), T start);

    //Balancing
    void CreateList();
    //void Balancing();
    void newBalancing();

    //GetSubtree
    BinTree<T> GetSubTree(T key);
    
    //FindSubTree
    bool FindSubTree(BinTree<T> sub_tree);

    //Threading
    list<Branch<T>>* Threading(string method = "LNR");

    //To string
    string toString(string method = "LNR");

    //Print
    void Print();

    //Other helping func for tests
    Branch<T>* give_root();
    Branch<T>* find_branch(T key);
    bool IsBalanced();

    //Destructor
    ~BinTree();

private:
    Branch<T>* root;

    //Helping funcs hidden for user
    Branch<T>* ShowParent(T key); //Show parent of the branch
    //void fromTreeToVine(); //Making a right vine from a tree (every branch has only right child)
    void MakeRotations(int count); //Func to make defined number of left rotations
    void RotateLeft(Branch<T>* parent); //Left rotate
    void RotateRight(Branch<T>* parent);//Right Rotate
};






//CONSTRUCTORS
template<typename T>
BinTree<T>::BinTree() {
    root = 0;
}

template<typename T>
BinTree<T>::BinTree(const T &key) {
    root = new Branch<T>;
    root->key = key;
    root->left = 0;
    root->right = 0;
}

template<typename T>
BinTree<T>::BinTree(const BinTree<T> &bintree) :BinTree() {
    copy(bintree.root, root);
    //Copying trees
}


//BASIC FUNCS
//Add
template<typename T> void BinTree<T>::Add(const T key) {
    add(root, key);
}

//Remove
template<typename T> void BinTree<T>::Remove(T key) {
    if (!root) {
        return;
    }
    remove(root, key);
}

//FIND
template<typename T> bool BinTree<T>::Find(T key) {
    if (!root) {
        cout << "Tree doesn't exist" <<endl;
        return false;
    }
    else {
        Branch<T>* temp= find(root,key);
        if (!temp)
            return false;
        else
            return true;

    }
}



//WHERE
template<typename T> BinTree<T> BinTree<T>::Where(int (*func)(T)) {
    BinTree<T> binTree = BinTree();
    if (!root) {
        return binTree;
    }
    copy(root, binTree.root);
    where(func, binTree.root);
    return binTree;
}


//REDUCE
template<typename T> T BinTree<T>::Reduce(T (*func)(T, T),  T start) {
    if (!root) {
        return 0;
    }
    list<Branch<T>>* list=this->Threading();
    T result;
    auto list_front = list->begin();
    result = func(list_front->key, start);
    advance(list_front,1);
    for (size_t i = 1; i < list->size(); i++) {
        result = func(list_front->key, result);
        advance(list_front, 1);
    }
    return result;
}


//THREADING
template<typename T> list<Branch<T>> *BinTree<T>::Threading(string method) {
    list<Branch<T>> *list =new ::list<Branch<T>>;
    if (!root) {
        return list;
    }
    tothread(root, list, method);
    return list;
}

/*
//BALANCING
template<typename T> void BinTree<T>::Balancing() {
    if (this->IsBalanced()==1) {return;}
    this->fromTreeToVine();
    int n = 0;
    for (Branch<T>* tmp = this->root; tmp != nullptr; tmp = tmp->right)
        n++;
    //m = 2^floor[log2(n+1)]-1
    int m = (1 << int(log2(n + 1))) - 1;
    this->MakeRotations(n - m);
    while (m > 1)
        this->MakeRotations(m /= 2);

}
*/

//NEW BALANCING
template<typename T>
void BinTree<T>::newBalancing() {
    if (this->IsBalanced()==1) {return;}
    this->CreateList();
    int n = 0;
    for (Branch<T>* tmp = this->root; tmp != nullptr; tmp = tmp->right)
        n++;
    //m = 2^floor[log2(n+1)]-1
    int m = (1 << int(log2(n + 1))) - 1;
    this->MakeRotations(n - m);
    while (m > 1)
        this->MakeRotations(m /= 2);
}

template<typename T>
void BinTree<T>::CreateList() {
    Branch<T>* parent = this->root;
    while (parent != nullptr) {
        if (parent->left != nullptr) {
            this->RotateRight(parent);
            Branch<T>* newparent = this->ShowParent(parent->key);
            parent = newparent;
        }
        else {
            parent = parent->right;
        }
    }
}

/*
template<typename T> void BinTree<T>::fromTreeToVine() {
    BinTree<T>* newTree =new BinTree<T>();
    list<Branch<T>>* list = this->Threading("LNR");
    auto list_front = list->begin();
    newTree->Add(list_front->key);
    for (int i =1; i<list->size(); i++) {
        advance(list_front,1);
        newTree->Add(list_front->key);
    }
    this->root = newTree->root;
    delete list;
}
*/

template<typename T> void BinTree<T>::MakeRotations(int count) {
    Branch<T>* parent = this->root;
    Branch<T>* child = this->root->right;
    for (; count > 0; count--)
    {
        if (child != nullptr)
        {
            this->RotateLeft(parent);
            parent = child->right;
            if (parent == nullptr)
                break;
            child = parent->right;
        }
        else
            break;
    }
}

template<typename T> void BinTree<T>::RotateLeft(Branch<T> *parent) {
    Branch<T>* right_child = parent->right;
    if (this->ShowParent(parent->key) != nullptr) {
        this->ShowParent(parent->key)->right = right_child;
    }
    else
        this->root = right_child;
    parent->right = right_child->left;
    right_child->left = parent;
}


template<typename T>
void BinTree<T>::RotateRight(Branch <T> *parent) {
    Branch<T>* left_child = parent->left;
    if (this->ShowParent(parent->key) != nullptr) {
        this->ShowParent(parent->key)->right= left_child;
    }
    else
        this->root = left_child;
    parent->left = left_child->right;
    left_child->right = parent;
}


//SHOWPARENT
template<typename T> Branch<T> *BinTree<T>::ShowParent(T key) {
    if (key == root->key){
        return NULL;
    }
    else return findparent(root,key);
}


//GETSUBTREE
template<typename T> BinTree<T> BinTree<T>::GetSubTree(T key) {
    BinTree<T> binTree = BinTree<T>();
    if (!root) {
        return binTree;
    }
    copy(find(root, key), binTree.root);
    return binTree;
}


//FINDSUBTREE
template<typename T> bool BinTree<T>::FindSubTree(BinTree<T> sub_tree) {
    return isSubtree(root, sub_tree.root);
}


//TO STRING
//OVERLOADING FUNCS
inline string
to_string(complex<double> __val)
{ string str;
    str= str+to_string(__val.real()) + " " + to_string(__val.imag());
    return str;
}

inline string
to_string(string __val)
{
    return __val;
}


template<typename T> string BinTree<T>::toString(string method) {
    string str;
    if (!root) {
        std::cout << "Tree is empty" << std::endl;
        return str;
    }
    list<Branch<T>>* list = this->Threading(method);
    auto list_front = list->begin();
    for (int i = 0; i < list->size(); i++) {
        str += to_string(list_front->key);
        if (i < list->size() - 1) {
            str += " ";
        }
        advance(list_front, 1);
    }
    return str;
}

//PRINT
template<typename T>
void BinTree<T>::Print()  {
    if (!root) {
        cout << "Tree is empty" << std::endl;
        return;
    }
    cout << "_________________Tree_Keys:_______________" << std::endl;
    printTree(root, nullptr, false);
}

//HELPERS
template<typename T>
Branch<T> *BinTree<T>::give_root() {
    return root;
}; //Return root

template<typename T>
Branch<T> *BinTree<T>::find_branch(T key) {
    return find(root, key);
} //Find a branch by key

template<typename T>
bool BinTree<T>::IsBalanced(){
    return is_balanced(root);
} //Checks if the tree is balanced

//Destructor
template<typename T>
BinTree<T>::~BinTree() {}







#endif //TREE_BINTREE_H



