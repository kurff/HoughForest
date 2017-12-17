#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

#include "opencv2/opencv.hpp"
using namespace cv;

namespace Beta{
    class Simulation{
        public:
            Simulation(){

            }

            ~Simulation(){

            }

            void deform(const Mat& img){


            }

            void noise(const Mat& img){

            }

            void subsampling(const Mat& img){

            }

            void illumination(const Mat& img){

            }



            Mat& get(){return image_;}

        protected:
            Mat image_;




    };






}
#endif