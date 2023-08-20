// Cartesian Line Analysis and Equation Solver

/// @brief This program reads in two Cartesian coordinates representing two
/// points on a line, then computes the line equation, slope direction, and
/// line segment length between the two points. If the points are the same,
/// an error is reported. If the input is bad, an error is reported.
/// On error, a usage message is presented.

// library includes
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

// set namespace
using namespace std;

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Local constant definition(s)
    // epsilon: used to test real numbers for equality
    // anything smaller than this number is considered zero
    const double EPS = 0.0000001;  // epsilon: used to test real numbers
    const int VERT = 0;         // signals slope is vertical
    const int HORZ = 1;         // signals slope is horizontal
    const int INCR = 2;         // signals slope is increasing
    const int DECR = 3;         // signals slope is decreasing
    const int CW   = 21;        // output label column width

    // Variable declarations(s)
    int exitState;              // tracks the exit code for the process
    exitState = EXIT_SUCCESS;   // set state to successful run

    double x1;                  // x coordinate of point 1
    double y1;                  // y coordinate of point 1
    double x2;                  // x coordinate of point 2
    double y2;                  // y coordinate of point 2
    string eMessage;            // error message

    int    direction = VERT;    // slope direction, init vert
    double slope     = 0;       // computed slope value (m)
    double intercept = 0;       // computed y-intercept value
    double dx;                  // change in x (the "run")
    double dy;                  // change in y (the "rise")
    double length = 0;          // line segment length

    /* ******* Input Phase *********************************************** */
    // Do not prompt user. Just read input, which will be redirected into
    // the program.
    if (cin >> x1 >> y1 >> x2 >> y2) {
        exitState = EXIT_SUCCESS;
    } else {
        exitState = EXIT_FAILURE;
        eMessage = "Error reading input. Please try again.";
    }


    /* ******* Processing Phase ****************************************** */
    // process the data if it was read successfully
    if (exitState == EXIT_SUCCESS) {
        // check for same point
        if (fabs((fabs(x1) - fabs(x2))) < EPS &&
            fabs((fabs(y1) - fabs(y2))) < EPS) {

            // set the error message to indicate the points are the same
            eMessage = "Error, the points are the same. Please try again.";
            exitState = EXIT_FAILURE;
        } else {
            dx = x2 - x1;                       // calculate change in x
            dy = y2 - y1;                       // calculate change in y
            length = sqrt(dx * dx + dy * dy);   // distance between pts

            // avoid division by zero
            // changing to absolute value avoids testing
            // a floating point number for equality
            if (fabs(dx) > 0) {
                slope = dy / dx;                // calculate the line slope
                intercept = y1 - slope * x1;    // calculate the y-intercept(b)

                // slope is assumed to be VERT if dx == 0
                // check for other cases to determine direction
                if (slope > 0) {
                    direction = INCR;
                } else if (slope < 0) {
                    direction = DECR;
                } else {
                    direction = HORZ;
                }
                // optional
                // direction = (slope < 0) ? DECR : (slope > 0) ? INCR : HORZ;
            }
        }
    }

    /* ******* Output Phase ********************************************** */
    if (exitState == EXIT_SUCCESS) {
        cout << left;                     // Set output justification

        // output the line equation
        cout << "From point: (" << x1 << ", " << y1 << ") to point: ("
        << x2 << ", " << y2 << ")." << "\n";
        cout << setw(CW) << "Line equation:";
        if (direction == VERT) {
            cout << "x = " << x1 << '\n';
        } else if (direction == HORZ) {
            cout << "y = " << y1 << '\n';
        } else {
            cout << "y = " << slope << "x + " << intercept << '\n';
        }


        // output the slope direction
        cout << setw(CW) << "Slope direction:";
        switch (direction) {
            case VERT:  cout << "vertical"  ;  break;
            case HORZ:  cout << "horizontal";  break;
            case INCR:  cout << "increasing";  break;
            case DECR:  cout << "decreasing";  break;
            default:    cout << "undefined" ;  break;
        }
        cout << endl;

        // output the segment length
        cout << setw(CW) << "Line segment length:" << length << endl;
    } else {
        cout << eMessage << endl;
    }

    cout << endl;

    return exitState;
}