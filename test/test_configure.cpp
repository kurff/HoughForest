#include "gtest/gtest.h"
#include "../proto/configuration.pb.h"
#include "configure.hpp"
#include "utils/utils.hpp"
using namespace Beta;
TEST(SELECTOR, generation){
    Config* config = new Config();
    config->read_from_text("config.txt");
}

TEST(TreeProto, save){
    TreeProto* tree_proto = new TreeProto();
    //tree_proto->



}

TEST(StateProto, save){
    StateProto* state_proto = new StateProto();
    state_proto->set_x0(1);
    state_proto->set_y0(1);
    state_proto->set_y1(2);
    state_proto->set_x1(2);
    state_proto->set_xc(3);
    state_proto->set_yc(4);
    state_proto->set_t(1.0f);
    write_txt(state_proto, "state.txt");
}

TEST(PointProto, save){
    shared_ptr<PointProto> point_proto = shared_ptr<PointProto>(new PointProto());
    point_proto->set_x(1.2);
    point_proto->set_y(1.5);
    write_txt((point_proto.get()),"point.txt");
    PointProto* proto = new PointProto();
    read_txt(proto, "point.txt");
    LOG(INFO)<<"x:" <<proto->x() <<" y: " << proto->y();
}

TEST(StatisticProto, save){

}

TEST(NodeProto,save){

}



