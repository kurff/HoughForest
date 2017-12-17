#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <stdint.h>
using google::protobuf::Message;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;



#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "glog/logging.h"
#include <stdint.h>
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
        fstream output(file, ios::out | ios::trunc | ios::binary);
        message->SerializeToOstream(&output);
    }

    void read_binary(Message* message, string file){
        int fd = open(file.c_str(), O_RDONLY);
        ZeroCopyInputStream* raw_input = new FileInputStream(fd);
        CodedInputStream* coded_input = new CodedInputStream(raw_input);
        coded_input->SetTotalBytesLimit(INT_MAX, 536870912);
        bool success = message->ParseFromCodedStream(coded_input);
        delete coded_input;
        delete raw_input;
        close(fd);

    }

    void read_txt(Message* message, string file){
        int fd = open(file.c_str(), O_RDONLY);
        FileInputStream* input = new FileInputStream(fd);
        bool success = google::protobuf::TextFormat::Parse(input, message);
        delete input;
        close(fd);
    }

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


}









#endif