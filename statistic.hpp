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
            Statistic(int dim_reg, int dim_cls): dim_reg_(dim_reg), dim_cls_(dim_cls){
                
                
            }
            ~Statistic(){

            }

            const int& dim_reg(){return dim_reg_;}
            const int& dim_cls(){return dim_cls_;}

            void init_cls(){
                cls_statistic_ = new float [dim_cls_] ();
            }

            void destroy_cls(){
                delete [] cls_statistic_;
            }

            void init_reg(){
                reg_statistic_ = new Point2f[dim_reg_]();
            }
            void destroy_reg(){
                delete [] reg_statistic_;
            }

            void run_cls(const IIterator& begin, const IIterator& end ){
                
                //memset(cls_statistic_, 0 , sizeof(float)* dim_);
                int count = 0;
                for(IIterator it =begin; it != end; ++ it, ++ count){
                    cls_statistic_[it->label_] ++;
                }
                for(int i = 0; i < dim_cls_; ++ i){
                    cls_statistic_[i] /= float(count) + 1e-6;
                }

            }
            void run_reg(const IIterator& begin, const IIterator& end){
                
                for(int i = 0; i < dim_reg_; ++ i){
                    reg_statistic_[i] = Point2f(0.0f,0.0f);
                    int count = 0 ; 
                    for(IIterator it =begin; it != end; ++ it, ++ count){
                       reg_statistic_[i] +=  it->keypoints_[i];
                    }
                    reg_statistic_[i].x /= float(count) + 1e-6;
                    reg_statistic_[i].y /= float(count) + 1e-6;
                }


            }
        protected:
            Point2f* reg_statistic_;
            int dim_reg_;

        protected:
            float* cls_statistic_;
            int dim_cls_;

            


    };
}
#endif