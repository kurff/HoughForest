#ifndef __STATISTIC_HPP__
#define __STATISTIC_HPP__

#include "opencv2/opencv.hpp"
using namespace cv;
#include "data.hpp"
#include <vector>
using namespace std;
namespace Beta{
    class Statistic{
        typedef typename vector<Image>::iterator IIterator;
        public:
            Statistic(){

            }
            ~Statistic(){

            }

            virtual const int& dim() = 0 ;
            virtual void run(const IIterator& begin, const IIterator& end ) = 0;
        protected:
    };

    class ClsStatistic: public Statistic{


        public:
            ClsStatistic(int dim):dim_(dim){
                cls_statistic_ = shared_ptr<float>(new float [dim_] );
            }
            ~ClsStatistic(){

            }

            const int & dim(){return dim_;}
            void run(const IIterator& begin, const IIterator& end){
                memset(cls_statistic_.get(), 0 , sizeof(float)* dim_);
                int count = 0;
                for(IIterator it =begin; it != end; ++ it, ++ count){
                    cls_statistic_[it->label_] ++;
                }
                for(int i = 0; i < dim_; ++ i){
                    cls_statistic_[i] /= float(count) + 1e-6;
                }
            }
        protected:
            shared_ptr<float> cls_statistic_;
            int dim_;
    };

    class RegStatistic: public Statistic{
        public:
            RegStatistic(int dim):dim_(dim){
                reg_statistic_ = shared_ptr<Point2f>(new Point2f[dim_]());

            }

            ~RegStatistic(){

            }

            const int& dim(){return dim_;}
            void run(const IIterator& begin, const IIterator& end){

                for(int i = 0; i < dim_; ++ i){
                    reg_statistic_[i] = Point2f(0.0f,0.0f);
                    int count = 0 ; 
                    for(IIterator it =begin; it != end; ++ it, ++ count){
                       reg_statistic_[i] +=  it->keypoints_[i];
                    }
                    reg_statistic_[i] /= float(count) + 1e-6;
                }
            }

        protected:
            shared_ptr<Point2f> reg_statistic_;
            int dim_;

    }



}









#endif