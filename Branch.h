
#ifndef TREE_BRANCH_H
#define TREE_BRANCH_H
#pragma once
#include <algorithm>
#include<list>
#include <stack>
#include <iterator>
#include <iostream>
#include <string>
#include<functional>
#include<cmath>
#include <complex>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;


template<typename T>
struct Branch
{
    T key;
    Branch<T>* left;
    Branch<T>* right;
};



template<typename T> void add(Branch<T>*& branch, const T key) {
    if (!branch) {
        branch = new Branch<T>;
        branch->key = key;
        branch->left = 0;
        branch->right = 0;
        return;
    }
    else {
        if (branch->key > key) {
            add(branch->left, key);
        }
        else {
            add(branch->right, key);
        }
    }
}



template<typename T> void remove(Branch<T>*& branch, T key) {
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


template<typename T> Branch<T>* find(Branch<T>*& branch, T key) {
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

//copy
template <typename T> void copy(const Branch<T>* s_branch, Branch<T>*& _branch) {
    if (!s_branch) return;
    _branch = new Branch<T>;
    _branch->key = s_branch->key;
    _branch->left = 0;
    _branch->right = 0;
    copy(s_branch->left, _branch->left);
    copy(s_branch->right, _branch->right);
    return;
}




template <typename T>
void mapp(vector<T>* array, Branch<T>*& branch, T (*func)(T)) {
    if (!branch) return;
    mapp(array, branch->left, func);
    array->push_back(func(branch->key));
    mapp(array, branch->right, func);
}




template <typename T> void where(int(*func)(T), Branch<T>*& branch) {
    if (!func(branch->key)) {
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


template <typename T> void tothread(Branch<T>*& branch, list<Branch<T>>* list, string method) {
    using pair = pair<Branch<T> *, bool>;
    stack<pair> stack;
    stack.push(pair{branch, false});
    string round_name = method;
    reverse(round_name.begin(), round_name.end());
    while (!stack.empty()) {
        pair current_node = stack.top();
        stack.pop();
        if (current_node.second)
            list->push_back(*current_node.first);
        else {
            if (current_node.first == nullptr)
                continue;
            for (auto ch : round_name)
                switch (ch) {
                    case 'N':
                        stack.push(pair{current_node.first, true});
                        break;
                    case 'L':
                        stack.push(pair{current_node.first->left, false});
                        break;
                    case 'R':
                        stack.push(pair{current_node.first->right, false});
                        break;
                }
        }
    }
}


template<typename T> Branch<T>* findparent(Branch<T>*& branch, T key) {
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


//GET KEY
template <typename T> T GetKey(Branch<T>* branch) {
    if (branch) {
        return branch->key;
    }
    else {
        return 0;
    }
} //Helper func to gey a key


//IS BALANCED
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


#endif //TREE_BRANCH_H