#include <iostream>
#include "gtest/gtest.h"
#include "ThreadLocal.h"
#include "IRunnable.h"
#include "Thread.h"
#include "BuilderHelper.h"

#include "TestCaseHelper.h"
//TODO: logger

class Runner : public IRunnable{
public:
    Runner(_Base & b){}
    Runner(){}
    ~Runner(){}

    void run(){
        std::cout << "do something in thread " << Thread::id() << std::endl;
    }
};
//TODO: Thread::make(IRunnable & r)????
TEST(RunnerTest, useRef){
    _Base b;
    Runner(b).run();
}

TEST(ThreadTest, easyUse){

//    std::shared_ptr<IRunnable> runner(new Runner);
//    auto t = Thread::make(runner.get());
    Runner r;
    Thread t(r);
    t.start();
    t.wait();
}



//Test Thread 
class TestRoutine : public IRunnable{
public:
    typedef BuilderHelper<TestRoutine> Builder;
    TestRoutine(ThreadLocal<int> * ptl)
    :_ptl(ptl){
    }
    virtual ~TestRoutine(){
    }
    void run(){
        if(_ptl == NULL){
            printf("ERROR: threaLocal<int> is NULL!");
            return ;
        }
        int i =0 ;
        if(_ptl->get() == NULL)
            _ptl->set(&i);
        assert(_ptl->get() == &i);   
    }
private:
    ThreadLocal<int> * _ptl;
};

TEST(ThreadTest, useBuilder){
    auto sptl = std::make_shared<ThreadLocal<int>>();
    //auto p = Builder<TestRoutine>::make();
    //p->run();

    auto p1 = TestRoutine::Builder::make(sptl.get());
    p1->run();
    delete p1;

    auto p3 = TestRoutine::Builder::make_shared(sptl);
    p3->run();
}

/*  

TEST(ThreadTest, useThreadLocal){
    ThreadLocal<int> pi;
    TestRoutine r(pi);

    Thread thread(r);
    thread.start();
    ASSERT_TRUE(thread.self() == Thread::id());
    thread.wait();
    

    const int thread_len = 128;
    std::shared_ptr<Thread> tarr[thread_len];
    for( int i = 0 ; i < thread_len; ++i){
        tarr[i] = std::make_shared<Thread>(r); 
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

TEST(ThreadTest, runLogger){
    auto tl_log = ThreadLocal<Logger>::make();
    std::shared_ptr<IRunnable> r(new RunLogger(tl_log.get()));


    auto t1 = Thread::make(r.get());
    t1->start();

    auto t2 = Thread::make(r.get());
    t2->start();

    t1->wait();
    t2->wait();
}
*/
