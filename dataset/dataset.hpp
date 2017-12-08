#ifndef __DATASET_HPP__
#define __DATASET_HPP__
#include <string>
#include <vector>
#include <map>
#include "dataset/anotation.hpp"
#include "glog/logging.h"
#include <fstream>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;



void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}



class Dataset{
    public:
        Dataset(){

        }

        ~Dataset(){

        }
        virtual void get_train_names(string file_name) = 0;
        virtual void get_test_names(string file_name) = 0;
        virtual void read_train_anotation(string path) = 0;
        virtual void read_test_anotation(string path) = 0;
        virtual void visualize_train_anotation(string path, int index) = 0;
        virtual void visualize_test_anotation(string path, int index) = 0;
        virtual void visualize_train_characters(string path, int index) = 0;

        virtual void get_train_keypoints(string path) = 0;

        void visualize(const Mat & image, vector<Box>& boxes){
            Mat img;
            image.copyTo(img);
            for(int i = 0; i < boxes.size(); ++ i){
                Point p0, p1;
                p0.x = boxes[i].sx();
                p0.y = boxes[i].sy();
                p1.x = boxes[i].sx() + boxes[i].sw();
                p1.y = boxes[i].sy() + boxes[i].sh();
                rectangle(img, p0, p1, Scalar(0,0,255), 2 );
                putText( img, boxes[i].name(), p0, FONT_HERSHEY_SIMPLEX,0.03*boxes[i].sh(),Scalar(0,255,0),2); 
            }


            imshow("anotation", img);
            waitKey(0);
        }

        void visualize_character(const Mat& image, ImageAnotation& anotation){
            Mat img;
            image.copyTo(img);
            for(int i = 0; i < anotation.sboxes().size(); ++ i){
                for(int j = 0; j < anotation.sboxes()[i].size(); ++ j){
                    Point p0, p1;
                    p0.x = anotation.sboxes()[i][j].sx();
                    p0.y = anotation.sboxes()[i][j].sy();
                    p1.x = anotation.sboxes()[i][j].sx() + anotation.sboxes()[i][j].sw();
                    p1.y = anotation.sboxes()[i][j].sy() + anotation.sboxes()[i][j].sh();
                    rectangle(img, p0, p1, Scalar(0,0,255), 2 );
                    putText( img, anotation.sboxes()[i][j].name(), p0, FONT_HERSHEY_SIMPLEX,0.03*anotation.sboxes()[i][j].sh(),Scalar(0,255,0),2); 

                }
            }


            imshow("anotation", img);
            waitKey(0);

        }

        


    protected:
        vector<string> train_names_;
        vector<string> test_names_;

};


class ICDAR2013: public Dataset{
    public:

        ICDAR2013():train_anotation_path_("Challenge2_Training_Task1_GT"),test_anotation_path_("Challenge2_Test_Task1_GT"),
        train_image_path_("Challenge2_Training_Task12_Images"),test_image_path_("Challenge2_Test_Task12_Images"),train_characters_path_("Challenge2_Training_Task2_GT"){

        }
        ~ICDAR2013(){

        }

    void get_train_names(string file_name){
        ifstream fin(file_name.c_str(), ios::in);
        if(!fin.is_open()){
            LOG(INFO)<<"can not open "<< file_name;
            return;
        }
        string file;
        while(fin >> file){
            train_names_.push_back(file);
        }
        LOG(INFO)<<"find "<< train_names_.size() <<" files" ;
        fin.close();
    }
    void get_test_names(string file_name){
        ifstream fin(file_name.c_str(), ios::in);
        string file;
        if(!fin.is_open()){
            LOG(INFO)<<"can not open "<< file_name;
            return;
        }
        while(fin >> file){
            test_names_.push_back(file);
        }
        LOG(INFO)<<"find "<< test_names_.size() <<" files" ;
        fin.close();
    }

    void read_train_anotation(string path){
        
        for(int i = 0; i < train_names_.size(); ++ i){
            ifstream fin(path+"/"+train_anotation_path_+"/gt_"+train_names_[i]+".txt", ios::in);
            if(!fin.is_open()){
                LOG(INFO) <<"can not open anotation file";
                return;
            }
            int x=0,y=0,x1=0,y1=0;
            string anotation_name;
            ImageAnotation anotation;
            while(fin >> x >> y >> x1 >> y1 >> anotation_name){
                Box text_box;
                text_box.sx() = x;
                text_box.sy() = y;
                text_box.sw() = x1-x;
                text_box.sh() = y1-y;
                text_box.sname() = anotation_name.substr(1,anotation_name.size()-2);
                anotation.stext_boxes().push_back(text_box);           
            }

            fin.close();

            ifstream fc(path+"/"+train_characters_path_+"/"+train_names_[i]+"_GT.txt", ios::in);
            if(!fc.is_open()){
                LOG(INFO) <<"can not open anotation file"<< train_names_[i];
                return;
            }
            //LOG(INFO) <<"can not open anotation file"<< train_names_[i];
            string text_content;
            anotation.sboxes().clear();
            vector<Box> boxes;
            Box box;
            while(getline(fc, text_content)){
                vector<string> names;
                SplitString(text_content, names, " ");
                if(names.size()<=1){
                    anotation.sboxes().push_back(boxes);
                    boxes.clear();
                }else{
                    stringstream ss;
                    ss << names[5];
                    ss >> box.sx();
                    ss.clear();
                    ss << names[6];
                    ss >> box.sy();
                    ss.clear();
                    ss << names[7];
                    ss >> x1;
                    box.sw() =x1-box.sx();
                    ss.clear();
                    ss << names[8];
                    ss >> y1;
                    box.sh() = y1-box.sy();

                    box.sname() = names[9].substr(1, names[9].size()-3);
                    boxes.push_back(box);

                }


            }
            anotation.sboxes().push_back(boxes);

            fc.close();



            train_anotation_.push_back(anotation);


        }
        LOG(INFO)<< "get "<< train_anotation_.size() <<" anotations";

    }


    



