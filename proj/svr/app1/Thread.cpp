#include "Thread.h"
#include "IRunnable.h"
#include <cassert>

void * Thread::ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    assert(thread != NULL);
    assert(thread->_run);
    thread->_run->run();
    return NULL;
}

Thread::Thread(IRunnable *  r)
:_run(r){
}

std::shared_ptr<Thread> Thread::make(IRunnable * r){
    return std::make_shared<Thread>(r);
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
