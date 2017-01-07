#include "Thread.h"
#include "IRunnable.h"
#include <cassert>

void * Thread::ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    assert(thread != NULL);
    assert( thread->_run);
    thread->_run->run(); 
    return NULL;
}

Thread::Thread(IRunnable * r)
:_run(r){
}

Thread * Thread::make(IRunnable * r){
    return new Thread(r);
}
Thread & Thread::makeRef(IRunnable * r){
    return  *(Thread::make(r));
}

Thread::~Thread(){
    _run = NULL;
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
