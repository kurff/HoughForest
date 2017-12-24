#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <vector>
#include "opencv2/opencv.hpp"
#include <algorithm>
#include <string>
#include <fstream>
#include "glog/logging.h"
#include "utils/utils.hpp"
#include "Random.h"
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
        int prediction_;
        float confidence_;
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

        void load_init_keypoints(vector<Point2f>& keypoints){
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
            LOG(INFO)<<"read positive training file"<< path << file ;
            ifstream fin(file, ios::in);
            string content;
            data_.clear();
            while(fin >> content){
                Image image;
                image.img_ = imread(path+"/images/"+content+".png",1);
                if(image.img_.channels() !=3){
                    LOG(INFO)<<"error";
                }
                load_keypoints(path+"/keypoints/"+content+".txt",image.keypoints_);
                image.name_ = content;
                vector<string> contents;
                SplitString(content,contents,"_");
                //image.label_ = characters_.find(contents[0]);
                image.label_ = 1;
                data_.push_back(image);
            }
            LOG(INFO)<< "Final load "<< data_.size()<< " data"; 
            fin.close();
            
        }


        Mat random_patch(Mat & image){
            Random ran;
            int height = image.rows;
            int width = image.cols;
            int y0 = ran.Next(0, height - height_);
            int x0 = ran.Next(0, width - width_);
            //LOG(INFO)<<height <<" "<< width <<" "<< y0<<" "<<x0<<"height "<< height_ <<"width "<< width_;
            Rect rect(x0,y0, width_, height_);
            return image(rect);
        }

        void load_neg(string path, string file){
            LOG(INFO)<<"load negtive file";
            LOG(INFO)<< path;
            LOG(INFO)<< file;
            ifstream fin(file, ios::in);
            string content;
            while(fin >> content){
                Image image;
                Mat img = imread(path+"/neg/"+content+".jpg",1);
                if(img.channels() !=3){
                    LOG(INFO)<<"error";
                }
                if(img.empty()){
                    LOG(INFO)<<"can not read image"<< (path+"/neg/"+content+".jpg");
                }
                Mat subimg = random_patch(img);
                subimg.copyTo(image.img_);
                load_neg_keypoints(image.keypoints_);
                image.name_=content;
                image.label_ = 0;
                data_.push_back(image);
            }
            fin.close();
            LOG(INFO)<<"load negative" << data_.size();

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

