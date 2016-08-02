#define BOOST_TEST_MODULE sorted array tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "sorted_array.h"

static const int NMAX = 100001;
typedef int T;


BOOST_AUTO_TEST_CASE(find_0)
{
    T array[NMAX];
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 0, 1));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 0, 100));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 0, 100000));
}

BOOST_AUTO_TEST_CASE(find_1)
{
    T array[NMAX] = { 5 };
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 1, 1));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 1, 5));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 1, 6));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 1, 6000));
}

BOOST_AUTO_TEST_CASE(find_2)
{
    T array[NMAX] = { 1, 3 };
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 2, 1));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 2, 3));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 2, 2));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 2, 0));
    BOOST_CHECK_EQUAL(&array[2], sorted_array_find(array, 2, 4));
}

BOOST_AUTO_TEST_CASE(find_10)
{   // positions:     0  1  2  3  4   5   6   7   8   9  10
    T array[NMAX] = { 1, 3, 6, 6, 7, 10, 11, 11, 11, 16 };
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 10, 0));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_find(array, 10, 1));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 10, 2));
    BOOST_CHECK_EQUAL(&array[1], sorted_array_find(array, 10, 3));
    BOOST_CHECK_EQUAL(&array[2], sorted_array_find(array, 10, 4));
    BOOST_CHECK_EQUAL(&array[2], sorted_array_find(array, 10, 5));
    BOOST_CHECK_EQUAL(&array[3], sorted_array_find(array, 10, 6));
    BOOST_CHECK_EQUAL(&array[4], sorted_array_find(array, 10, 7));
    BOOST_CHECK_EQUAL(&array[5], sorted_array_find(array, 10, 8));
    BOOST_CHECK_EQUAL(&array[5], sorted_array_find(array, 10, 9));
    BOOST_CHECK_EQUAL(&array[5], sorted_array_find(array, 10, 10));
    BOOST_CHECK_EQUAL(&array[8], sorted_array_find(array, 10, 11));
    BOOST_CHECK_EQUAL(&array[9], sorted_array_find(array, 10, 12));
    BOOST_CHECK_EQUAL(&array[9], sorted_array_find(array, 10, 15));
    BOOST_CHECK_EQUAL(&array[9], sorted_array_find(array, 10, 16));
    BOOST_CHECK_EQUAL(&array[10], sorted_array_find(array, 10, 17));
}

BOOST_AUTO_TEST_CASE(insert_0)
{
    T array[NMAX];
    BOOST_CHECK_EQUAL(&array[0], sorted_array_push(array, 0, 1));
    BOOST_CHECK_EQUAL(array[0], 1);
}

BOOST_AUTO_TEST_CASE(insert_after)
{
    T array[NMAX] = { 5 };
    BOOST_CHECK_EQUAL(&array[1], sorted_array_push(array, 1, 6));
    BOOST_CHECK_EQUAL(&array[2], sorted_array_push(array, 2, 7));
    BOOST_CHECK_EQUAL(&array[3], sorted_array_push(array, 3, 8));
    BOOST_CHECK_EQUAL(&array[4], sorted_array_push(array, 4, 9));
    BOOST_CHECK_EQUAL(array[0], 5);
    BOOST_CHECK_EQUAL(array[1], 6);
    BOOST_CHECK_EQUAL(array[2], 7);
    BOOST_CHECK_EQUAL(array[3], 8);
    BOOST_CHECK_EQUAL(array[4], 9);
}

BOOST_AUTO_TEST_CASE(insert_before)
{
    T array[NMAX] = { 5 };
    BOOST_CHECK_EQUAL(&array[0], sorted_array_push(array, 1, 4));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_push(array, 2, 3));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_push(array, 3, 2));
    BOOST_CHECK_EQUAL(&array[0], sorted_array_push(array, 4, 1));
    BOOST_CHECK_EQUAL(array[0], 1);
    BOOST_CHECK_EQUAL(array[1], 2);
    BOOST_CHECK_EQUAL(array[2], 3);
    BOOST_CHECK_EQUAL(array[3], 4);
    BOOST_CHECK_EQUAL(array[4], 5);
}

BOOST_AUTO_TEST_CASE(insert_middle)
{
    T array[NMAX] = { 5, 7, 9 };
    BOOST_CHECK_EQUAL(&array[1], sorted_array_push(array, 3, 6));
    BOOST_CHECK_EQUAL(&array[3], sorted_array_push(array, 4, 8));
    BOOST_CHECK_EQUAL(array[0], 5);
    BOOST_CHECK_EQUAL(array[1], 6);
    BOOST_CHECK_EQUAL(array[2], 7);
    BOOST_CHECK_EQUAL(array[3], 8);
    BOOST_CHECK_EQUAL(array[4], 9);
}

BOOST_AUTO_TEST_CASE(insert_same)
{
    T array[NMAX] = { 5, 7, 9 };
    BOOST_CHECK_EQUAL(&array[2], sorted_array_push(array, 3, 7));
    BOOST_CHECK_EQUAL(&array[3], sorted_array_push(array, 4, 7));
    BOOST_CHECK_EQUAL(array[0], 5);
    BOOST_CHECK_EQUAL(array[1], 7);
    BOOST_CHECK_EQUAL(array[2], 7);
    BOOST_CHECK_EQUAL(array[3], 7);
    BOOST_CHECK_EQUAL(array[4], 9);
}

