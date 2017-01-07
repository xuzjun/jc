#ifndef  THREAD_H
#define  THREAD_H

class IRunnable;

#include <pthread.h>

class Thread{
private:
    Thread(IRunnable * r);
public:
    typedef unsigned long ThreadIdType;

    static Thread * make(IRunnable * r);
    static Thread & makeRef(IRunnable * r);
    ~Thread();

    void start();
    void wait();

    static ThreadIdType id();
    ThreadIdType self();

private:
    static void * ThreadEntry(void * ctx);
private:
    pthread_t _thread;
    IRunnable * _run;
};



#endif   /* THREAD_H */
