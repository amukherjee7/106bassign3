/*
 * sierpinski.cpp
 * Names: Srishti Boral, Anika Mukherjee
 * Course: CS 106B
 * Description: This file draws a Sierpinski triangle, a fractal made of
 * smaller copies of itself. drawSierpinskiTriangle recursively splits a
 * triangle into three half-size triangles at the midpoints of its sides,
 * draws only the black triangles at order 0, and returns how many black
 * triangles it drew.
 */

#include <iostream>
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/* Draws a Sierpinski triangle of the given order with corners one, two, and three.
 * An order 0 triangle is one filled black triangle.
 * For a higher order, it finds the midpoint of each side and recursively draws
 * three triangles of order - 1, one in each corner of the original.
 * Parameters: window (where to draw), one, two, three (the corner points),
 * order (how many levels of recursion to draw)
 * Returns: the total number of black triangles drawn
*/

int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order == 0) { // base case
        fillBlackTriangle(window, one, two, three);
        return 1;
    }

    GPoint mid12((one.x + two.x)/2, (one.y + two.y)/2); // define midpoint between one and two
    GPoint mid23((two.x + three.x)/2, (two.y + three.y)/2); // define midpoint between two and three
    GPoint mid13((one.x + three.x)/2, (one.y + three.y)/2); // define midpoint between one and three

    int count = 0; // this is what the function returns, count = number of triangles in the drawing
    count += drawSierpinskiTriangle(window, one, mid12, mid13, order - 1); // draw bottom left triangle
    count += drawSierpinskiTriangle(window, mid12, two, mid23, order - 1); // draw top triangle
    count += drawSierpinskiTriangle(window, mid13, mid23, three, order - 1); // draw bottom right triangle

    return count;
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all your testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

