/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "SimpleTest.h"
using namespace std;

// Function signatures
Queue<int> binaryMerge(Queue<int> a, Queue<int> b);

void checkSorted(Queue<int> q) {
    if (q.isEmpty()) {
        return;
    }

    int previous = q.dequeue();

    while (!q.isEmpty()) {
        int current = q.dequeue();

        if (current < previous) {
            error("binaryMerge input nonsorted error");
        }

        previous = current;
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    checkSorted(a);
    checkSorted(b);

    Queue<int> result;
    while (!a.isEmpty() && !b.isEmpty()) {
        if (a.peek() <= b.peek()) {
            result.enqueue(a.dequeue());
        } else {
            result.enqueue(b.dequeue());
        }
    }

    while (!a.isEmpty()) {
        result.enqueue(a.dequeue());
    }

    while (!b.isEmpty()) {
        result.enqueue(b.dequeue());
    }

    return result;
}

/*
 * The function naiveMultiMerge assumes you have a correctly working
 * binaryMerge function, which this function calls to iteratively
 * merge a collection of sequences, starting off with an empty sequence
 * and repeatedly merging in an additional sequence until all are merged.
 * The code below is provided to you is implemented correctly and you
 * should not need to modify it.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    if (all.isEmpty()) {
        return {};
    }

    if (all.size() == 1) {
        return all[0];
    }

    int mid = all.size() / 2;

    Vector<Queue<int>> leftRes = all.subList(0, mid);
    Vector<Queue<int>> rightRes = all.subList(mid, all.size() - mid);

    Queue<int> lResult = recMultiMerge(leftRes);
    Queue<int> rResult = recMultiMerge(rightRes);

    return binaryMerge(lResult, rResult);
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}


PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


// STUDENT TESTS
STUDENT_TEST("naiveMultiMerge with empty inputs") {
    Vector<Queue<int>> all;
    EXPECT_EQUAL(naiveMultiMerge(all), {});
}

STUDENT_TEST("naiveMultiMerge w/ empty queues") {
    Vector<Queue<int>> all = {{}, {}, {}};
    EXPECT_EQUAL(naiveMultiMerge(all), {});
}

STUDENT_TEST("recMultiMerge handles empty inputs") {
    Vector<Queue<int>> all;
    EXPECT_EQUAL(recMultiMerge(all), {});
}

STUDENT_TEST("recMultiMerge w/ one queue") {
    Vector<Queue<int>> all = {{1, 2, 3}};
    EXPECT_EQUAL(recMultiMerge(all), {1, 2, 3});
}

STUDENT_TEST("recMultiMerge w/ empty and nonempty inputs") {
    Vector<Queue<int>> all = {{}, {1, 3, 5}, {}, {2, 4, 6}};
    EXPECT_EQUAL(recMultiMerge(all), {1, 2, 3, 4, 5, 6});
}

STUDENT_TEST("naiveMultiMerge w/ empty and nonempty inputs") {
    Vector<Queue<int>> all = {{}, {1, 3, 5}, {}, {2, 4, 6}};
    EXPECT_EQUAL(naiveMultiMerge(all), {1, 2, 3, 4, 5, 6});
}

STUDENT_TEST("binaryMerge w/ unsorted queues") {
    Queue<int> a = {3, 7, 4};
    Queue<int> b = {4, 5};
    Queue<int> c = {5, 4};

    EXPECT_ERROR(binaryMerge(a, b));
    EXPECT_ERROR(binaryMerge(b, c));
}

STUDENT_TEST("binaryMerge w/ empty queue") {
    Queue<int> a;
    Queue<int> b = {1, 2, 3};
    EXPECT_EQUAL(binaryMerge(a, b), {1, 2, 3});
    EXPECT_EQUAL(binaryMerge(b, a), {1, 2, 3});
}

STUDENT_TEST("binaryMerge w/ super different queue lengths") {
    Queue<int> a = {1};
    Queue<int> b = {2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQUAL(binaryMerge(a, b), {1, 2, 3, 4, 5, 6, 7, 8});
}

STUDENT_TEST("Time test: binaryMerge (my test)") {
    for (int n = 10000; n <= 80000; n *= 2) {
        Queue<int> a = createSequence(n);
        Queue<int> b = createSequence(n);

        TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
    }
}

STUDENT_TEST("Time test: naiveMultiMerge w/ varying n") {
    int k = 100;

    for (int n = 1000; n <= 16000; n *= 2) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, naiveMultiMerge(all));
    }
}

STUDENT_TEST("Time test: naiveMultiMerge w/ varying k") {
    int n = 16000;

    for (int k = 1; k <= 256; k *= 4) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, naiveMultiMerge(all));
    }
}

STUDENT_TEST("Time test: recMultiMerge w/ varying n") {
    int k = 100;

    for (int n = 1000; n <= 16000; n *= 2) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, recMultiMerge(all));
    }

}

STUDENT_TEST("Time test: recMultiMerge w/ varying k") {
    int n = 16000;

    for (int k = 1; k <= 256; k *= 4) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, recMultiMerge(all));
    }

}
