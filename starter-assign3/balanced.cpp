/*
 * balanced.cpp
 * Names: Srishti Boral, Anika Mukherjee
 * Course: CS 106B
 * Description: This file checks whether the bracketing operators in a \
 * string are balanced. operatorsFrom recursively pulls out only the ( ) [ ] { } characters,
 * and operatorsAreMatched recursively removes matching
 * pairs until the string is empty (balanced) or no pair is left to remove
 * (not balanced). isBalanced puts the two together.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "SimpleTest.h"

using namespace std;

/* Returns only the bracketing operators ( ) [ ] { } from a string, in the
 * same order, and drops every other character. It checks the first
 * character, keeps it if it's an operator, and then recursively handles
 * the rest of the string.
 * Parameter: str (the string to filter)
 * Returns: a string with only the bracketing operators from str
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

/* Returns whether a string of bracketing operators is balanced. An empty
 * string is balanced. Otherwise it looks for a matching pair "()", "[]",
 * or "{}" next to each other, removes it, and recursively checks what is
 * left. If no matching pair can be found, the operators are not balanced.
 *
 * Parameter: ops (a string containing only bracketing operators)
 * Returns: true if the operators are balanced, false otherwise
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

STUDENT_TEST("operatorsFrom keeps all six operator types in order") {
    EXPECT_EQUAL(operatorsFrom("{x[y](z)}"), "{[]()}");
}

STUDENT_TEST("operatorsFrom on a string with no operators") {
    EXPECT_EQUAL(operatorsFrom("hello world 123"), "");
}

STUDENT_TEST("operatorsAreMatched on an empty string") {
    EXPECT(operatorsAreMatched(""));
}

STUDENT_TEST("operatorsAreMatched on nested pairs") {
    EXPECT(operatorsAreMatched("{[()]}"));
    EXPECT(operatorsAreMatched("(())"));
}

STUDENT_TEST("operatorsAreMatched on pairs side by side") {
    EXPECT(operatorsAreMatched("()[]{}"));
}

STUDENT_TEST("operatorsAreMatched on single operator") {
    EXPECT(!operatorsAreMatched("("));
    EXPECT(!operatorsAreMatched("]"));
}

STUDENT_TEST("operatorsAreMatched on missing or out of order openers/closers") {
    EXPECT(!operatorsAreMatched("))"));
    EXPECT(!operatorsAreMatched("{()"));
    EXPECT(!operatorsAreMatched(")("));
}

STUDENT_TEST("operatorsAreMatched on improperly nested pairs") {
    EXPECT(!operatorsAreMatched("[(])"));
}

STUDENT_TEST("operatorsAreMatched on mismatched operator types and random chars") {
    EXPECT(!operatorsAreMatched("(]"));
    EXPECT(!operatorsAreMatched("(a)"));
}

STUDENT_TEST("isBalanced on strings with no operators at all") {
    EXPECT(isBalanced(""));
    EXPECT(isBalanced("no brackets here"));
}