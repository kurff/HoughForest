#include "gtest/gtest.h"
#include "state.hpp"
#include "selector.hpp"
using namespace Beta;
TEST(SELECTOR, generation){

    Selector<State>* selector = new Selector<State>(0,100);
    selector->random_generation(100);
    selector->print();





}