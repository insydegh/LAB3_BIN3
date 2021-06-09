//
// Created by fokus on 16.05.2021.

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Menu.h"

//create a tree
BinTree<int> maketree(){
    BinTree<int> tree = BinTree<int>();
    tree.Add(50);
    tree.Add(55);
    tree.Add(45);
    tree.Add(77);
    tree.Add(48);
    tree.Add(53);
    tree.Add(90);
    tree.Add(100);
    tree.Add(110);
    return tree;
}


int double_number(int x) {
    return x*2;
}
int (*f_map)(int) = &double_number;

int isBiggerThan(int x){
    return x>57 ? 1 : 0;
}
int (*f_where)(int) = &isBiggerThan;


int Summ(int x1, int x2){
    return 2*x1+x2;
}
int (*f_reduce)(int, int) = &Summ;



TEST_CASE("ADD") {
    BinTree<int> tree = maketree();
    /*
     _________________Tree:_______________
                              110
                         100
                    90
               77
          55
               53
     50
               48
          45

    */

    REQUIRE(GetKey(tree.give_root())==50);
    REQUIRE(GetKey(tree.give_root()->left)==45);
    REQUIRE(GetKey(tree.give_root()->right)==55);
    REQUIRE(GetKey(tree.give_root()->right->right)==77);
    REQUIRE(GetKey(tree.give_root()->right->left)==53);

    tree.Add(60);
    /*

                               110
                         100
                    90
               77
                    60
          55
               53
     50
               48
          45

    */

    REQUIRE(tree.find_branch(77)->left->key==60);
}


TEST_CASE("REMOVE") {
    BinTree<int> tree = maketree();
    tree.Remove(55);
    /*
                           110
                    100
               90
          77
               53
     50
               48
          45

     */

    REQUIRE(tree.give_root()->right->key==77);
    REQUIRE(tree.give_root()->right->left->key==53);
}

TEST_CASE("FIND") {
    BinTree<int> tree = maketree();
    REQUIRE(tree.Find(100)==1);
    REQUIRE(tree.Find(90)==1);
    REQUIRE(tree.Find(77)==1);
    REQUIRE(tree.Find(45)==1);
}


TEST_CASE("MAP") {
    BinTree<int> tree = maketree();
    BinTree<int> tree1 = tree.Map(f_map);
    //Multyplying by 2
    REQUIRE(tree1.find_branch(100));
    REQUIRE(tree1.find_branch(200));
    REQUIRE(tree1.find_branch(90));
    REQUIRE(tree1.find_branch(106));
}


TEST_CASE("WHERE") {
    BinTree<int> tree = maketree();
    //Is number bigger than 57?
    BinTree<int> tree1 = tree.Where(f_where);

    //                 110
    //           100
    //      90
    // 77

    REQUIRE(tree1.give_root()->key==77);
    REQUIRE(tree1.give_root()->right->key==90);
    REQUIRE(tree1.give_root()->right->right->key==100);
}

TEST_CASE("REDUCE") {

    BinTree<int> tree = maketree();
    //2X1+X2
    REQUIRE(tree.Reduce(f_reduce,10)==1266);
}

TEST_CASE("THREADING AND TO STRING") {
    BinTree<int> tree = maketree();
    SECTION("NLR") {
        REQUIRE(tree.toString("NLR")=="50 45 48 55 53 77 90 100 110");
    }
    SECTION("NRL") {
        REQUIRE(tree.toString("NRL")=="50 55 77 90 100 110 53 45 48");
    }
    SECTION("RNL") {
        REQUIRE(tree.toString("RNL")=="110 100 90 77 55 53 50 48 45");
    }
    SECTION("RLN") {
        REQUIRE(tree.toString("RLN")=="110 100 90 77 53 55 48 45 50");
    }
    SECTION("LNR") {
        REQUIRE(tree.toString("LNR")=="45 48 50 53 55 77 90 100 110");
    }
    SECTION("LRN") {
        REQUIRE(tree.toString("LRN")=="48 45 53 110 100 90 77 55 50");
    }
}

TEST_CASE("BALANCING") {
    BinTree<int> tree = maketree();
    REQUIRE(tree.IsBalanced()==0);
    tree.newBalancing();
    REQUIRE(tree.IsBalanced()==1);
    /*
                   110
          100
               90
     77
               55
          53
                    50
               48
                    45
     */

}

TEST_CASE("GET SUB TREE") {
    BinTree<int> tree = maketree();
    BinTree<int> tree1 = tree.GetSubTree(55);
    REQUIRE(tree1.give_root()->key==55);
    REQUIRE(tree1.give_root()->right->key==77);
    REQUIRE(tree1.give_root()->left->key==53);
}

TEST_CASE("FIND SUB TREE") {
    BinTree<int> tree = maketree();
    BinTree<int> tree1 = tree.GetSubTree(55);
    BinTree<int> tree2 = tree.GetSubTree(55);
    tree2.Add(44);
    REQUIRE(tree.FindSubTree(tree1)==1);
    REQUIRE(tree.FindSubTree(tree2)==0);
}


TEST_CASE("FROM STRING ") {
    string LNR = "2 3 4 5 7 8 9";
    BinTree<int> tree = toTree<int>(LNR, "LNR");
    REQUIRE(tree.toString("LNR")==LNR);
    string RNL = "9 8 7 5 4 3 2";
    tree = toTree<int>(RNL, "RNL");
    REQUIRE(tree.toString("RNL")==RNL);

    string NRL = "5 3 2 4 8 7 9";
    tree = toTree<int>(NRL, "NLR");
    REQUIRE(tree.toString("NLR")==NRL);


    string LRN = "2 4 3 7 9 8 5";
    tree = toTree<int>(LRN, "LRN");
    REQUIRE(tree.toString("LRN")==LRN);
}

TEST_CASE("Z_HEAP_ADD") {
    Heap<int> heap = Heap<int>();
    heap.insertNode(23);
    heap.insertNode(56);
    heap.insertNode(33);
    heap.insertNode(21);
    heap.insertNode(78);
    heap.insertNode(2);
    REQUIRE(heap.find_array(0)==78);
    REQUIRE(heap.find_array(1)==56);
    REQUIRE(heap.find_array(2)==33);
    REQUIRE(heap.find_array(3)==21);
    REQUIRE(heap.find_array(4)==23);
    heap.insertNode(55);
    REQUIRE(heap.find_array(2)==55);
    REQUIRE(heap.find_array(1)==56);
    REQUIRE(heap.find_array(3)==21);
    heap.insertNode(100);
    REQUIRE(heap.find_array(0)==100);
    REQUIRE(heap.find_array(1)==78);
    REQUIRE(heap.find_array(2)==55);
}

TEST_CASE("Z_HEAP_REMOVE") {
    Heap<int> heap = Heap<int>();
    heap.insertNode(23);
    heap.insertNode(56);
    heap.insertNode(33);
    heap.insertNode(21);
    heap.insertNode(78);
    heap.insertNode(2);
    heap.removeByNumber(78);
    REQUIRE(heap.find_array(0)==56);
    REQUIRE(heap.find_array(1)==23);
    heap.removeByIndex(2);
    REQUIRE(heap.find_array(2)==2);

}

TEST_CASE("Z_HEAP FIND") {
    Heap<int> heap = Heap<int>();
    heap.insertNode(23);
    heap.insertNode(56);
    heap.insertNode(33);
    heap.insertNode(21);
    heap.insertNode(78);
    heap.insertNode(2);
    REQUIRE(heap.find_bool(23)==true);
    REQUIRE(heap.find_bool(56)==true);
    REQUIRE(heap.find_bool(122)==false);

}