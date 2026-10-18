/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "SimpleTest.h"

using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
string operatorsFrom(string str) {
    if (str.size() == 0) { // base case
        return "";
    }
    string first = "";
    char ch = str[0]; // check top char
    if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') { // check if top char is an operator
        first = ch; // set first equal to top char
    }
    return first + operatorsFrom(str.substr(1)); // run recursively
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool operatorsAreMatched(string ops) {
    if (ops.size() == 0) { // base case
        return true;
    }

    int pairIndex = ops.find("()"); // check if each operator pair exists
    if (pairIndex == -1) { // if () doesn't exist
        pairIndex = ops.find("[]"); // check if [] exists
    }
    if (pairIndex == -1) { // if both () and [] don't exist
        pairIndex = ops.find("{}"); // check if {} exists
    }

    if (pairIndex == -1) { // if none of the operator pairs exist
        return false; // we have nothing to check! return false
    }

    return operatorsAreMatched(ops.substr(0, pairIndex) + ops.substr(pairIndex + 2)); // run recursively, removing the operator pair
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example = "int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

// STUDENT TEST CASES
STUDENT_TEST("operatorsFrom on empty string") {
    EXPECT_EQUAL(operatorsFrom(""), "");
}

STUDENT_TEST("operatorsFrom on a random char") {
    EXPECT_EQUAL(operatorsFrom("a"), "");
}

STUDENT_TEST("operatorsFrom with random chars between operators") {
    EXPECT_EQUAL(operatorsFrom("(abc)"), "()");
}

STUDENT_TEST("operatorsAreMatched on an empty string") {
    EXPECT(operatorsAreMatched(""));
}

STUDENT_TEST("operatorsAreMatched on nested pairs") {
    EXPECT(operatorsAreMatched("{[()]}"));
    EXPECT(operatorsAreMatched("(())"));
}

STUDENT_TEST("operatorsAreMatched on lone operator") {
    EXPECT(!operatorsAreMatched("("));
    EXPECT(!operatorsAreMatched("]"));
}

STUDENT_TEST("operatorsAreMatched on missing or out of order openers/closers") {
    EXPECT(!operatorsAreMatched("))"));
    EXPECT(!operatorsAreMatched("{()"));
    EXPECT(!operatorsAreMatched(")("));
}

STUDENT_TEST("operatorsAreMatched on mismatched operator types and random chars") {
    EXPECT(!operatorsAreMatched("(]"));
    EXPECT(!operatorsAreMatched("(a)"));
}
