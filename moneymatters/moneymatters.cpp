#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Person1{
    int index;
    bool visited = false;
    int owedMoney;
    vector<int> friends;

};

bool fff(vector<Person1> persons);

int main(){
    int personsAmount, friendsAmounts;
    cin >> personsAmount >> friendsAmounts;
    vector<Person1> persons;

    for(int i=0; i<personsAmount; i++){
        Person1 person;
        cin >> person.owedMoney;
        person.index = i;
        persons.push_back(person);
    }

    for(int i=0; i<friendsAmounts; i++){
        int a, b;
        cin >> a >> b;
        persons[a].friends.push_back(b);
        persons[b].friends.push_back(a);
    }

    bool complete = fff(persons);
    if(complete) cout << "POSSIBLE" << endl;
    else cout << "IMPOSSIBLE" << endl;
}



void fffHelper(vector<Person1>& persons, const int& index, int& sum){
    if(persons[index].visited) return;
    persons[index].visited = true;
    sum += persons[index].owedMoney;
    for(int ff : persons[index].friends){
        if(!persons[ff].visited){
            fffHelper(persons, ff, sum);
        }
    }

}
void fHelper(vector<Person1>& persons, const int& index, int& sum){
    fffHelper(persons, index, sum);
}

bool fff(vector<Person1> persons){
    for(Person1 person : persons){
        int sum = 0;
        fHelper(persons, person.index, sum);
        if(sum != 0) return false;
    }
    return true;
}

