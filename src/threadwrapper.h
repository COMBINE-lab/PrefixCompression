#ifndef THREADWRAPPER_H
#define THREADWRAPPER_H

#include <iostream>
#include <stdio.h>
#include <list>
#include <cassert>
#include <stdexcept>
#include <stdlib.h>
#include "tinythread.h"

using namespace std;
namespace prefixMatching{
class ThreadWrapper
{
public:
    ThreadWrapper();
    void start();
    void join();
    void detach();
    static void runThread(void *p);
    void sleep(float sec);
    prefixMatching::thread::id self();
    virtual std::string classname();
    ~ThreadWrapper();
protected:
    bool                             _isDetached;
    prefixMatching::thread*             _pThread;
    prefixMatching::thread::id          _self;

    void yield();
    virtual void run();
};
} //namespace prefixMatching
#endif // THREADWRAPPER_H
