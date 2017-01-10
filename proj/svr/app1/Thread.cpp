#include "Thread.h"
#include "IRunnable.h"
#include <cassert>

void * Thread::ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    assert(thread != NULL);
    thread->_run.run();
    return NULL;
}

Thread::Thread(IRunnable &  r)
:_run(r){
}

Thread::Thread(IRunnable * pr)
:_run(*pr){
}

std::shared_ptr<Thread> Thread::make(IRunnable * r){
    assert(r);
    return std::make_shared<Thread>(*r);
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
