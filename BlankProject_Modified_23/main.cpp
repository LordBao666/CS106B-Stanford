/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "SimpleTest.h"
using namespace std;

STUDENT_TEST("Test"){
    EXPECT_EQUAL("hi","hi");
}

int main()
{
    if(ALL_TESTS){
        cout<<"test cases passed"<<endl;
    }
    return 0;
}
