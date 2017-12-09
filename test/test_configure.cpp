#include "gtest/gtest.h"
#include "../proto/configuration.pb.h"
#include "configure.hpp"
using namespace Beta;
TEST(SELECTOR, generation){
    Config* config = new Config();
    config->read_from_text("config.txt");
    





}