/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
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

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
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

