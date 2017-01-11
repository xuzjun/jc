#include <iostream>
#include "gtest/gtest.h"
#include "ThreadLocal.h"
#include "IRunnable.h"
#include "Thread.h"
#include "Builder.h"

#include "TestCaseHelper.h"
//TODO: logger
//TODO: isolate the UT  dir

class FRunner : public IRunnable{
public:
    
    static std::shared_ptr<IRunnable> make(){
        return BuilderSptr<FRunner>::make();
    }
    FRunner(){ 
        printf("constructor\n");
    }
    virtual ~FRunner(){
        printf("destructor\n");
    }

    virtual void run(){
        std::cout << "do something in thread " << Thread::id() << std::endl;
    }
};
TEST(FRunnerTest, easyUse){
    auto pir = FRunner::make();
    auto thread = Thread::make(pir);
        
    thread->start();
    thread->wait();
}

//Test Thread 
class TestRoutine : public IRunnable{
public:
    typedef ThreadLocal<int> ThreadLocalType;
    
    static std::shared_ptr<IRunnable> make(std::shared_ptr<ThreadLocalType> sp){
        return BuilderSptrSptr<TestRoutine>::make(sp);
    }
    static std::shared_ptr<IRunnable> make(ThreadLocalType* ptr){
        return BuilderSptr<TestRoutine>::make(ptr);
    }

    TestRoutine(ThreadLocalType * ptl):_ptl(ptl){
        printf("constructor\n");
    }
    virtual ~TestRoutine(){
        printf("destructor\n");
    }
    virtual void run(){
        if(_ptl == NULL){
            printf("Error: thread local <int> is NULL\n");
            return ;
        }
        int i =0 ;
        if(_ptl->get() == NULL)
            _ptl->set(&i);
        assert(_ptl->get() == &i);   
    }
private:
    ThreadLocalType *_ptl;
};

TEST(ThreadTest, useThreadLocal){
    auto sptl = std::make_shared<ThreadLocal<int>>();
    auto trt = TestRoutine::make(sptl);
    auto thread = Thread::make(trt);

    thread->start();
    ASSERT_TRUE(thread->self() == Thread::id());
    thread->wait();

    const int thread_len = 128;
    std::shared_ptr<Thread> tarr[thread_len];
    for( int i = 0 ; i < thread_len; ++i){
        tarr[i] = Thread::make(trt);
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
    typedef ThreadLocal<Logger> ThreadLocalType;

    static std::shared_ptr<IRunnable> make(std::shared_ptr<ThreadLocalType> sp){
        return BuilderSptrSptr<RunLogger>::make(sp);
    }

    RunLogger(ThreadLocalType * tl_log)
    :_tl_log(tl_log){
    }
    virtual ~RunLogger(){
    }
    Logger * getLogger(){
        if(_tl_log->get() == NULL)
            _tl_log->set(new Logger);
        return _tl_log->get();
    }
    virtual void run(){
        char buf[128];
        snprintf(buf, sizeof(buf), "%s:%lu", "hell world", Thread::id());
        getLogger()->info(buf);

    }
private:
    ThreadLocalType * _tl_log;
};

TEST(ThreadTest, runLogger){
    auto tl_log = ThreadLocal<Logger>::make();
    auto r = RunLogger::make(tl_log);
    auto t1 = Thread::make(r);
    t1->start();

    auto t2 = Thread::make(r);
    t2->start();

    t1->wait();
    t2->wait();
}
