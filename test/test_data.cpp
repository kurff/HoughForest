#include "gtest/gtest.h"
#include "dataset/dataset.hpp"


TEST(ICDAR2013, readName){
    Dataset* dataset = new ICDAR2013();
    dataset->get_train_names("../train.txt");
    string path = "/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/";
    dataset->read_train_anotation(path);
    //for(int i = 0; i < 100; ++ i){
        //dataset->visualize_train_characters(path,i);
    //}
    dataset->get_train_keypoints(path);

    

    // dataset->get_test_names("../test.txt");
    // string path = "/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/";
    // dataset->read_test_anotation(path);
    // for(int i = 0; i < 100; ++ i){
    //     dataset->visualize_test_anotation(path,i);
    // }
}

