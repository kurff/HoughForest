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

#include "utils/utils.hpp"
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
                
                const size_t tree_size = tree->get_size();
                for(size_t i = 0; i < tree_size; ++ i){
                    Node<State>* node = tree->get_node(i);
                    NodeProto* node_proto = tree_proto->add_nodes();
                    node_proto->set_depth(node->depth());
                    //node_proto->set_depth(1);
                    node_proto->set_index(node->index());
                }
                //tree_proto->set
                tree_proto->set_counter(tree->counter());
                write_txt(tree_proto.get(),file);

                

                
                


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