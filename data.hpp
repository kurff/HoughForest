#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <vector>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

class Image{
    public:
        Image(){}
        ~Image(){}
        Mat img_;
        int index_;



};

class Data{
    public:
        Data(){}
        ~Data(){}

    

    

    protected:

    
        vector<Image> data_;



};





#endif

