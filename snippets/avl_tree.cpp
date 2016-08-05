#define BOOST_TEST_MODULE sorted array tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "avl_tree.h"

BOOST_AUTO_TEST_CASE(init)
{
    AvlTree<int, 16> t;
    BOOST_CHECK_EQUAL(0, t.size);
}

BOOST_AUTO_TEST_CASE(push_1)
{
    AvlTree<int, 16> t;
    auto n = t.insert(42);
    BOOST_CHECK_EQUAL(1, t.size);
    BOOST_CHECK_EQUAL(n, t.nodes);
    BOOST_CHECK_EQUAL(n, t.root);
    BOOST_REQUIRE(n);
    BOOST_CHECK(n->kids[0]->isnull());
    BOOST_CHECK(n->kids[1]->isnull());
    BOOST_CHECK_EQUAL(42, n->value);
}

BOOST_AUTO_TEST_CASE(push_5)
{
    AvlTree<int, 16> t;
    auto n5 = t.insert(5);
    auto n3 = t.insert(3);
    auto n7 = t.insert(7);
    auto n1 = t.insert(1);
    auto n9 = t.insert(9);
    BOOST_CHECK(n5);
    BOOST_CHECK(n3);
    BOOST_CHECK(n7);
    BOOST_CHECK(n1);
    BOOST_CHECK(n9);
    BOOST_CHECK_EQUAL(5, t.size);
    BOOST_CHECK_EQUAL(n5, &t.nodes[0]);
    BOOST_CHECK_EQUAL(n3, &t.nodes[1]);
    BOOST_CHECK_EQUAL(n7, &t.nodes[2]);
    BOOST_CHECK_EQUAL(n1, &t.nodes[3]);
    BOOST_CHECK_EQUAL(n9, &t.nodes[4]);
    BOOST_CHECK_EQUAL(5, n5->value);
    BOOST_CHECK_EQUAL(3, n3->value);
    BOOST_CHECK_EQUAL(7, n7->value);
    BOOST_CHECK_EQUAL(1, n1->value);
    BOOST_CHECK_EQUAL(9, n9->value);
    BOOST_CHECK_EQUAL(n5, t.root);
    BOOST_CHECK_EQUAL(n3, n5->kids[0]);
    BOOST_CHECK_EQUAL(n7, n5->kids[1]);
    BOOST_CHECK_EQUAL(n1, n3->kids[0]);
    BOOST_CHECK(n3->kids[1]->isnull());
    BOOST_CHECK(n7->kids[0]->isnull());
    BOOST_CHECK_EQUAL(n9, n7->kids[1]);
}

BOOST_AUTO_TEST_CASE(height)
{
    AvlTree<int, 16> t;
    auto n5 = t.insert(5);
    BOOST_CHECK_EQUAL(0, n5->height);
    auto n3 = t.insert(3);
    BOOST_CHECK_EQUAL(1, n5->height);
    BOOST_CHECK_EQUAL(0, n3->height);
    auto n7 = t.insert(7);
    BOOST_CHECK_EQUAL(1, n5->height);
    BOOST_CHECK_EQUAL(0, n3->height);
    BOOST_CHECK_EQUAL(0, n7->height);
    auto n1 = t.insert(1);
    BOOST_CHECK_EQUAL(2, n5->height);
    BOOST_CHECK_EQUAL(1, n3->height);
    BOOST_CHECK_EQUAL(0, n7->height);
    BOOST_CHECK_EQUAL(0, n1->height);
    auto n9 = t.insert(9);
    BOOST_CHECK_EQUAL(2, n5->height);
    BOOST_CHECK_EQUAL(1, n3->height);
    BOOST_CHECK_EQUAL(1, n7->height);
    BOOST_CHECK_EQUAL(0, n1->height);
    BOOST_CHECK_EQUAL(0, n9->height);
}

BOOST_AUTO_TEST_CASE(balance)
{
    AvlTree<int, 16> t;
    auto n5 = t.insert(5);               //     5 
    auto n3 = t.insert(3);               //    /  
    auto n1 = t.insert(1);               //   3   
    BOOST_CHECK_EQUAL(n1, n3->kids[0]);  //  /    
    BOOST_CHECK_EQUAL(n5, n3->kids[1]);  // 1     
    BOOST_CHECK(n1->kids[0]->isnull());  //       
    BOOST_CHECK(n1->kids[1]->isnull());  //   3   
    BOOST_CHECK(n5->kids[0]->isnull());  //  / \ .
    BOOST_CHECK(n5->kids[1]->isnull());  // 1   5 
    BOOST_CHECK_EQUAL(0, n1->height);
    BOOST_CHECK_EQUAL(0, n5->height);
    BOOST_CHECK_EQUAL(1, n3->height);

    auto n7 = t.insert(7);               //    3      
    auto n9 = t.insert(9);               //  1/ \5    
    BOOST_CHECK_EQUAL(n7, n3->kids[1]);  //       \7  
    BOOST_CHECK_EQUAL(n5, n7->kids[0]);  //         \9
    BOOST_CHECK_EQUAL(n9, n7->kids[1]);  //           
    BOOST_CHECK_EQUAL(0, n1->height);    //    3      
    BOOST_CHECK_EQUAL(0, n5->height);    //  1/ \7    
    BOOST_CHECK_EQUAL(0, n9->height);    //    5/ \9  
    BOOST_CHECK_EQUAL(1, n7->height);    //           
    BOOST_CHECK_EQUAL(2, n3->height);    //           

    auto n8 = t.insert(8);
    BOOST_CHECK_EQUAL(n7, t.root);
    BOOST_CHECK(n1->kids[0]->isnull());
    BOOST_CHECK(n1->kids[1]->isnull());
    BOOST_CHECK(n5->kids[0]->isnull());
    BOOST_CHECK(n5->kids[1]->isnull());
    BOOST_CHECK(n8->kids[0]->isnull());
    BOOST_CHECK(n8->kids[1]->isnull());
    BOOST_CHECK(n9->kids[1]->isnull());
    BOOST_CHECK_EQUAL(n3, n7->kids[0]);
    BOOST_CHECK_EQUAL(n9, n7->kids[1]);
    BOOST_CHECK_EQUAL(n1, n3->kids[0]);
    BOOST_CHECK_EQUAL(n5, n3->kids[1]);
    BOOST_CHECK_EQUAL(n8, n9->kids[0]);
    BOOST_CHECK_EQUAL(0, n1->height);
    BOOST_CHECK_EQUAL(0, n5->height);
    BOOST_CHECK_EQUAL(0, n8->height);
    BOOST_CHECK_EQUAL(1, n3->height);
    BOOST_CHECK_EQUAL(1, n9->height);
    BOOST_CHECK_EQUAL(2, n7->height);
}

