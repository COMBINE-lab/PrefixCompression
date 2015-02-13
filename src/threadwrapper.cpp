#include "threadwrapper.h"
#include <unistd.h>
namespace prefixMatching{
ThreadWrapper::ThreadWrapper(): _isDetached(0),
                               _pThread(NULL),
                               _self(0)
{
}
/** launch the thread inside*/
void ThreadWrapper::start(){
    this->_pThread = new thread(runThread,(void*)this);
    this->_self = this->_pThread->get_id();
    if(this->_isDetached) this->_pThread->detach();
}
/** set the thread detached*/
void ThreadWrapper::detach(){
    if(!_isDetached)
        this->_pThread->detach();
}
/** get the thread ID*/
prefixMatching::thread::id ThreadWrapper::self(){
    return this->_self;
}
/** the entry function for the thread*/
void ThreadWrapper::runThread(void* arg){
    try{
        if(!arg) throw invalid_argument("invalid thread argument");
        ((ThreadWrapper*)arg)->run();
    }catch(const exception& e){
        cerr<<e.what()<<endl;
        cerr.flush();
        exit(-1);
    }
}
string ThreadWrapper::classname(){
    return std::string("class::ThreadWrapper");
}

void ThreadWrapper::run(){
    cout<<this->classname()<<'\t'<<_self<<endl;
}
ThreadWrapper::~ThreadWrapper(){

}
void ThreadWrapper::join(){
    if(!_isDetached){
        _pThread->join();

    }
}
void ThreadWrapper::yield(){ prefixMatching::this_thread::yield();}
/**
  * sleep for a specified second
  */
void ThreadWrapper::sleep(float sec){prefixMatching::this_thread::sleep_for(chrono::seconds(sec));}
} //namespace algn_ppbwt
