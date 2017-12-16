#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <vector>
#include "opencv2/opencv.hpp"
#include <algorithm>
#include <string>
// #include "feature.hpp"
// #include "configure.hpp"
// #include "selector.hpp"
using namespace std;
using namespace cv;






namespace Beta{
class Image{
    public:
        Image(){}
        ~Image(){}
        Mat img_;
        int index_;
        float key_; // feature
        int label_;
        vector<Point2f> keypoints_;
        vector<Point2f> initkeypoints_;

};

bool compare(const Image & i1, const Image& i2 ){
    return i1.key_ < i2.key_;

}


//template<typename State>
class Data{
    public:
        Data(){
            // feature_ = new Feature<State>(config);
            // int context_patch = config.configuration_.context_patch();
            // selector_ = new Selector<State>(-context_patch, context_patch);

        }
        ~Data(){


        }


        void load_data(string path){

            

        }

    

    public:

    
        vector<Image> data_;
        // Config config_;
        // Feature<State>* feature_;
        // Selector<State>* selector_;




};



}

#endif

