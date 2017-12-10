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
        Node<State>* & sparent(){return parent_;}
        bool & sflag(){return flag_;}

        
        const float N(){return N_;}
        const float W(){return W_;}
        const float Q(){return Q_;}
        const float P(){return P_;}
        const float U(){return U_;}
        const string name(){return name_;}
        const unsigned long index(){return index_;}
        const map<unsigned long, Node<State> * > child(){return child_;}
        const Node<State>* parent(){return parent_;}
        const bool flag(){return flag_;}

    

    protected:
        map<unsigned long, Node<State> * > child_;
        Node<State>* parent_;
        State state_;
        unsigned long index_;
        string name_;
        float N_;
        float W_;
        float Q_;
        float P_;
        float U_;
        bool flag_; // if flag == TRUE, keep else remove
        //static int index;
};


template<typename State>
class Tree{
    typedef typename map<unsigned long, Node<State>* >::iterator Iterator;
    typedef typename vector<Image>::iterator IIterator;
    public:
        Tree(const Config& config):counter_(0){
            L_ = config.configuration_.max_depth();
            feature_ = shared_ptr<Feature<State>  > (new Feature(config));
            int context_patch = config.configuration_.context_patch();
            selector_ = shared_ptr<Selector<State> >(new Selector(- context_patch, context_patch));
            dim_features_ = config.configuration_.dim_features();

            reg_eval_ = shared_ptr<Evaluation> (new RegressionEvaluation(config));
            cls_eval_ = shared_ptr<Evaluation> (new ClassificationEvaluation(config));


        }
        ~Tree(){

        }

        void add_node(Node<State>* leaf_node, Node<State>* node){
            //leaf_node->

            DLOG(INFO)<< "adding "<< counter_<<" node";
            node->sindex() = ++ counter_;
            nodes_[counter_] = node;
            leaf_node->schild().insert(std::pair<unsigned long, Node<State>* >(counter_,node));
            node->sparent()=leaf_node;

            
            
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

        void train(){

        }


        void train_recurse(IIterator& begin, IIterator& end){
            selector_->random_generation(dim_features_);
            Random random_generator;



            for(int i = 0; i < dim_features_; ++ i){
                for(IIterator it = begin; it != end; ++ it){
                    it->key_ = feature_->extract(it->img_, selector_->selector(i));
                }
                sort(begin,end, compare);

                eval_ = random_generation.NextDouble() > 0.5 ? reg_val_ : cls_eval_;
              
                for(IIterator it  = begin, it != end; ++ it){
                    eval_->calculate(begin, it, end);


                }

            }

            
        }


        const size_t size(){return nodes_.size();}
        const unsigned long counter(){return counter_;}
        const int L(){return L_;}
        const queue<Node<State>* > leafs(){return leafs_;}
        const std::map<unsigned long, Node<State>* > nodes(){return nodes_;}



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

};

} //end of namespace Beta

#endif