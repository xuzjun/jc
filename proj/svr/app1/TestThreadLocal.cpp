#include "ThreadLocal.h"
#include "gtest/gtest.h"

TEST(ThreadLocalTest, useInThread){
    auto tl = ThreadLocal<int>::make();
    int i = 10;
    tl->set(&i);
    ASSERT_EQ(&i, tl->get());
}

static void * routine1(void * ctx){
    ThreadLocal<int> * pt = (ThreadLocal<int> *) ctx;
    assert(pt && pt->get() == NULL);

    int i =0 ;
    if(pt->get() == NULL)
        pt->set(&i);
    assert(&i == pt->get());
    return NULL;
}

TEST(ThreadLocal, useInMultiThread){
    auto t = ThreadLocal<int>::make();

    const int th_len = 100; //32bit 384*8192K(thread stack size)
    ::pthread_t th[th_len];

    for(int i =0; i < th_len; ++i){
        ::pthread_create(th+i, NULL, routine1, t.get());
    }

    for(int i =0; i < th_len; ++i){
        ::pthread_join(th[i], NULL);
    }
}
