#ifndef __EVALUATION_HPP__
#define __EVALUATION_HPP__

#include "data.hpp"
#include <vector>
using namespace std;

namespace Beta{
class RegressionEvaluation{
    typedef typename vector<Image>::iterator IIterator;
    public:
        RegressionEvaluation(){}
        ~RegressionEvaluation(){}
        float calculate(IIterator begin, IIterator middle, IIterator end){
            float xm = 0;
            float ym = 0;


            for(IIterator it = begin; it != middle; ++ it){
                
            }

        }
    protected:


        

};

class ClassificationEvaluation{
    typedef typename vector<Image>::iterator IIterator;
    public:
        ClassificationEvaluation(){}
        ~ClassificationEvaluation(){}
        float calculate(IIterator begin, IIterator middle, IIterator end){
            float xm = 0;
            float ym = 0;

            
            for(IIterator it = begin; it != middle; ++ it){
                
            }

        }
    protected:


}






}











#endif