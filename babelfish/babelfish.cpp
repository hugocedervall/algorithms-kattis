#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

/*
 * Puts loads of words in a dictionary and
 * then translates given words.
 */
int main()
{
    map<string, string> dictionary;

    string line;
    while(getline(cin, line) && !line.empty()){
        string engWord, foreignWord;
        ptrdiff_t pos = find(line.begin(), line.end(), ' ') - line.begin();
        engWord = line.substr(0, pos);
        foreignWord = line.substr(pos + 1, line.length());
        dictionary[foreignWord] = engWord;
    }

    string word;
    while(cin >> word){
        if(dictionary.find(word) != dictionary.end()){
            cout << dictionary[word] << endl;
        }
        else{
            cout << "eh" << endl;
        }
    }
    return 0;
}

