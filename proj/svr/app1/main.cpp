#include <iostream>
#include "ThreadLocal.h"
#include "IRunnable.h"
#include "Thread.h"
#include <memory>
//TODO: logger
//TODO: use gtest & gmock


void testThreadLocal(){
    auto tl = ThreadLocal<int>::make();
    int i = 10;
    tl->set(&i);
    assert(tl->get() == &i);
}

void * routine1(void * ctx){
    ThreadLocal<int> * pt = (ThreadLocal<int> *) ctx;

    assert(pt->get() == NULL);

    int i =0 ;
    if(pt->get() == NULL)
        pt->set(&i);
    assert(pt->get() == &i);   
    return NULL;
}

void testThreadLocalInMultiThread(){
    auto t = ThreadLocal<int>::make();

    const int th_len = 128;
    ::pthread_t th[th_len];

    for(int i =0; i < th_len; ++i){
        ::pthread_create(th+i, NULL, routine1, t.get());
    }

    for(int i = th_len - 1; i >= 0; --i){
        ::pthread_join(th[i], NULL);
    }
}


//Test Thread 
class TestRoutine : public IRunnable{
    ThreadLocal<int> * _tl;
public:
    TestRoutine(ThreadLocal<int> * tl)
    :_tl(tl){
    }
    virtual ~TestRoutine(){
    }

    void run(){
        assert(_tl != NULL && _tl->get() == NULL);
        //printf("thread id is :%lu\n", Thread::id());

        int i =0 ;
        if(_tl->get() == NULL)
            _tl->set(&i);
        assert(_tl->get() == &i);   
    }
};

void testThread(){
    auto pi = ThreadLocal<int>::make();
    std::shared_ptr<IRunnable> r(new TestRoutine(pi.get()));
    auto t = std::make_shared<Thread>(r.get());
    t->start();
    assert(t->self() == Thread::id());
    t->wait();

    const int thread_len = 128;
    std::shared_ptr<Thread> tarr[thread_len];
    for( int i = 0 ; i < thread_len; ++i){
        tarr[i] = std::make_shared<Thread>(r.get()); 
        tarr[i]->start();
    }
    for(int i =0; i < thread_len; ++i){
        tarr[i]->wait();
    }
}

class Logger{
public:
    void info(const char * msg){
        printf("INFO:%s\n",msg);
    }
    Logger(int i){
        printf("constructor %d\n", i);
    }
    Logger(){
        printf("constructor\n");
    }
    ~Logger(){
        printf("destructor\n");
    }
};

class RunLogger : public IRunnable {
public:
    RunLogger(ThreadLocal<Logger>* tl_log)
    :_tl_log(tl_log){
    }
    virtual ~RunLogger(){
    }
    Logger * getLogger(){
        if(_tl_log->get() == NULL)
            _tl_log->set(new Logger);
        return _tl_log->get();
    }
    void run(){
        char buf[128];
        snprintf(buf, sizeof(buf), "%s:%lu", "hell world", Thread::id());
        getLogger()->info(buf);
    }
private:
    ThreadLocal<Logger> * _tl_log;
};

void testLogger(){
    auto tl_log = ThreadLocal<Logger>::make();
    std::shared_ptr<IRunnable> r(new RunLogger(tl_log.get()));
    auto t1 = Thread::make(r.get());
    t1->start();

    auto t2 = Thread::make(r.get());
    t2->start();

    t1->wait();
    t2->wait();
}

void  testSharedPtr(){
    //std::shared_ptr<Logger> plogger(new Logger);
    //auto plogger = std::make_shared<Logger>();
    auto plogger = std::make_shared<Logger>(10);
    plogger->info("shared ptr");
}
void testWeakPtr(){
    // create weak_ptr from shared_ptr
    auto m = std::make_shared<Logger>(10);
    std::weak_ptr<Logger> w(m);
}

//int main(int argc, char * argv[]){
//    testThreadLocal();
//    testThreadLocalInMultiThread();
//    testThread();
//    testLogger();
//    testSharedPtr();
//   return 0;
//}
