#ifndef  THREAD_H
#define  THREAD_H


#include <memory>
#include <pthread.h>

class IRunnable;

class Thread{
private:
public:

    static std::shared_ptr<Thread> make(IRunnable * r);
    static std::shared_ptr<Thread> make(std::shared_ptr<IRunnable> spr);

    Thread(IRunnable * r);
    ~Thread();

    void start();
    void wait();

    typedef unsigned long ThreadIdType;
    static ThreadIdType id();
    ThreadIdType self();

private:
    static void * ThreadEntry(void * ctx);
private:
    pthread_t _thread;
    IRunnable * _run;
};



#endif   /* THREAD_H */
