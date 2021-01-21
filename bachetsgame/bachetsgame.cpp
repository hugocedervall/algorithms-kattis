#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    int stones, moves;
    while(cin >> stones >> moves) {
        int numbers[moves];
        bool winners[stones+1] = {};
        for(int i=0; i<moves; i++){
            int temp;
            cin >> temp;
            numbers[i] = temp;
        }

        for(int i = 1; i<=stones; i++){
            for(int j=0; j<moves; j++){
                int temp = i - numbers[j];
                if(winners[temp] == false && temp >= 0) winners[i] = true;
            }
        }

        if(winners[stones]) cout << "Stan wins" << endl;
        else cout << "Ollie wins" << endl;
    }
    return 0;
}
