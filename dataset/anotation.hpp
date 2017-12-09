#ifndef __ANOTATION_HPP__
#define __ANOTATION_HPP__

#include <vector>
#include <string>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;

class Box{
    public:
        Box(){

        }
        ~Box(){

        }

        const float confidence(){return confidence_;}
        const string name(){return name_;}
        const int x(){return x_;}
        const int y(){return y_;}
        const int w(){return w_;}
        const int h(){return h_;}

        float & sconfidence(){return confidence_;}
        string & sname(){return name_;}
        int& sx(){return x_;}
        int& sy(){return y_;}
        int& sw(){return w_;}
        int& sh(){return h_;}




    protected:
        float confidence_;
        string name_;
        int x_;
        int y_;
        int w_;
        int h_;
};






class ImageAnotation{
    public:
        ImageAnotation(){

        }
        ~ImageAnotation(){

        }

        vector<vector<Box> > & sboxes(){return boxes_;}
        vector<vector<string> > & sground_truth_name(){ return ground_truth_name_;}
        string & sfile_name(){ return file_name_;}
        //vector<string>& stext_ground_truth(){return text_ground_truth_;}
        vector<Box>& stext_boxes(){return text_boxes_;}

        const vector<vector<Box> > boxes(){return boxes_;}
        const vector<vector<string> > ground_truth_name(){return ground_truth_name_;}
        const string file_name(){return file_name_;}
        const vector<Box> text_boxes(){return text_boxes_;}

        vector< vector<Point*> > & strain_keypoints(){return train_keypoints_;}

        const vector< vector<Point*> > train_keypoints(){return train_keypoints_;}

    protected:
        vector<vector<Box> > boxes_;
        vector<Box> text_boxes_;
        //vector<string> text_ground_truth_;
        vector<vector<string> > ground_truth_name_;
        string file_name_;
        vector< vector<Point*> > train_keypoints_;
        vector< vector<Point*> > test_keypoints_;


};




class Anotation{
    public:
        Anotation(){

        }
        ~Anotation(){

        }

        vector<Point> & skeypoints(){return keypoints_;}

        const vector<Point> keypoints(){return keypoints_;}

    protected:
        vector<Point> keypoints_;


};







#endif