//
// Created by fokus on 05.05.2021.
//
#include<functional>
#include<cmath>
#ifndef TREE_BINTREE_H
#define TREE_BINTREE_H
#endif //TREE_BINTREE_H
#pragma once
#include "algorithm"
#include<list>
#include <stack>
#include <iterator>
#include <iostream>
#include <string>
using namespace std;


template<typename T>
struct Branch
{
    T data;
    int key;
    Branch<T>* left;
    Branch<T>* right;
};


template<typename T>
class BinTree {
    struct Trunk
    {
        Trunk *prev;
        string str;

        Trunk(Trunk *prev, string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };
// Helper function to print branches of the binary tree
    void showTrunks(Trunk *p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        cout << p->str;

    }
// Recursive function to print a binary tree.
// It uses the inorder traversal.
    void printTree(Branch<T>* root, Trunk *prev, bool isLeft, string type)
    {
        if (root == nullptr) {
            return;
        }

        string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);

        printTree(root->right, trunk, false, type);

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


        if (type=="data")
            cout << root->data << endl;
        if (type=="key")
            cout << root->key<<endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, true, type);
    }

public:

    BinTree(){
        root = 0;
    }; //Create 0 tree

    BinTree(const T& item) {
        root = new Branch<T>;
        root->data = item;
        root->left = 0;
        root->right = 0;
    } //Create tree with only a root

    BinTree(const BinTree<T>& bintree) : BinTree() {
        copy(bintree.root, root);
    } //Copying trees

    //Basic funcs
    void Add(const T& data, int key);
    void Remove(int key);
    T Find(int key);

    //Map Where Reduce
    BinTree<T> Map(T(*func)(T));
    BinTree<T> Where(int(*func)(T));
    T Reduce(T(*func)(T, T), T start);

    //Balancing
    void Balancing();

    //GetSubtree
    BinTree<T> GetSubTree(int key);
    
    //FindSubTree
    bool FindSubTree(BinTree<T> sub_tree);

    //Threading
    list<Branch<T>>* Threading(string method = "LNR");

    //To string
    string toString(string method = "LNR");

    //Print
    void Print() {
        if (!root) {
            cout << "Tree is empty" << std::endl;
            return;
        }
        cout << "_________________Tree_Data:_______________" << std::endl;
        printTree(root, nullptr, false, "data");
        cout << "_________________Tree_Keys:_______________" << std::endl;
        printTree(root, nullptr, false, "key");
    }

    //Other helping func for tests
    Branch<T>* give_root() {
        return root;
    }; //Return root
    Branch<T>* find_branch(int key) {
        return find(root, key);
    } //Find a branch by key
    bool IsBalanced(){
        return is_balanced(root);
    } //Checks if the tree is balanced

    //Destructor
    ~BinTree(){};

private:
    Branch<T>* root;

    //Helping funcs hidden for user
    Branch<T>* ShowParent(int key); //Show parent of the branch
    void fromTreeToVine(); //Making a right vine from a tree (every branch has only right child)
    void MakeRotations(int count); //Func to make defined number of left rotations
    void RotateLeft(Branch<T>* parent); //Left rotate
};


template<typename T> void BinTree<T>::Add(const T &data, int key) {
    add(root, data, key);
}

template<typename T> void add(Branch<T>*& branch, const T& data, int key) {
    if (!branch) {
        branch = new Branch<T>;
        branch->data = data;
        branch->key = key;
        branch->left = 0;
        branch->right = 0;
        return;
    }
    else {
        if (branch->key > key) {
            add(branch->left, data, key);
        }
        else {
            add(branch->right, data, key);
        }
    }
}



template<typename T> void BinTree<T>::Remove(int key) {
    if (!root) {
        return;
    }
    remove(root, key);
}

