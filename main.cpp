#include "data.hpp"
#include "serialize.hpp"
#include "state.hpp"
#include "tree.hpp"
#include "configure.hpp"

using namespace Beta;
int main(int argc, char* argv[]){
    if(argc <= 1 || argc >=3){
        LOG(INFO)<<"./main config.txt";
        return -1;
    }


    Config* config = new Config();
    config->read_from_text(argv[1]);

    Tree<State>* tree = new Tree<State>(*config);

    Data* data = new Data();

    



    





    return 0;
}