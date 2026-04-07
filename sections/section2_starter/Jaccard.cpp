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
#include "set.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/*
 * See Stanford library's promptUserForFile function to get
 * a file into a stream format:
 * https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/filelib.html#Function:promptUserForFile
 */
Set<string> wordsIn(istream& input) {
    string word;
    Set<string> ans;
    while(input>>word){//以空白符为分隔符读取单词
        ans.add(word);
    }
    return ans;
}

//以连续的k个单词为整体
Set<string> wordsIn(istream& input,int k) {
    if(k==1){
        return wordsIn(input);
    }


    string word;
    Vector<string> vec;
    while(input>>word){//以空白符为分隔符读取单词
        vec.add(word);
    }
    if(vec.size()<k){return {};}

    string kWord=vec[0];
    for(int i=1;i<k;i++){
        kWord+=" " + vec[i];
    }

    Set<string> ans={kWord};


    //依次添加第i个单词和删除第i-k个单词以形成新串
    for(int i=k;i<vec.size();i++){
        int secondWordIndex =  kWord.find(" ") + 1;
        kWord = kWord.substr(secondWordIndex)+" " + vec[i];
        ans.add(kWord);
    }
    return ans;
}

//计算jaccard相似度
double jaccardSimilarity(Set<string> s1, Set<string> s2){
    Set<string> unionSet = s1 + s2;
    Set<string> intersectionSet = s1 * s2;
    if(unionSet.isEmpty())return 0.0;
    return (1.0 * intersectionSet.size())/unionSet.size();
}


STUDENT_TEST("1-gram jaccard similarity test") {
    string filename1="res/1gram_a.txt";
    string filename2="res/1gram_b.txt";

    ifstream file1(filename1);
    ifstream file2(filename2);
    if(file1.fail() || file2.fail()){
        error("Can't open file(s)");
    }

    double jaccardSimlar = jaccardSimilarity(wordsIn(file1),wordsIn(file2));
    double expectedJaccardSimlar = .25;//两个文本期望得到的1-gram相似度为0.25
    int result  = abs(jaccardSimlar-expectedJaccardSimlar)<1e-3?1:0;
    EXPECT_EQUAL(result,1);
}

STUDENT_TEST("2-gram jaccard similarity test") {
    string filename1="res/2gram_a.txt";
    string filename2="res/2gram_b.txt";

    ifstream file1(filename1);
    ifstream file2(filename2);
    if(file1.fail() || file2.fail()){
        error("Can't open file(s)");
    }
    int k=2;
    double jaccardSimlar = jaccardSimilarity(wordsIn(file1,k),wordsIn(file2,k));
    double expectedJaccardSimlar = 4.0/11;//两个文本期望得到的2-gram相似度为4/11
    int result  = abs(jaccardSimlar-expectedJaccardSimlar)<1e-3?1:0;
    EXPECT_EQUAL(result,1);
}