template<typename T> void remove(Branch<T>*& branch, int key) {
    if (branch == NULL)
        return;

    if (key == branch->key) {

        Branch<T>* tempBranch;
        if (branch->right == NULL) {
            tempBranch = branch->left;
        }
        else {
            Branch<T>* ptr = branch->right;
            if (ptr->left == NULL) {
                ptr->left = branch->left;
                tempBranch = ptr;
            }
            else {

                Branch<T>* pmin = ptr->left;
                while (pmin->left != NULL) {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = branch->left;
                pmin->right = branch->right;
                tempBranch = pmin;
            }
        }

        delete branch;
        branch = tempBranch;
        return;
    }
    else if (key < branch->key)
        remove(branch->left, key);
    else
        remove(branch->right, key);
    return;
}



template<typename T> T BinTree<T>::Find(int key) {
    if (!root) {
        cout << "Tree doesn't exist" <<endl;
        return NULL;
    }
    else {
        Branch<T>* temp= find(root,key);
        if (!temp)
            return NULL;
        else {
            return temp->data;
        }
    }
}


template<typename T> Branch<T>* find(Branch<T>*& branch, int key) {
    if (branch == NULL)
        return NULL; // empty

    if (key == branch->key) {
        return branch;
    }
    else if (key < branch->key)
        find(branch->left, key);
    else
        find(branch->right, key);
}



template<typename T> BinTree<T> BinTree<T>::Map(T (*func)(T)) {
    BinTree<T> binTree = BinTree();
    if (!root) {
        return binTree;
    }
    copy(root, binTree.root);
    mapp(func, binTree.root);
    return binTree;
}

template <typename T> void mapp(T(*func)(T), Branch<T>* branch) {
    branch->data = func(branch->data);
    if (branch->left == nullptr && branch->right == nullptr) {
        return;
    }
    if (branch->left != nullptr) {
        mapp(func, branch->left);
    }
    if (branch->right != nullptr) {
        mapp(func, branch->right);
    }
}

template <typename T> void copy(const Branch<T>* s_branch, Branch<T>*& _branch) {
    if (!s_branch) return;
    _branch = new Branch<T>;
    _branch->data = s_branch->data;
    _branch->key = s_branch->key;
    _branch->left = 0;
    _branch->right = 0;
    copy(s_branch->left, _branch->left);
    copy(s_branch->right, _branch->right);
    return;
}



template<typename T> BinTree<T> BinTree<T>::Where(int (*func)(T)) {
    BinTree<T> binTree = BinTree();
    if (!root) {
        return binTree;
    }
    copy(root, binTree.root);
    where(func, binTree.root);
    return binTree;
}

template <typename T> void where(int(*func)(T), Branch<T>*& branch) {
    if (!func(branch->data)) {
        remove(branch, branch->key);
        if (!branch) return;
        where(func, branch);
        return;
    }

    if (branch->left == nullptr && branch->right == nullptr) {
        return;
    }
    if (branch->left != nullptr) {
        where(func, branch->left);
    }
    if (branch->right != nullptr) {
        where(func, branch->right);
    }
}



template<typename T> T BinTree<T>::Reduce(T (*func)(T, T),  T start) {
    if (!root) {
        return 0;
    }
    list<Branch<T>>* list=this->Threading();
    T result;
    auto list_front = list->begin();
    result = func(list_front->data, start);
    advance(list_front,1);
    for (size_t i = 1; i < list->size(); i++) {
        result = func(list_front->data, result);
        advance(list_front, 1);
    }
    return result;
}



template<typename T> list<Branch<T>> *BinTree<T>::Threading(string method) {
    list<Branch<T>> *list =new ::list<Branch<T>>;
    if (!root) {
        return list;
    }
    tothread(root, list, method);
    return list;
}

template <typename T> void tothread(Branch<T>*& branch, list<Branch<T>>* list, string method) {
    using pair = pair<Branch<T>*, bool>;
    stack<pair> stack;
    stack.push(pair{ branch, false });
    string round_name = method;
    reverse(round_name.begin(), round_name.end());
    while (!stack.empty())
    {
        pair current_node = stack.top();
        stack.pop();
        if (current_node.second)
            list->push_back(*current_node.first);
        else
        {
            if (current_node.first == nullptr)
                continue;
            for (auto ch : round_name)
                switch (ch)
                {
                    case 'N':
                        stack.push(pair{ current_node.first, true });
                        break;
                    case 'L':
                        stack.push(pair{ current_node.first->left, false });
                        break;
                    case 'R':
                        stack.push(pair{ current_node.first->right, false });
                        break;
                }
        }
    }
}



template<typename T> void BinTree<T>::Balancing() {
    if (this->IsBalanced()==1) {cout<<"Tree is already balanced"<<endl; return;}
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

template<typename T> void BinTree<T>::fromTreeToVine() {
    BinTree<T>* newTree =new BinTree<T>();
    list<Branch<T>>* list = this->Threading("LNR");
    auto list_front = list->begin();
    newTree->Add(list_front->data, list_front->key);
    for (int i =1; i<list->size(); i++) {
        advance(list_front,1);
        newTree->Add(list_front->data, list_front->key);
    }
    this->root = newTree->root;
    delete list;
}

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



template<typename T> Branch<T> *BinTree<T>::ShowParent(int key) {
    if (key == root->key){
        return NULL;
    }
    else return findparent(root,key);
}

template<typename T> Branch<T>* findparent(Branch<T>*& branch, int key) {
    if (branch == NULL) {
        return NULL; // empty
    }

    if (key == GetKey(branch->left) || key == GetKey(branch->right)) {
        return branch;
    }
    else if (key < branch->key) {
        findparent(branch->left, key);

    }
    else {
        findparent(branch->right, key);
    }
}



template<typename T> BinTree<T> BinTree<T>::GetSubTree(int key) {
    BinTree<T> binTree = BinTree<T>();
    if (!root) {
        return binTree;
    }
    copy(find(root, key), binTree.root);
    return binTree;
}



template<typename T> bool BinTree<T>::FindSubTree(BinTree<T> sub_tree) {
    return isSubtree(root, sub_tree.root);
}

template <typename T> bool areIdentical(Branch<T>* root1, Branch<T>* root2) {
    /* base cases */
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 != NULL && root2 != NULL) {
        if (root1->key == root2->key && areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right)) {
            return true;
        }

    }
    return false;

}

