#include <iostream>
#include "ThreadLocal.h"
#include "IRunnable.h"
#include "Thread.h"
//TODO: logger
//TODO: use gtest & gmock


//Test the ThreadLocal
void testThreadLocal(){
    ThreadLocal<int> * tl = ThreadLocal<int>::make();
    int i = 10;
    tl->set(&i);
    assert(tl->get() == &i);

    ThreadLocal<int> &tlref = ThreadLocal<int>::makeRef();
    tlref.set(&i);
    assert(tlref.get() == &i);

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

void test_threadLocal_in_multi_pthread(){
    ThreadLocal<int> * t = ThreadLocal<int>::make();

    const int th_len = 128;
    ::pthread_t th[th_len];

    for(int i =0; i < th_len; ++i){
        ::pthread_create(th+i, NULL, routine1, t);
    }

    for(int i = th_len - 1; i >= 0; --i){
        ::pthread_join(th[i], NULL);
    }
    delete t;
}


//Test Thread 
class TestRoutine : public IRunnable{
    ThreadLocal<int> * _tl;
public:
    TestRoutine(ThreadLocal<int> * tl)
    :_tl(tl){
    }
    ~TestRoutine(){
    }

    void run(){
        assert(_tl != NULL && _tl->get() == NULL);
        //mprintf("thread id is :%lu\n", Thread::id());

        int i =0 ;
        if(_tl->get() == NULL)
            _tl->set(&i);
        assert(_tl->get() == &i);   
    }
};

void testThread(){
    ThreadLocal<int> * pi = ThreadLocal<int>::make();
    IRunnable * r = new TestRoutine(pi);

    Thread * t = Thread::make(r);
    t->start();
    assert(t->self() == Thread::id());
    t->wait();

    Thread & tr = Thread::makeRef(r);
    tr.start();
    tr.wait();

    const int thread_len = 128;
    Thread * tarr[thread_len] = {0};
    for( int i = 0 ; i < thread_len; ++i){
        tarr[i] = Thread::make(r); 
        tarr[i]->start();
    }
    for(int i =0; i < thread_len; ++i){
        tarr[i]->wait();
    }
}

int main(int argc, char * argv[]){
    testThreadLocal();
    test_threadLocal_in_multi_pthread();
    testThread();
    return 0;
}
