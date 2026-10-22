/* ballots.cpp
 * Names: Srishti Boral, Anika Mukherjee
 * Course: CS 106B
 * Description: This file counts the ways ballots can be tallied in a
 * two-candidate election. countAllOrderings recursively counts every
 * possible order the ballots can come out of the box. countGoodOrderings
 * counts only the orders where the winner, A, stays always ahead for
 * the whole tally.
 */
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/* Returns the number of different orders the ballots can be tallied in.
 * If one candidate has no ballots left, there is only one order left. Otherwise
 * the next ballot is either for A or for B, so it adds up the orders for both of those smaller cases.
 * Parameters: a (ballots for A), b (ballots for B)
 * Returns: the number of possible tally orders
*/

int countAllOrderings(int a, int b) {
    if (a == 0 || b == 0) { // if one person got no votes, only one possible ordering
        return 1;
    } else {
        return (countAllOrderings(a - 1, b) + countAllOrderings(a, b - 1));
    }
}


/*
 * Recursive helper for countGoodOrderings.
 * It counts the orders for the remaining ballots that keep A always ahead, given A's current lead.
 * If the lead ever drops to 0 or below, this path can't be good, so it counts 0.
 * If there are no ballots left and A stayed ahead, it counts 1.
 * Otherwise it tries tallying an A next (lead goes up) and a B next
 * (lead goes down) and adds the results.
 * Parameters: a (A ballots left), b (B ballots left), lead (A's votes - B's votes so far)
 * Returns: the number of good orderings for the remaining ballots
 */

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

/* Returns the number of orders where A is strictly ahead of B for the
 * whole tally. A good ordering has to start with an A ballot, so it tallies
 * one A (giving A a lead of 1) and lets countGoodHelper count the rest.
 * Parameters: a (ballots for A), b (ballots for B)
 * Returns: the number of good tally orders, or 0 if A has no ballots
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

STUDENT_TEST("countGoodOrderings on edge cases") {
    EXPECT_EQUAL(countGoodOrderings(2, 0), 1);
    EXPECT_EQUAL(countGoodOrderings(1, 1), 0);
}

STUDENT_TEST("countGood / countAll matches Bertrand's formula (a - b) / (a + b)") {
    for (int a = 1; a <= 10; a++) {
        for (int b = 0; b < a; b++) {
            double ratio = double(countGoodOrderings(a, b)) / countAllOrderings(a, b);
            double bertrand = double(a - b) / (a + b);
            EXPECT(ratio - bertrand < 0.000001 && bertrand - ratio < 0.000001);
        }
    }
}