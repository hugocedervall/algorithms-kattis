//@AUTHOR: Hugo Cedervall

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int iterations = 0;

    while(cin >> iterations){
        int action, number;

        stack<int> tempStack;
        queue<int> tempQueue;
        priority_queue<int> tempPrioQueue;

        vector<string> options{"stack", "queue", "priority queue"};

        for(int i=0; i<iterations; i++){
            cin >> action >> number;

            if(action==1){
                tempStack.push(number);
                tempQueue.push(number);
                tempPrioQueue.push(number);
            }
            else if(action ==2){
                if(find(options.begin(), options.end(), "stack") != options.end() && (tempStack.size() <= 0 || tempStack.top() != number)){
                    options.erase(find(options.begin(), options.end(), "stack"));
                }
                if(find(options.begin(), options.end(), "queue") != options.end() && (tempQueue.size() <= 0 || tempQueue.front() != number)){
                    options.erase(find(options.begin(), options.end(), "queue"));
                }
                if(find(options.begin(), options.end(), "priority queue") != options.end() && (tempPrioQueue.size() <= 0 || tempPrioQueue.top() != number)){
                    options.erase(find(options.begin(), options.end(), "priority queue"));
                }
                if(!tempStack.empty()) tempStack.pop();
                if(!tempQueue.empty()) tempQueue.pop();
                if(!tempPrioQueue.empty()) tempPrioQueue.pop();
            }
        }

        if(options.size() == 0){
            cout << "impossible" << endl;
        }
        else if(options.size() > 1){
            cout << "not sure" << endl;
        }
        else if(options.size() == 1){
            cout << options.back() << endl;
        }
    }
    return 0;
}

