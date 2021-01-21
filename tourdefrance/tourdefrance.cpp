// @AUTHOR: Hugo Cedervall

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

/*
 * Calculates the maximum spread between all teeth differences of a bike.
 */
int main() {
    int front, back;
    while(cin >> front && front != 0 && cin >> back && back != 0){
        vector<int> frontClus, backClus;
        frontClus.resize(front);
        backClus.resize(back);

        for(int f=0; f<front; f++){
            cin >> frontClus[f];
        }
        for(int b=0; b<back; b++){
            cin >> backClus[b];
        }

        vector<double> driveRatios;
        for(auto f : frontClus){
            for(auto b : backClus){
                driveRatios.push_back(double(b) / double(f));
            }
        }
        sort(driveRatios.begin(), driveRatios.end());

        //Because vector is sorted, we only try to divide by the number coming before.
        double maxSpread = 0;
        for(int i=0; i<driveRatios.size(); i++){
            int j = i+1;
            if(j>=driveRatios.size()) break;
            double spread = driveRatios[j]/driveRatios[i];
            if(spread > maxSpread){
                maxSpread = spread;
            }

        }
        printf("%.2f\n", maxSpread);
    }
    return 0;
}
