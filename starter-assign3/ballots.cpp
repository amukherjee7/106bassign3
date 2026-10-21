/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int countAllOrderings(int a, int b) {
    if (a == 0 || b == 0) { // if one person got no votes, only one possible ordering
        return 1;
    } else {
        return (countAllOrderings(a - 1, b) + countAllOrderings(a, b - 1)); //
    }
}


// helper function for recursion
int countGoodHelper(int a, int b, int lead) {
    if (lead <= 0) {
        return 0;
    }

    if (a == 0 && b == 0) {
        return 1;
    }

    int count = 0;
    if (a > 0) {
        count += countGoodHelper(a - 1, b, lead + 1);
    }

    if (b > 0) {
        count += countGoodHelper(a, b - 1, lead - 1);
    }

    return count;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int countGoodOrderings(int a, int b) {
    if (a == 0) {
        return 0;
    }
    return countGoodHelper(a - 1, b, 1);
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("countAllOrderings, two A one B") {
   EXPECT_EQUAL(countAllOrderings(2, 1), 3);
}

PROVIDED_TEST("countGoodOrderings, two A one B") {
   EXPECT_EQUAL(countGoodOrderings(2, 1), 1);
}

// STUDENT TEST CASES

STUDENT_TEST("countAllOrderings, bases cases") {
    EXPECT_EQUAL(countAllOrderings(0, 0), 1);
    EXPECT_EQUAL(countAllOrderings(1, 0), 1);
    EXPECT_EQUAL(countAllOrderings(0, 1), 1);
}

STUDENT_TEST("countAllOrderings one ballot") {
    EXPECT_EQUAL(countAllOrderings(1, 1), 2);
}

STUDENT_TEST("countAllOrderings on example elections") {
    EXPECT_EQUAL(countAllOrderings(2, 1), 3);
    EXPECT_EQUAL(countAllOrderings(2, 2), 6);
}

STUDENT_TEST("countGoodOrderings on example elections") {
    EXPECT_EQUAL(countGoodOrderings(2, 1), 1);
    EXPECT_EQUAL(countGoodOrderings(3, 1), 2);
    EXPECT_EQUAL(countGoodOrderings(3, 2), 2);
}

STUDENT_TEST("countGoodOrderings on edge case") {
    EXPECT_EQUAL(countGoodOrderings(2, 0), 1);
}
