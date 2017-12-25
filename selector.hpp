#ifndef __SELECTOR_HPP__
#define __SELECTOR_HPP__

#include <vector>
#include <iostream>

#include "Random.h"
using namespace std;
namespace Beta{
template<typename State>
class Selector{
    public:
        Selector(int minVal, int maxVal):min_val_(minVal), max_val_(maxVal){

        }
        ~Selector(){

        }

        void random_generation(int number){
            selector_.resize(number);
            Random rand;
            for(int i = 0; i < number; ++ i){
                //cout<<selector_[i].x1_<<" "<<endl;
                selector_[i].x0_ = rand.Next(min_val_, max_val_);
                selector_[i].y0_ = rand.Next(min_val_, max_val_);
                selector_[i].x1_ = rand.Next(min_val_, max_val_);
                selector_[i].y1_ = rand.Next(min_val_, max_val_);
            }
        }

        void set_center(float x, float y){
            for(auto & se : selector_){
                se.xc_ = x;
                se.yc_ = y;
            }
        }


        void print(){
            for(int i = 0; i < selector_.size(); ++ i){
                cout<< selector_[i].x1_ <<" "<< selector_[i].y1_<<" "<<endl;
                cout<< selector_[i].x0_ <<" "<< selector_[i].y0_<<" "<<endl;

            }
        }

        const State & selector(int index){
            return selector_[index];
        }
    protected:
        vector<State> selector_;
        int min_val_;
        int max_val_;



};




}





#endif