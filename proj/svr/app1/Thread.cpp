#include "Thread.h"
#include "IRunnable.h"
#include "Builder.h"
#include <cassert>
#include <stdio.h>

void * Thread::ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    if(thread && thread->_run){
        thread->_run->run();
    }
    else  if(thread == NULL){
        printf("ERROR: Thread is NULL");
    }
    else{ //(thread->_run == NULL){
        printf("ERROR thread->_run is NULL");
    }
    return NULL;
}

Thread::Thread(IRunnable *  r)
:_run(r){
}

std::shared_ptr<Thread> Thread::make(IRunnable * r){
    return BuilderSptr<Thread>::make(r);
}
std::shared_ptr<Thread> Thread::make(std::shared_ptr<IRunnable> spr){
    return BuilderSptrSptr<Thread>::make(spr);
}

Thread::~Thread(){
}

void Thread::start(){
    ::pthread_create(&_thread, NULL, ThreadEntry, this);
}

void Thread::wait(){
    ::pthread_join(_thread, NULL);
}

Thread::ThreadIdType Thread::id(){
    return (ThreadIdType)::pthread_self();
}

Thread::ThreadIdType Thread::self(){
    return Thread::id();
}
