//Bring in unit testing code and tell it to build a main function
//If you have multiple unit test files, only one should have this define
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//This pragma supresses a bunch of warnings QTCreator produces (and should not)
#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

//Hide some false warnings - this is supposed to look commented out
// clazy:skip

//Tell clang analyzer to ignore doctest.h
#ifndef __clang_analyzer__
#include "doctest.h"
#endif

//Use Approx from doctest without saying doctest::Approx
using doctest::Approx;

//-----------------------------------------------------------------------------------

//Sample functions
int squareDifference(int a, int b) {
    return (a - b) * (a - b);
}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt( squareDifference(x1, x2) + squareDifference(y1, y2) );
}


//Tests:

TEST_CASE( "squareDifference" ) {

    //CHECK means keep running this TEST_CASE even if failed.
    CHECK( squareDifference(1, 4) == 9 );

    //Test that ordering does not matter
    CHECK( squareDifference(4, 1) == 9 );

    //Test that negatives are handled
    int answer3 = squareDifference(-2, -6);
    CHECK( answer3 == 16 );

    //Check that x is 5. REQUIRE means stop running this TEST_CASE if failed
    //  and move on to the next TEST_CASE
    //Use it in situations where there is no point in trying rest of tests if
    //  this step fails.
    //REQUIRE( squareDifference(-2, -6) == 16 );
}

TEST_CASE( "distance" ) {
    int x1 = 0, y1 = 0;
    int x2 = 3, y2 = 4;
    int x3 = -2, y3 = -2;

    //Approx sees if a double value is "close enough" to believe that any difference
    // is based on rounding error.
    //Always tests doubles using Approx.
    //It only exists in unit tests - do not use in normal code.
    CHECK( distance(x1, y1, x2, y2) == Approx(5.0) );

    //Check reverse direction
    CHECK( distance(x2, y2, x1, y1) == Approx(5.0) );

    //Test some negative coordinate values
    double answer2 = distance(x1, y1, x3, y3);
    double answer2Desired = 2 * sqrt(2);
    CHECK( answer2 == Approx(answer2Desired) );
}
