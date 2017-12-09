#ifndef __STATE_HPP__
#define __STATE_HPP__

namespace Beta{
    class State{
        public:
            State():x0_(0), y0_(0),x1_(0), y1_(0), t_(0.0f),xc_(0),yc_(0){

            }

            ~State(){

            }

        public:
            int x0_;
            int y0_;
            int x1_;
            int y1_;
            float t_; // threshold

            int xc_;
            int yc_;






    };

    class RegressionState{
        public:
            RegressionState(){

            }
            ~RegressionState(){

            }
        


    };




}








#endif