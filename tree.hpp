#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>



#include "glog/logging.h"
#include "feature.hpp"
#include "evaluation.hpp"
#include "selector.hpp"
#include "data.hpp"
#include "statistic.hpp"
#include "serialize.hpp"

#include <mutex>

using namespace std;

namespace Beta{

template<typename State>
class Node{
    
    public:
        Node(string name):N_(0.0f),W_(0.0f),Q_(0.0f),P_(0.0f), index_(0), name_(name), flag_(true), parent_(nullptr){
            child_.clear();
            
            
        }



        ~Node(){

        }

        // compute features using 
        void compute_feature(){

        }
    
        //float& sN(){return N_;}
        

        unsigned long & sindex(){return index_;}
        map<unsigned long, Node<State>* >& schild(){return child_;}

        void insert(pair<unsigned long, Node<State>* > elements){
            child_.insert(elements);
        }

        Node<State>* & sparent(){return parent_;}
        bool & sflag(){return flag_;}
        State & sstate(){return state_;}
        int& sdepth(){return depth_;}
        int& stype(){return type_;}
        int& sleft(){return left_;}
        int& sright(){return right_;}
        
        const float N(){return N_;}
        const float W(){return W_;}
        const float Q(){return Q_;}
        const float P(){return P_;}
        const float U(){return U_;}
        const int depth(){return depth_;}
        const string name(){return name_;}
        const unsigned long index(){return index_;}
        const map<unsigned long, Node<State> * > child(){return child_;}
        const Node<State>* parent(){return parent_;}
        const bool flag(){return flag_;}
        const int& type(){return type_;}
        const State& state(){return state_;}
        const int& left(){return left_;}
        const int& right(){return right_;}

        void print_state(){
            LOG(INFO)<<"x0: "<<state_.x0_ <<" y0: "<<state_.y0_<<" x1: "<<state_.x1_<<" y1: "<<state_.y1_<<" xc: "<<state_.xc_<<" yc: "<<state_.yc_<<" t: "<< state_.t_;
        }

    

    protected:
        map<unsigned long, Node<State> * > child_;
        Node<State>* parent_;
        State state_;
        unsigned long index_;
        int depth_;
        string name_;
        float N_;
        float W_;
        float Q_;
        float P_;
        float U_;
        bool flag_; // if flag_ = 1, is leaf node;
        int type_; // type = 1, regression node; type = 2, classification node; type=-1
        
        int left_;
        int right_;

        Statistic* statistic_;
        //static int index;
};


template<typename State>
class Tree{
    typedef typename map<unsigned long, Node<State>* >::iterator Iterator;
    typedef typename vector<Image>::iterator IIterator;
    public:
        Tree(const Config& config):counter_(0){
            L_ = config.configuration_.max_depth();
            feature_ = shared_ptr<Feature<State>  > (new Feature<State>(config));
            int context_patch = config.configuration_.context_patch();
            selector_ = shared_ptr<Selector<State> >(new Selector<State>(- context_patch, context_patch));
            dim_features_ = config.configuration_.dim_features();



            reg_eval_ = shared_ptr<Evaluation> (new RegressionEvaluation(config));
            cls_eval_ = shared_ptr<Evaluation> (new ClassificationEvaluation(config));
            minimum_samples_ = config.configuration_.minimum_samples();

        }
        ~Tree(){

        }

        void add_node(Node<State>* leaf_node, Node<State>* node){
            //leaf_node->

            DLOG(INFO)<< "adding "<< counter_<<" node";
            node->sindex() = ++ counter_;
            //nodes_[counter_] = node;
            nodes_.insert(std::pair<unsigned long, Node<State>* >(counter_,node));
            leaf_node->insert(std::pair<unsigned long, Node<State>* >(counter_,node));
            node->sparent()=leaf_node;

            LOG(INFO)<<"adding finish";
            
            //tree_.push_back(node);
            //leaf_node->child_ = node;
        }

        bool add_node(Node<State>* node){
            DLOG(INFO)<< "adding "<< counter_<<" node: "<< node->name();
            Iterator it = nodes_.find(node->index());
            if(it != nodes_.end()){
                LOG(INFO)<<" tree already has such node";
                return false;
            }
            node->sindex() = ++ counter_;
            nodes_[counter_] = node;
            return true;
        }


        Node<State>* find(int index){
            Iterator it = nodes_.find(index);
            if(it == nodes_.end()){
                LOG(INFO)<<"can not find" << index;
            }
            return it->second;
        }


        void travel(Node<State>* root){       
            queue<Node<State>* > cache;
            cache.push(root);
            while(cache.size()){
                Node<State>* ele = cache.front();
                DLOG(INFO)<<"visit "<< ele->name()<<" child size: "<< ele->schild().size();
                for(Iterator it = ele->schild().begin(); it != ele->schild().end(); ++ it){
                    cache.push(it->second);
                }
                cache.pop();
            }
        }

