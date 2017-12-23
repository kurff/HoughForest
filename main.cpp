#include "data.hpp"
#include "serialize.hpp"
#include "state.hpp"
#include "tree.hpp"
#include "configure.hpp"
#include <iostream>
using namespace std;
using namespace Beta;
int main(int argc, char* argv[]){
    if(argc <= 1 || argc >=3){
        LOG(INFO)<<"./main config.txt";
        return -1;
    }

    std::cout<< argv[1]<<std::endl;

    Config* config = new Config();
    config->read_from_text(argv[1]);
    


    Tree<State>* tree = new Tree<State>(*config);


    Data* data = new Data(config->configuration_.num_keypoints(),config->configuration_.height(),
    config->configuration_.width());

    
    data->load_data(config->configuration_.path(), config->configuration_.file_list());
    data->load_neg(config->configuration_.path(),config->configuration_.neg_file_list());



    shared_ptr<Serialize> serialize = shared_ptr<Serialize>(new Serialize());
    if(config->configuration_.mode() == 1){
        tree->train(data);
        //serialize->serialize_binary<State>(config->configuration_.save_path(), tree); 
        tree->test(data);
    }
    



    





    return 0;
}