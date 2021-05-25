//
// Created by fokus on 16.05.2021.
/*
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BinTree.h"

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

//
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
/*
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
/*
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
/*
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
        REQUIRE(tree.toString("NLR")=="(0, 50), (1, 45), (2, 48), (3, 55), (4, 53), (5, 77), (6, 90), (7, 100), (8, 110)");
    }
    SECTION("NRL") {
        REQUIRE(tree.toString("NRL")=="(0, 50), (1, 55), (2, 77), (3, 90), (4, 100), (5, 110), (6, 53), (7, 45), (8, 48)");
    }
    SECTION("RNL") {
        REQUIRE(tree.toString("RNL")=="(0, 110), (1, 100), (2, 90), (3, 77), (4, 55), (5, 53), (6, 50), (7, 48), (8, 45)");
    }
    SECTION("RLN") {
        REQUIRE(tree.toString("RLN")=="(0, 110), (1, 100), (2, 90), (3, 77), (4, 53), (5, 55), (6, 48), (7, 45), (8, 50)");
    }
    SECTION("LNR") {
        REQUIRE(tree.toString("LNR")=="(0, 45), (1, 48), (2, 50), (3, 53), (4, 55), (5, 77), (6, 90), (7, 100), (8, 110)");
    }
    SECTION("LRN") {
        REQUIRE(tree.toString("LRN")=="(0, 48), (1, 45), (2, 53), (3, 110), (4, 100), (5, 90), (6, 77), (7, 55), (8, 50)");
    }
}

TEST_CASE("BALANCING") {
    BinTree<int> tree = maketree();
    REQUIRE(tree.IsBalanced()==0);
    tree.Balancing();
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
/*
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


    string RLN = "2 4 3 7 9 8 5";
    tree = toTree<int>(RLN, "LRN");
    REQUIRE(tree.toString("LRN")==RLN);



}
*/