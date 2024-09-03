#include <iostream>
#include "console.h"
#include "filelib.h"
#include "map.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

bool getFrequencies(string filename, Map<string, int>& map)
{
    ifstream ifs;

    if (!openFile(ifs, filename))
    {
        cout << "Failed to open file in getFrequencies(): " << filename << endl;
        return false;
    }

    Vector<string> lines = readLines(ifs);
    for (string line : lines)
    {
        Vector<string> words = stringSplit(line, " ");
        for (string word : words)
        {
            // Note that map.get(word)++ would not work here.
            map[word]++;

            // We could have done the following, but since map[word] gives us a 0
            // for any key not in the map, the line above accomplishes our goal
            // more succinctly.
            //
            //    if (map.contains(word))
            //    {
            //       int freq = map.get(word);
            //       map[word] = freq + 1;
            //    }
            //    else
            //    {
            //       map[word] = 1;
            //    }
        }
    }

    return true;
}

int main()
{
    Map<string, int> wordToFrequencyMap;
    getFrequencies("poem.txt", wordToFrequencyMap);

    // Print occurrence frequencies.
    for (string s : wordToFrequencyMap.keys())
    {
        cout << s << ": " << wordToFrequencyMap.get(s) << endl;
    }

    return 0;
}
