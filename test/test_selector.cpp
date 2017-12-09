#include "gtest/gtest.h"
#include "state.hpp"
#include "selector.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using namespace Beta;
TEST(SELECTOR, generation){

    Selector<State>* selector = new Selector<State>(0,100);
    selector->random_generation(100);
    selector->print();





}

TEST(SORT, sort){
    vector<int> x{1,33,4,5,78,3,23,56,56,4,34,23};
    vector<int>::iterator begin = x.begin();
    vector<int>::iterator end = x.end();
    sort(begin,end);
    for(vector<int>::iterator it = begin; it !=end; it ++ ){
        cout<< * it <<" ";
    }


}