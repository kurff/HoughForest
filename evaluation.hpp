#ifndef __EVALUATION_HPP__
#define __EVALUATION_HPP__

#include "data.hpp"
#include <vector>
#include <string>
#include "configure.hpp"
#include "opencv2/opencv.hpp"
#include <cmath>
using namespace std;
using namespace cv;
#define FLOAT_EPS 0.0000001
namespace Beta{

class Evaluation{
    public:
        Evaluation(){

        }

        ~Evaluation(){

        }

        virtual float calculate(const IIterator& begin, const IIterator& middle, const IIterator& end)  =0;



};


class RegressionEvaluation: public Evaluation{
    typedef typename vector<Image>::iterator IIterator;
    public:
        RegressionEvaluation(const Config& config){
            num_keypoints_ = config.configuration_.num_keypoints();
        }
        ~RegressionEvaluation(){}
        float calculate(const IIterator& begin, const IIterator& middle, const IIterator& end){
            vector<Point2f> mean_left;
            mean_left.resize(num_keypoints_);
            int count = 0;
            for(int i = 0; i < num_keypoints_; ++ i){
                mean_left[i] = Point2f(0.0f,0.0f);
                for(IIterator it = begin, count=0; it != middle; ++ it, ++count){
                    mean_left[i] += it->keypoints_[i];
                }
                mean_left[i] /= float(count) + 0.01;

            }
            
            vector<Point2f> mean_right;
            mean_right.resize(num_keypoints_);


            for(int i = 0; i < num_keypoints_; ++ i ){
                mean_right[i] = Point2f(0.0f,0.0f);
                for(IIterator it = middle, count=0; it != end; ++ it, ++count){
                    mean_right[i] += it->keypoints_[i];
                }
                mean_right[i] /= float(count) + FLOAT_EPS;
            }

            float dis_left = 0.0f, dis_right = 0.0f;
            Point2f t;
            for(int i = 0; i < num_keypoints_; ++ i){
                for(IIterator it = begin, count=0; it != middle; ++ it, ++count){
                    t = (it->keypoints_[i] - mean_left[i]);
                    dis_left += t.x * t.x + t.y * t.y;
                }
                dis_left /= float(count) + FLOAT_EPS;
                for(IIterator it = middle, count=0; it != end; ++ it, ++count){
                    t = (it->keypoints_[i] - mean_right[i]);
                    dis_right += t.x * t.x + t.y * t.y;
                }
                dis_right /= float(count) + FLOAT_EPS;

            }


            return dis_left + dis_right;

        }
    protected:
        int num_keypoints_;


        

};

class ClassificationEvaluation: public Evaluation{
    typedef typename vector<Image>::iterator IIterator;
    public:
        ClassificationEvaluation(const Config & config){
            num_classes_ = config.configuration_.num_classes();
            histogram_left_ = shared_ptr<float> (new float [num_classes_] ());
            histogram_right_ = shared_ptr<float> (new float [num_classes_] ());
            //histogram_all_ = shared_ptr<float>(new float [num_classes_]());

        }
        ~ClassificationEvaluation(){
            
        }

        // void set(const IIterator& begin, const IIterator& end){
        //     memset(histogram_all_.get(), 0, sizeof(float)* num_classes_);
        //     for(IIterator it = begin;  it != end; ++ it){
        //         histogram_all_[it->label_] ++ ;               
        //     }
        // }


        float calculate(const IIterator& begin, const IIterator& middle, const IIterator& end){
            float entropy_left = 0.0f;
            float entropy_right = 0.0f;
            memset(histogram_left_.get(), 0 , sizeof(float)*num_classes_);
            memset(histogram_right_.get(), 0, sizeof(float)*num_classes_);
            //memcpy(histogram_right_, histogram_all_, sizeof(float)* num_classes_);
            int count_left = 0 , count_right = 0;
            for(IIterator it = begin, count_left=0; it != middle; ++ it, ++count_left){
                histogram_left_[it->label_] ++ ;
            }
            for(int i = 0; i < num_classes_; ++ i){
                histogram_left_[i] / float(count_left);
            }

            for(IIterator it = middle, count_right=0; it != end; ++ it, ++count_right){
                histogram_right_[it->label_] ++ ;
            }

            for(int i = 0; i < num_classes_; ++i){
                histogram_right_[i] / float(count_right);
            }
            
            for(int i = 0; i < num_classes_; ++ i){
                entropy_left -= histogram_left_[i] * log(histogram_left_[i] + FLOAT_EPS);
            }

            for(int i = 0; i < num_classes_; ++ i){
                entropy_right -= histogram_right_[i] * log(histogram_right_[i]+ FLOAT_EPS);
            }

            return entropy_left/ float(count_left) + entropy_right / float(count_right);

        }
    protected:
        int num_classes_;
        shared_ptr<float> histogram_left_;
        shared_ptr<float> histogram_right_;
        //shared_ptr<float> histogram_all_
        


};






}











#endif