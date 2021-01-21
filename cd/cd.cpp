//@author hugce564

#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Prints amount of CDs that are owned by both Jack and Jill.
 */
int main()
{
    int m, n;
    while(cin >> m >> n){
        if(n == 0 && m == 0) break;
        vector<int> jack, jill;

        for(int i=0; i<m; i++){
            int temp;
            cin >> temp;
            jack.push_back(temp);
        }

        for(int i=0; i<n; i++){
            int temp;
            cin >> temp;
            jill.push_back(temp);
        }

        int sum = 0;
        vector<int>::iterator itJack = jack.begin();
        vector<int>::iterator itJill = jill.begin();
        //Only goes through the lists once
        while(itJack != jack.end() && itJill != jill.end()){
            if(*itJack<*itJill) itJack++;
            else if(*itJill<*itJack) itJill++;
            else{
                sum++;
                itJack++;
                itJill++;
            }
        }
        cout << sum << endl;
    }

    return 0;
}