template <typename T> bool isSubtree(Branch<T>* branch, Branch<T>* sub_branch)
{
    /* base cases */
    if (sub_branch == NULL)
        return true;

    if (branch == NULL)
        return false;

    /* Check the tree with root as current node */
    if (areIdentical(branch, sub_branch))
        return true;

    /* If the tree with root as current
    node doesn't match then try left
    and right subtrees one by one */
    return isSubtree(branch->left, sub_branch) ||
           isSubtree(branch->right, sub_branch);
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
        str += "(" + to_string(i) + ", " + to_string(list_front->key) + ")";
        if (i < list->size() - 1) {
            str += ", ";
        }
        advance(list_front, 1);
    }
    return str;
}



template <typename T> int GetKey(Branch<T>* branch) {
    if (branch) {
        return branch->key;
    }
    else {
        return 0;
    }
} //Helper func to gey a key



template <typename T> int height(Branch<T>* node)
{
    /* base case tree is empty */
    if (node == NULL)
        return 0;

    /* If tree is not empty then
    height = 1 + max of left
        height and right heights */
    return 1 + max(height(node->left),
                   height(node->right));
}



template <typename T> bool is_balanced(Branch<T>* root)
{
    int lh; /* for height of left subtree */
    int rh; /* for height of right subtree */

    /* If tree is empty then return true */
    if (root == NULL)
        return 1;

    /* Get the height of left and right sub trees */
    lh = height(root->left);
    rh = height(root->right);

    if (abs(lh - rh) <= 1 && is_balanced(root->left) && is_balanced(root->right))
        return 1;

    /* If we reach here then
    tree is not height-balanced */
    return 0;
}


/*
template <typename T>
void ThreadPrint(list<Branch<T>>* list) {
    auto list_front = list->begin();
    for (int i = 0; i < list->size(); i++) {
        cout<<"key:"<<i<<" "<<"data:"<<list_front->data<<endl;
        advance(list_front, 1);
    }
}
*/