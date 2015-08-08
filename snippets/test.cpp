#include "structs.h"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(stack) {
    Stack s;
    BOOST_CHECK_EQUAL(s.size, 0);
    BOOST_CHECK_EQUAL(s.find(0), -1);
    BOOST_CHECK_THROW(s.pop(), Exc);
    COUT << "Stack #1 - "; s.print(); COUT << std::endl;

    s.push(10);
    s.push(20);
    s.push(30);
    BOOST_CHECK_EQUAL(s.size, 3);
    BOOST_CHECK_EQUAL(s.data[0], 10);
    BOOST_CHECK_EQUAL(s.data[1], 20);
    BOOST_CHECK_EQUAL(s.data[2], 30);
    BOOST_CHECK_EQUAL(s.find(0), -1);
    BOOST_CHECK_EQUAL(s.find(10), 0);
    BOOST_CHECK_EQUAL(s.find(20), 1);
    BOOST_CHECK_EQUAL(s.find(30), 2);
    COUT << "Stack #2 - "; s.print(); COUT << std::endl;

    BOOST_CHECK_EQUAL(s.pop(), 30);
    BOOST_CHECK_EQUAL(s.size, 2);
    BOOST_CHECK_EQUAL(s.pop(), 20);
    BOOST_CHECK_EQUAL(s.size, 1);
    BOOST_CHECK_EQUAL(s.pop(), 10);
    BOOST_CHECK_EQUAL(s.size, 0);
    BOOST_CHECK_THROW(s.pop(), Exc);
    COUT << "Stack #3 - "; s.print(); COUT << std::endl;

    s.push(1); s.push(11);
    s.push(21); s.push(31);
    s.push(41); s.push(51);
    s.push(61); s.push(71);
    s.push(81); s.push(91); 
    BOOST_CHECK_THROW(s.push(101), Exc);
    BOOST_CHECK_EQUAL(s.size, 10);
    BOOST_CHECK_EQUAL(s.data[0], 1);
    BOOST_CHECK_EQUAL(s.data[1], 11);
    BOOST_CHECK_EQUAL(s.data[2], 21);
    BOOST_CHECK_EQUAL(s.find(10), -1);
    BOOST_CHECK_EQUAL(s.find(31), 3);
    BOOST_CHECK_EQUAL(s.find(41), 4);
    BOOST_CHECK_EQUAL(s.find(51), 5);
    COUT << "Stack #4 - "; s.print(); COUT << std::endl;

    BOOST_CHECK_EQUAL(s.pop(), 91);
    BOOST_CHECK_EQUAL(s.pop(), 81);
    BOOST_CHECK_EQUAL(s.pop(), 71);
    BOOST_CHECK_EQUAL(s.size, 7);
    COUT << "Stack #5 - "; s.print(); COUT << std::endl;
}

