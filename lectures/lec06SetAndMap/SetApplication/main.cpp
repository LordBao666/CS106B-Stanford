/*
 * File: main.cpp
 * --------------
 * print all the duplicate elements in some vector,
 * but only print each duplicate once, no matter how many
 * times it's duplicated in the array.
 */

#include <iostream>
#include <set.h>
using namespace std;


int main()
{
    Vector<string> v = {"unicorn", "cupcake", "swamp", "cupcake", "unicorn", "unicorn"};
    Set<string> seen ;
    Set<string> dupe;
    for(string s:v){
        if(seen.contains(s)){
            dupe.add(s);
        }
        seen.add(s);
    }
    cout<<"the duplicate set is"<<dupe<<endl;
    return 0;
}