    void read_test_anotation(string path){

        for(int i = 0; i < test_names_.size(); ++ i){
            ifstream fin(path+"/"+test_anotation_path_+"/gt_"+test_names_[i]+".txt", ios::in);
            if(!fin.is_open()){
                LOG(INFO) <<"can not open anotation file";
                return;
            }
            int x=0,y=0,x1=0,y1=0;
            string text_content;
            ImageAnotation anotation;
            while(getline(fin, text_content)){
                vector<string> names;
                SplitString(text_content, names, ",");
                stringstream ss;
                ss << names[0];
                Box text_box;
                ss >> text_box.sx();
                ss.clear();
                ss << names[1];
                ss >> text_box.sy();
                ss.clear();
                ss << names[2];
                ss >> x1;
                text_box.sw() = x1 -text_box.x();
                ss.clear();
                ss << names[3];
                ss >> y1;
                text_box.sh() = y1- text_box.y();
                text_box.sname() = names[4].substr(2, names[4].size()-4);
                anotation.stext_boxes().push_back(text_box);           
            }
            test_anotation_.push_back(anotation);
            fin.close();
        }
        LOG(INFO)<< "get "<< test_anotation_.size() <<" anotations";

    }

    void visualize_train_anotation(string path, int index){
        if(index <0 || index> train_anotation_.size()){
            LOG(INFO) << "exceed the size of train anotation";
            return;
        }

        Mat img = imread(path + "/" + train_image_path_+"/"+train_names_[index]+".jpg");

        if(img.empty()){
            LOG(INFO)<< "can not read image";
            LOG(INFO)<< path + "/" + train_image_path_+"/"+train_names_[index]+".jpg";
            return;
        }

        visualize(img, train_anotation_[index].stext_boxes());
    }


    void get_train_keypoints(string path){

        for(int i = 0 ; i < train_names_.size(); ++ i){
            Mat img = imread(path + "/" + train_image_path_+"/"+train_names_[i]+".jpg");
            Mat mask = imread(path+"/"+train_characters_path_+"/"+train_names_[i]+"_GT.bmp");
            //cout<< path+"/"+train_characters_path_+"/"+train_names_[i]+"_GT.bmp";
            for(int j = 0 ; j < train_anotation_[i].sboxes().size(); ++ j){
                for(int k = 0; k < train_anotation_[i].sboxes()[j].size(); ++ k){
                    Box box = train_anotation_[i].sboxes()[j][k];
                    Rect rect(box.x(),box.y(), box.w(), box.h());
                    
                    Mat sub_img = mask(rect);
                    resize(sub_img,sub_img,Size(120,180));
                    imshow("sub_img", sub_img);
                    Mat canny_img ;
                    Canny(sub_img,canny_img, 10, 100);
                    imshow("canny", canny_img);
                    waitKey(0);
                }
                

            }



        }



    }



    void visualize_test_anotation(string path, int index){
        if(index <0 || index> test_anotation_.size()){
            LOG(INFO) << "exceed the size of test anotation";
            return;
        }
        Mat img = imread(path + "/" + test_image_path_+"/"+test_names_[index]+".jpg");

        if(img.empty()){
            LOG(INFO)<< "can not read image";
            return;
        }
        visualize(img, test_anotation_[index].stext_boxes());

    }

    void visualize_train_characters(string path, int index){
        if(index <0 || index> train_anotation_.size()){
            LOG(INFO) << "exceed the size of train anotation";
            return;
        }

        Mat img = imread(path + "/" + train_image_path_+"/"+train_names_[index]+".jpg");

        if(img.empty()){
            LOG(INFO)<< "can not read image";
            LOG(INFO)<< path + "/" + train_image_path_+"/"+train_names_[index]+".jpg";
            return;
        }

        visualize_character(img, train_anotation_[index]);



    }


    protected:
        vector<ImageAnotation> train_anotation_; 
        vector<ImageAnotation> test_anotation_;
        string train_anotation_path_;
        string test_anotation_path_;
        string train_image_path_;
        string test_image_path_;

        string train_characters_path_;
        



};








#endif