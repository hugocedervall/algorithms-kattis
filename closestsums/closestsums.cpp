#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> permutations(vector<int> &numbers);
int findClosest(int &number, vector<int> &permutationSums);

/*
 * Finds the closest sum of two integers to given number and integers.
 */
int main()
{
    int counter = 0;
    int n;
    while(cin >> n){
        counter ++;
        cout << "Case " << counter << ":" << endl;

        vector<int> distrinctInt;
        distrinctInt.resize(n);

        for(int i=0; i<n; i++){
            cin >> distrinctInt[i];
        }

        vector<int> permutationSums = permutations(distrinctInt);
        int m;
        cin >> m;

        for(int i=0; i<m; i++){
            int temp;
            cin >> temp;
            int closest = findClosest(temp, permutationSums);
            cout << "Closest sum to " << temp << " is " << closest << "." << endl;
        }
    }
    return 0;
}

/*
 * Returns the closest sum in sorted vector to number.
 */
int findClosest(int& number, vector<int>& permutationSums){
    int kingNumber = permutationSums[0];

    for(int i=0; i<permutationSums.size(); i++){
        if(abs(permutationSums[i] - number) < abs(kingNumber - number)){
            kingNumber = permutationSums[i];
        }
    }
    return kingNumber;
}

/*
 * Returns all available sums of two numbers in given vector.
 */
vector<int> permutations(vector<int>& numbers){
    vector<int> permutatedSums;
    for(int i=0; i<numbers.size(); i++){
        for(int j=i+1; j<numbers.size(); j++){
            permutatedSums.push_back(numbers[i] + numbers[j]);
        }
    }
    return permutatedSums;
}
