#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <vector>
#include "opencv2/opencv.hpp"
#include <algorithm>
#include <string>
#include <fstream>
#include "glog/logging.h"
#include "utils/utils.hpp"
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
        string name_;
        vector<Point2f> keypoints_;
        vector<Point2f> initkeypoints_;

};

bool compare(const Image & i1, const Image& i2 ){
    return i1.key_ < i2.key_;

}


//template<typename State>
class Data{
    public:
        Data(int num_keypoints, int height, int width):num_keypoints_(num_keypoints), height_(height)
        , width_(width){
            // feature_ = new Feature<State>(config);
            // int context_patch = config.configuration_.context_patch();
            // selector_ = new Selector<State>(-context_patch, context_patch);
            characters_="0123456789ABCDEFGHIJKLMNOPQRSTUYWXYZabcdefghijklmnopqrstuvwxyz";
        }
        ~Data(){


        }

        void load_keypoints(string file, vector<Point2f>& keypoints ){
            ifstream fin(file , ios::in);
            float x = 0, y = 0;
            while(fin >> x >> y){
                Point2f point(x,y);
                keypoints.push_back(point);
            }
            fin.close();
        }

        void load_neg_keypoints(vector<Point2f>& keypoints){
            keypoints.clear();
            
            int step = height_/(num_keypoints_/4);
            for(int i = 0; i < num_keypoints_/4; ++ i){
                keypoints.push_back(Point(0.0f,i*step));
                keypoints.push_back(Point(width_,i*step));
            }
            for(int i = 0; i < num_keypoints_/4; ++i){
                keypoints.push_back(Point(i*step,0.0f));
                keypoints.push_back(Point(i*step,height_));
            }
            

        }


        void load_data(string path, string file){
            ifstream fin(file, ios::in);
            string content;
            data_.clear();
            while(fin >> content){
                Image image;
                image.img_ = imread(path+"/images/"+content+".png");
                load_keypoints(path+"/keypoints/"+content+".txt",image.keypoints_);
                image.name_ = content;
                vector<string> contents;
                SplitString(content,contents,"_");
                image.label_ = characters_.find(contents[0]);
                data_.push_back(image);
            }
            LOG(INFO)<< "load "<< data_.size()<< " data"; 
            fin.close();
            
        }

        void load_neg(string path, string file){
            ifstream fin(file, ios::in);
            string content;
            while(fin >> content){
                Image image;
                image.img_ = imread(path+"/neg/"+content+".png");
                load_neg_keypoints(image.keypoints_);
                
                image.name_=content;
                image.label_ = -1;
                data_.push_back(image);


            }


            fin.close();


        }

    

    public:

    
        vector<Image> data_;
        // Config config_;
        // Feature<State>* feature_;
        // Selector<State>* selector_;
        string characters_;
        int num_keypoints_;
        int height_;
        int width_;



};



}

#endif

