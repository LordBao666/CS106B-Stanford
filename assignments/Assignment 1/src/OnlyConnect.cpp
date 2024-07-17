/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include <cctype>
#include <string>
#include <strlib.h>
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
using namespace std;

/**
 * Suppose ch is an English letter, i.e a letter between 'a' and 'z'
 * or between 'A' and  'Z', return true if it is a  consonant,otherwise
 * return false.
 */
bool isEnglishLetterConsonant(char ch);

string onlyConnectize(string phrase) {
    int size = phrase.size();
    if(size==0){
        return string("");
    }

    string substr = phrase.substr(1);
    //if phrase[0] is a consonant
    if(isalpha(phrase[0]) && isEnglishLetterConsonant(phrase[0])){
        return charToString(toupper(phrase[0]))+onlyConnectize(substr);
    }else{
        return onlyConnectize(substr);
    }
}

bool isEnglishLetterConsonant(char ch){
    ch=tolower(ch);
    if(ch=='a' || ch=='e' || ch=='i' ||
       ch=='o' || ch=='u' ){
        return false;
    }
    return true;
}




/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */

STUDENT_TEST("Handles special characters."){
    EXPECT_EQUAL(onlyConnectize("*!.,:---,....."), "");
    EXPECT_EQUAL(onlyConnectize("+;234.1.323JOoj"), "JJ");
}

STUDENT_TEST("Handles empty string"){
    EXPECT_EQUAL(onlyConnectize(""), "");

}