        // remove given node and its descendant
        void clear_node(Node<State>*  node){
            Iterator it = nodes_.find(node->index());
            if(it == nodes_.end()){
                DLOG(INFO)<<"can not find node "<< node->name(); 
                return;
            }
            Iterator it_child = node->sparent()->schild().find(node->index());
            node->sparent()->schild().erase(it_child);
            queue<Node<State>* > cache;
            cache.push(node);

            // get all nodes in the sub-tree of node and remove these node
            // 
            while(cache.size()){
                Node<State>* ele = cache.front();
                for(Iterator it = ele->schild().begin(); it != ele->schild().end(); ++ it){
                    cache.push(it->second);
                } 
                nodes_.erase(nodes_.find(ele->index()));
                cache.pop();
            }
        }

        void reset_root(Node<State>*  node){
            nodes_.clear();
            add_node(node);
        }

        void select(){
            

        }
        void expand_and_evaluate(){


            // push leaf node into leafs_ for evaluation

        }
        void backup(){

        }

        void run(){
            select();
            expand_and_evaluate();
            backup();

        }

        void train(Data* data){
            Node<State>* node = new Node<State>("Node"+std::to_string(counter_));
            node->sindex() = counter_;
            node->sdepth() = 0;
            add_node(node);
            DLOG(INFO)<<"start training from root";
            train_recurse(data->data_.begin(), data->data_.end(),0);
            


        }


        void test(Data* data){

            for(IIterator it = data->data_.begin() ; it != data.data_->end(); ++it ){
                predict(it->img_, it->prediction_, it->confidence_);
            }
            float correct = 0;
            float total_samples = 0;
            for(IIterator it = data->data_.begin() ; it != data.data_->end(); ++it ){
                if(it->prediction_ == it->label_){
                    ++ correct;
                }
                ++ total_samples;
            }
            LOG(INFO)<<"training accuracy: "<< correct / total_samples;
        }

        void predict(const Mat& image, int & label , float & confidence){
            Node<State>* node = find(0);
            float v = 0;
            while(node->child().size()){
                v =  feature_->extract(image, node->state());
                if(v < node->state().t_){
                    node = find(node->left());
                }else{
                    node = find(node->right());
                }
            }

            //label = ;
            







        }





        void train_recurse(const IIterator& begin, const IIterator& end, int depth){
            IIterator best, it;
            int number_samples = 0;
            for(it = begin; it != end; ++it){
                ++ number_samples;
            }

            if(depth >= L_ || number_samples < minimum_samples_){
                LOG(INFO)<<"return with depth: " << depth <<" number_samples: "<< number_samples; 
                return;
            }

            selector_->random_generation(dim_features_);
            Random random_generator;
            
            
            DLOG(INFO)<<"random generation";

            float max_val = 1e10;
            float val = 0;

            Node<State>* node  = find(counter_);


            for(int i = 0; i < dim_features_; ++ i){
                for(it = begin; it != end; ++ it){
                    it->key_= feature_->extract(it->img_, selector_->selector(i));
                    //std::cout<< it->key_<<" ";
                }

                LOG(INFO)<< "sort" << i ;

                sort(begin,end, compare);

                
                eval_ = random_generator.NextDouble() > 0.5 ? reg_eval_ : cls_eval_;
                for(it  = begin; it != end; ++ it){
                    val  = eval_->calculate(begin, it, end);
                    //val = 0;
                    if(max_val >= val){
                        max_val = val;
                        node->sstate() = selector_->selector(i);
                        node->sstate().t_ = it->key_;
                        best = it;
                    }
                }
            }

            node->print_state();






            Node<State>* node_left = new Node<State>("Node"+std::to_string(counter_+1) );
            LOG(INFO)<< "adding Node "<<std::to_string(counter_+1);
            node->sleft() = counter_+1;
            node_left->sdepth() = depth + 1;
            add_node(node, node_left);
            train_recurse(begin, best, depth+1);

            Node<State>* node_right = new Node<State>("Node"+std::to_string(counter_+1));
            LOG(INFO)<< "adding Node "<<std::to_string(counter_+1);
            node_right->sdepth() = depth + 1;
            node->sright() = counter_+1;
            add_node(node, node_right);
            train_recurse(best, end, depth+1);


            
        }


        const size_t size(){return nodes_.size();}
        const unsigned long counter(){return counter_;}
        const int L(){return L_;}
        const queue<Node<State>* >& leafs(){return leafs_;}
        const std::map<unsigned long, Node<State>* >& nodes(){return nodes_;}
        Node<State>* get_node(int index){
            Iterator it = nodes_.find(index);
            if(it == nodes_.end()){
                DLOG(INFO)<<"can not find node "; 
                return nullptr;
            }
            return it->second;
        }

        const size_t get_size(){
            return nodes_.size();
        }




    protected:
        std::map<unsigned long, Node<State>* > nodes_;
        queue<Node<State>* > leafs_;
        unsigned long counter_;
        shared_ptr <Feature<State> >  feature_;
        shared_ptr <Selector<State> > selector_;
        int dim_features_;

        shared_ptr<Evaluation> reg_eval_;
        shared_ptr<Evaluation> cls_eval_;
        shared_ptr<Evaluation> eval_;





        int L_;
        int minimum_samples_;

};

} //end of namespace Beta

#endif