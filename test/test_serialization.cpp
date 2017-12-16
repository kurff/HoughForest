#include "gtest/gtest.h"
#include "../proto/configuration.pb.h"
#include "configure.hpp"
#include "utils/utils.hpp"
#include "tree.hpp"
#include "serialize.hpp"
using namespace Beta;
TEST(SERIALIZE, save){
     Config* config = new Config();
    config->read_from_text("config.txt");
    Tree<int>* tree =new Tree<int>(*config);
    Serialize* ptr_ser = new Serialize();
    ptr_ser ->serialize<int>("1.txt", tree);    
}