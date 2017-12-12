#ifndef __SERIALIZE_HPP__
#define __SERIALIZE_HPP__


#include "proto/configuration.pb.h"
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

#include "tree.hpp"

using namespace std;

namespace Beta{
    class Serialize{
        public:
            Serialize(){

            }

            ~Serialize(){

            }

            template<typename State>
            void serialize(string file, Tree<State>* tree){

                shared_ptr<TreeProto> tree_proto = shared_ptr<TreeProto>(new TreeProto);
                
                


            }

            template<typename State>
            void deserialize(string file, Tree<State>* tree){


            }

            template<typename State>
            void serialize_binary(string file, Tree<State>* tree){

            }
            template<typename State>
            void deserialize_binary(string file, Tree<State>* tree){


            }
        protected:







    };

}










#endif