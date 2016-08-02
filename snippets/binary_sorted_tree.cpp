#define BOOST_TEST_MODULE sorted array tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "binary_sorted_tree.h"

BOOST_AUTO_TEST_CASE(init)
{
    BinarySortedTree<int, 16> t;
    BOOST_CHECK_EQUAL(0, t.size);
}

BOOST_AUTO_TEST_CASE(push_1)
{
    BinarySortedTree<int, 16> t;
    auto n = t.push(42);
    BOOST_CHECK_EQUAL(1, t.size);
    BOOST_CHECK_EQUAL(n, t.nodes);
    BOOST_CHECK_EQUAL(n, t.root);
    BOOST_REQUIRE(n);
    BOOST_CHECK(!n->l);
    BOOST_CHECK(!n->r);
    BOOST_CHECK_EQUAL(42, n->value);
}

BOOST_AUTO_TEST_CASE(push_5)
{
    BinarySortedTree<int, 16> t;
    auto n5 = t.push(5);
    auto n3 = t.push(3);
    auto n7 = t.push(7);
    auto n1 = t.push(1);
    auto n9 = t.push(9);
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
    BOOST_CHECK_EQUAL(5, t.nodes[0].value);
    BOOST_CHECK_EQUAL(3, t.nodes[1].value);
    BOOST_CHECK_EQUAL(7, t.nodes[2].value);
    BOOST_CHECK_EQUAL(1, t.nodes[3].value);
    BOOST_CHECK_EQUAL(9, t.nodes[4].value);
    BOOST_CHECK_EQUAL(n5, t.root);
    BOOST_CHECK_EQUAL(n3, n5->l);
    BOOST_CHECK_EQUAL(n7, n5->r);
    BOOST_CHECK_EQUAL(n1, n3->l);
    BOOST_CHECK(!n3->r);
    BOOST_CHECK(!n7->l);
    BOOST_CHECK_EQUAL(n9, n7->r);
}

BOOST_AUTO_TEST_CASE(floor_check) {
    BinarySortedTree<int, 16> t;
    BOOST_CHECK(!t.floor(6));

    t.push(5);
    BOOST_CHECK(!t.floor(4));
    BOOST_CHECK(t.floor(5));
    BOOST_CHECK_EQUAL(5, t.floor(5)->value);
    BOOST_CHECK(t.floor(6));
    BOOST_CHECK_EQUAL(5, t.floor(6)->value);

    t.push(3);
    BOOST_CHECK(!t.floor(2));
    BOOST_CHECK(t.floor(4));
    BOOST_CHECK_EQUAL(3, t.floor(4)->value);
    BOOST_CHECK(t.floor(6));
    BOOST_CHECK_EQUAL(5, t.floor(6)->value);

    t.push(7);
    BOOST_CHECK(!t.floor(2));
    BOOST_CHECK(t.floor(4));
    BOOST_CHECK_EQUAL(3, t.floor(4)->value);
    BOOST_CHECK(t.floor(6));
    BOOST_CHECK_EQUAL(5, t.floor(6)->value);
    BOOST_CHECK(t.floor(7));
    BOOST_CHECK_EQUAL(7, t.floor(7)->value);
    BOOST_CHECK(t.floor(8));
    BOOST_CHECK_EQUAL(7, t.floor(8)->value);

    t.push(10);
    BOOST_CHECK(!t.floor(2));
    BOOST_CHECK(t.floor(4));
    BOOST_CHECK_EQUAL(3, t.floor(4)->value);
    BOOST_CHECK(t.floor(6));
    BOOST_CHECK_EQUAL(5, t.floor(6)->value);
    BOOST_CHECK(t.floor(6));
    BOOST_CHECK_EQUAL(5, t.floor(6)->value);
    BOOST_CHECK(t.floor(8));
    BOOST_CHECK_EQUAL(7, t.floor(8)->value);
    BOOST_CHECK(t.floor(9));
    BOOST_CHECK_EQUAL(7, t.floor(9)->value);
    BOOST_CHECK(t.floor(10));
    BOOST_CHECK_EQUAL(10, t.floor(10)->value);
}

BOOST_AUTO_TEST_CASE(ceil_check) {
    BinarySortedTree<int, 16> t;
    BOOST_CHECK(!t.ceil(6));

    t.push(5);
    BOOST_CHECK(t.ceil(5));
    BOOST_CHECK_EQUAL(5, t.ceil(5)->value);
    BOOST_CHECK(t.ceil(4));
    BOOST_CHECK_EQUAL(5, t.ceil(4)->value);
    BOOST_CHECK(!t.ceil(6));

    t.push(3);
    BOOST_CHECK(t.ceil(2));
    BOOST_CHECK_EQUAL(3, t.ceil(2)->value);
    BOOST_CHECK(t.ceil(4));
    BOOST_CHECK_EQUAL(5, t.ceil(4)->value);
    BOOST_CHECK(!t.ceil(6));

    t.push(7);
    BOOST_CHECK(t.ceil(2));
    BOOST_CHECK_EQUAL(3, t.ceil(2)->value);
    BOOST_CHECK(t.ceil(4));
    BOOST_CHECK_EQUAL(5, t.ceil(4)->value);
    BOOST_CHECK(t.ceil(6));
    BOOST_CHECK_EQUAL(7, t.ceil(6)->value);
    BOOST_CHECK(t.ceil(7));
    BOOST_CHECK_EQUAL(7, t.ceil(7)->value);
    BOOST_CHECK(!t.ceil(8));

    t.push(10);
    BOOST_CHECK(t.ceil(2));
    BOOST_CHECK_EQUAL(3, t.ceil(2)->value);
    BOOST_CHECK(t.ceil(4));
    BOOST_CHECK_EQUAL(5, t.ceil(4)->value);
    BOOST_CHECK(t.ceil(6));
    BOOST_CHECK_EQUAL(7, t.ceil(6)->value);
    BOOST_CHECK(t.ceil(7));
    BOOST_CHECK_EQUAL(7, t.ceil(7)->value);
    BOOST_CHECK(t.ceil(8));
    BOOST_CHECK_EQUAL(10, t.ceil(8)->value);
    BOOST_CHECK(t.ceil(9));
    BOOST_CHECK_EQUAL(10, t.ceil(9)->value);
    BOOST_CHECK(t.ceil(10));
    BOOST_CHECK_EQUAL(10, t.ceil(10)->value);
    BOOST_CHECK(!t.ceil(11));
}

BOOST_AUTO_TEST_CASE(check_depth) {
    BinarySortedTree<int, 16> t;
    BOOST_CHECK_EQUAL(0, t.depth);
    t.push(5);
    BOOST_CHECK_EQUAL(1, t.depth);
    t.push(3);
    BOOST_CHECK_EQUAL(2, t.depth);
    t.push(7);
    BOOST_CHECK_EQUAL(2, t.depth);
    t.push(1);
    BOOST_CHECK_EQUAL(3, t.depth);
    t.push(6);
    BOOST_CHECK_EQUAL(3, t.depth);
    t.push(9);
    BOOST_CHECK_EQUAL(3, t.depth);
    t.push(8);
    BOOST_CHECK_EQUAL(4, t.depth);
}
