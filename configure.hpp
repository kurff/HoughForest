#ifndef __CONFIGURE_HPP__
#define __CONFIGURE_HPP__

#include "proto/configuration.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <stdint.h>
using google::protobuf::Message;
using google::protobuf::io::FileInputStream;
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
    class Configure{

        public:

            ConfigurationProto configuration_;

            void read_from_text(string file){
                int fd = open(file.c_str(), O_RDONLY);
                
                FileInputStream* input = new FileInputStream(fd);
                bool success = google::protobuf::TextFormat::Parse(input, (Message*)(&configuration_));
                delete input;
                LOG(INFO)<<"max_depth "<< configuration_.max_depth();
                LOG(INFO)<<"num_trees " << configuration_.num_trees();
                LOG(INFO)<<"mode " << configuration_.mode();
                LOG(INFO)<<"min_entropy " << configuration_.min_entropy();
                close(fd);
            }


    };



}







#endif