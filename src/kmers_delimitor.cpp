#include "kmers_delimitor.h"
using namespace prefixMatching;
namespace prefixMatching{
    kmers_Delimitor* kmers_Delimitor::_ins = NULL;
    kmers_Delimitor::kmers_Delimitor()
    {
        this->init();
    }
     kmers_Delimitor* kmers_Delimitor::getInstance(){
        if(!_ins){
            _ins = new kmers_Delimitor();
            assert(_ins);
        }
        return _ins;
    }
    void kmers_Delimitor::init(){
        _delimitor[0]='|';
        _delimitor[1]='@';
    }
    char kmers_Delimitor::insideDeli(){
        return this->_delimitor[0];
    }
    char kmers_Delimitor::outsideDeli(){
        return this->_delimitor[1];
    }
    string kmers_Delimitor::classname(){
        return std::string("class::kmers_Delimitor");
    }
}//namespace prefixMatching
