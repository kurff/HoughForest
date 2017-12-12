#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <stdint.h>
using google::protobuf::Message;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "glog/logging.h"

using namespace std;
namespace Beta{

    void write_txt(Message* message, string file){

        int fd = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        FileOutputStream* output = new FileOutputStream(fd);
        google::protobuf::TextFormat::Print(* message, output);
        delete output;
        close(fd);
    }
    void write_binary(Message* message, string file){

    }


    void read_txt(Message* message, string file){
        int fd = open(file.c_str(), O_RDONLY);
        FileInputStream* input = new FileInputStream(fd);
        bool success = google::protobuf::TextFormat::Parse(input, message);
        delete input;
        close(fd);
    }




}









#endif