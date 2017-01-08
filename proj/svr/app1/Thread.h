#ifndef  THREAD_H
#define  THREAD_H


#include <memory>
#include <pthread.h>

class IRunnable;

class Thread{
public:
    typedef unsigned long ThreadIdType;

    static std::shared_ptr<Thread> make(IRunnable * r);

    Thread(IRunnable * r);
    ~Thread();

    void start();
    void wait();

    static ThreadIdType id();
    ThreadIdType self();

private:
    static void * ThreadEntry(void * ctx);
private:
    pthread_t _thread;
    IRunnable* _run;
};



#endif   /* THREAD_H */
