#ifndef __FEATURE_HPP__
#define __FEATURE_HPP__
#include "configure.hpp"
namespace Beta{

template<typename State>
class Feature{
    public:
        Feature(const Config& config): config_(config){}
        ~Feature(){}

        float extract(const cv::Mat& image, const State& state){
            int x0 = state.xc_ + state.x0_;
            int y0 = state.yc_ + state.y0_;
            int x1 = state.xc_ + state.x1_;
            int y1 = state.yc_ + state.y1_;
            int width = config_.configuration_.width();
            
            int height = config_.configuration_.height();
            x0 = x0 <0? x0 + width: x0;
            x0 = x0 >= width? x0 -width:x0;

            x1 = x1 <0? x1 + width: x1;
            x1 = x1 >= width? x1 -width:x1;

            y0 = y0 <0? y0 + height: y0;
            y0 = y0 >= height? y0 -height:y0;

            y1 = y1 <0? y1 + height: y1;
            y1 = y1 >= height? y1 -height:y1;

             
            Vec3b v1 = image.at<Vec3b>(y1,x1);
            Vec3b v0 = image.at<Vec3b>(y0,x0);

            float v = max( float(v1.val[0]) - float(v0.val[0]), 
            float(v1.val[1]) - float(v0.val[1]) );
            float vmax = max(v, float(v1.val[2]) - float(v0.val[2]) );
            return vmax;
        }



    protected:
        Config config_;
        

};

}





#endif