BOOST_AUTO_TEST_CASE(queue) {
    Queue q;

    COUT << "Queue #0 - "; q.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(q.size, 0);
    BOOST_CHECK_EQUAL(q.find(0), -1);
    BOOST_CHECK_THROW(q.pop(), Exc);
    q.push(10);
    q.push(20);
    q.push(30);
    COUT << "Queue #1 - "; q.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(q.size, 3);
    BOOST_CHECK_EQUAL(q.get(0), 10);
    BOOST_CHECK_EQUAL(q.get(1), 20);
    BOOST_CHECK_EQUAL(q.get(2), 30);
    BOOST_CHECK_EQUAL(q.find(0), -1);
    BOOST_CHECK_EQUAL(q.find(10), 0);
    BOOST_CHECK_EQUAL(q.find(20), 1);
    BOOST_CHECK_EQUAL(q.find(30), 2);
    BOOST_CHECK_EQUAL(q.pop(), 10);
    BOOST_CHECK_EQUAL(q.size, 2);
    BOOST_CHECK_EQUAL(q.pop(), 20);
    BOOST_CHECK_EQUAL(q.size, 1);
    BOOST_CHECK_EQUAL(q.pop(), 30);
    BOOST_CHECK_EQUAL(q.size, 0);
    BOOST_CHECK_THROW(q.pop(), Exc);
    COUT << "Queue #2 - "; q.print(); COUT << std::endl;
    q.push(1); q.push(11);
    q.push(21); q.push(31);
    q.push(41); q.push(51);
    q.push(61); q.push(71);
    q.push(81); q.push(91); 
    COUT << "Queue #3 - "; q.print(); COUT << std::endl;
    BOOST_CHECK_THROW(q.push(101), Exc);
    BOOST_CHECK_EQUAL(q.size, 10);
    BOOST_CHECK_EQUAL(q.get(0), 1);
    BOOST_CHECK_EQUAL(q.get(1), 11);
    BOOST_CHECK_EQUAL(q.get(8), 81);
    BOOST_CHECK_EQUAL(q.get(9), 91);
    BOOST_CHECK_EQUAL(q.find(10), -1);
    BOOST_CHECK_EQUAL(q.find(31), 3);
    BOOST_CHECK_EQUAL(q.find(41), 4);
    BOOST_CHECK_EQUAL(q.find(51), 5);
    BOOST_CHECK_EQUAL(q.pop(),  1);
    BOOST_CHECK_EQUAL(q.pop(), 11);
    BOOST_CHECK_EQUAL(q.pop(), 21);
    BOOST_CHECK_EQUAL(q.size, 7);
    COUT << "Queue #4 - "; q.print(); COUT << std::endl;
}

BOOST_AUTO_TEST_CASE(list) {
    List l;
    COUT << "List #0 - "; l.print(); COUT << std::endl;
    List::Node* n = l.insert(10, NULL);
    n = l.insert(20, n);
    n = l.insert(30, n);
    COUT << "List #1 - "; l.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(l.size, 3);
    BOOST_CHECK(l.find(10) != NULL);
    BOOST_CHECK(l.find(20) != NULL);
    BOOST_CHECK(l.find(30) != NULL);
    BOOST_CHECK(!l.remove(n+1));
    BOOST_CHECK(l.remove(l.find(20)));
    COUT << "List #2 - "; l.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(l.size, 2);
    BOOST_CHECK(l.find(10) != NULL);
    BOOST_CHECK(l.find(20) == NULL);
    BOOST_CHECK(l.find(30) != NULL);
    BOOST_CHECK(l.remove(l.find(10)));
    COUT << "List #3 - "; l.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(l.size, 1);
    BOOST_CHECK(l.find(10) == NULL);
    BOOST_CHECK(l.find(20) == NULL);
    BOOST_CHECK(l.find(30) != NULL);
    BOOST_CHECK(l.remove(l.find(30)));
    COUT << "List #4 - "; l.print(); COUT << std::endl;
    BOOST_CHECK_EQUAL(l.size, 0);
    BOOST_CHECK(l.find(10) == NULL);
    BOOST_CHECK(l.find(20) == NULL);
    BOOST_CHECK(l.find(30) == NULL);
}

BOOST_AUTO_TEST_CASE(sort) {
    int data[] = {10, 23, -1113, 232, 23, 984, -54, 66, 37};
    COUT << "Sort #0 - "; printArray(data, ARRAY_SIZE(data)); COUT << std::endl;
    quickSort(data, ARRAY_SIZE(data));
    COUT << "Sort #1 - "; printArray(data, ARRAY_SIZE(data)); COUT << std::endl;
    BOOST_CHECK_EQUAL(data[0], -1113);
    BOOST_CHECK_EQUAL(data[1], -54);
    BOOST_CHECK_EQUAL(data[2], 10);
    BOOST_CHECK_EQUAL(data[3], 23);
    BOOST_CHECK_EQUAL(data[4], 23);
    BOOST_CHECK_EQUAL(data[5], 37);
    BOOST_CHECK_EQUAL(data[6], 66);
    BOOST_CHECK_EQUAL(data[7], 232);
    BOOST_CHECK_EQUAL(data[8], 984);
}
