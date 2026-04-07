/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "testing/SimpleTest.h"
#include "lexicon.h"
#include "set.h"
#include <string>
using namespace std;

string mostXzibitWord(const Lexicon& words) {

    string ans;
    int maxCount=0;

    for(string word:words){

        Lexicon curLex;//记录对于word满足题目条件的所有子串.curLex自带去重功能

        //遍历所有子串
        for(int startPos =0; startPos<word.size();startPos++){
            for(int endPos = startPos;endPos<word.size();endPos++){
                int len = endPos-startPos+1;
                string subStr =word.substr(startPos,len);
                if(words.contains(subStr)){
                    curLex.add(subStr);
                }
            }
        }
        if(curLex.size()>maxCount){
            maxCount = curLex.size();
            ans = word;
        }


    }
    return ans;
}

/* * * * * Provided Tests Below This Point * * * * */

static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Example from handout") {
    Lexicon& lex = sharedLexicon();
    EXPECT_EQUAL(mostXzibitWord(lex), "foreshadowers");
}
