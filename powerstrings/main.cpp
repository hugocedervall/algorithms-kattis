#include <iostream>

using namespace std;


int algo(const string &word) {
    string pattern;

    for (int i = 0; i < word.length(); i++) {
        pattern += word[i];

        if (word.length() % pattern.length() == 0) {
            // Check if pattern reoccuring
            int counter = 1;
            int low = pattern.length();
            while (true) {
                string tempPattern = word.substr(low, pattern.length());
                if (tempPattern == pattern) {
                    counter++;
                } else
                    break;

                if (low + pattern.length() > word.length()) break;
                low += pattern.length();
            }
            if (counter == (double(word.length()) / pattern.length())) return counter;
        }
    }
    return 1;
}


int main() {

    string input;
    while (cin >> input && input != ".") {
        int repeats = algo(input);
        cout << repeats << endl;
    }

    return 0;
}
