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
    typedef typename vector<Image>::iterator IIterator;
    public:
        Evaluation(){

        }

        ~Evaluation(){

        }

        virtual float calculate(const IIterator& begin, const IIterator& middle, const IIterator& end)  =0;
        virtual float calculate_single(const IIterator& begin, const IIterator& middle, const IIterator& end, int index)  =0;


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
            IIterator it;
            for(int i = 0; i < num_keypoints_; ++ i){
                mean_left[i] = Point2f(0.0f,0.0f);

                for(it = begin, count = 0; it != middle; ++ it, ++count){
                    mean_left[i] += it->keypoints_[i];
                }
                mean_left[i].x /= float(count) + FLOAT_EPS;
                mean_left[i].y /= float(count) + FLOAT_EPS;

            }
            
            vector<Point2f> mean_right;
            mean_right.resize(num_keypoints_);


            for(int i = 0; i < num_keypoints_; ++ i ){
                mean_right[i] = Point2f(0.0f,0.0f);
                for(it = middle, count=0; it != end; ++ it, ++count){
                    mean_right[i] += it->keypoints_[i];
                }
                mean_right[i].x /= float(count) + FLOAT_EPS;
                mean_right[i].y /= float(count) + FLOAT_EPS;
            }

            float dis_left = 0.0f, dis_right = 0.0f;
            Point2f t;
            for(int i = 0; i < num_keypoints_; ++ i){
                for( it = begin, count=0; it != middle; ++ it, ++count){
                    t = (it->keypoints_[i] - mean_left[i]);
                    dis_left += t.x * t.x + t.y * t.y;
                }
                dis_left /= float(count) + FLOAT_EPS;
                for( it = middle, count=0; it != end; ++ it, ++count){
                    t = (it->keypoints_[i] - mean_right[i]);
                    dis_right += t.x * t.x + t.y * t.y;
                }
                dis_right /= float(count) + FLOAT_EPS;

            }


            return dis_left + dis_right;

        }

        float calculate_single(const IIterator& begin, const IIterator& middle, const IIterator& end, int index){
            Point2f mean_left = Point2f(0.0f,0.0f);
            int count = 0;
            IIterator it;

            
            for(it = begin, count = 0; it != middle; ++ it, ++count){
                mean_left += it->keypoints_[index];
            }
            mean_left.x /= float(count) + FLOAT_EPS;
            mean_left.y /= float(count) + FLOAT_EPS;
        
            Point2f mean_right = Point2f(0.0f,0.0f);      
            for(it = middle, count=0; it != end; ++ it, ++count){
                mean_right += it->keypoints_[index];
            }
            mean_right.x /= float(count) + FLOAT_EPS;
            mean_right.y /= float(count) + FLOAT_EPS;
            

            float dis_left = 0.0f, dis_right = 0.0f;
            Point2f t;

            for( it = begin, count=0; it != middle; ++ it, ++count){
                t = (it->keypoints_[index] - mean_left);
                dis_left += t.x * t.x + t.y * t.y;
            }
            dis_left /= float(count) + FLOAT_EPS;
            for( it = middle, count=0; it != end; ++ it, ++count){
                t = (it->keypoints_[index] - mean_right);
                dis_right += t.x * t.x + t.y * t.y;
            }
            dis_right /= float(count) + FLOAT_EPS;

            


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
            histogram_left_ = new float [num_classes_] ();
            histogram_right_ = new float [num_classes_] ();
            //histogram_all_ = shared_ptr<float>(new float [num_classes_]());

        }
        ~ClassificationEvaluation(){
            delete [] histogram_left_;
            delete [] histogram_right_;
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
            memset(histogram_left_, 0 , sizeof(float)*num_classes_);
            memset(histogram_right_, 0, sizeof(float)*num_classes_);
            //memcpy(histogram_right_, histogram_all_, sizeof(float)* num_classes_);
            int count_left = 0 , count_right = 0;
            IIterator it;
            for(it = begin, count_left=0; it != middle; ++ it, ++count_left){
                histogram_left_[it->label_] ++ ;
            }
            for(int i = 0; i < num_classes_; ++ i){
                histogram_left_[i] / float(count_left);
            }

            for(it = middle, count_right=0; it != end; ++ it, ++count_right){
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

        float calculate_single(const IIterator& begin, const IIterator& middle, const IIterator& end, int index){
            calculate(begin, middle, end);
        }
    protected:
        int num_classes_;
        float* histogram_left_;
        float* histogram_right_;
        //shared_ptr<float> histogram_all_
        


};






}











#endif