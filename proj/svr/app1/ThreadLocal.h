#ifndef  THREADLOCAL_H
#define  THREADLOCAL_H

#include <pthread.h>
#include <cassert>
#include <memory>
#include "Builder.h"

template <typename Value>
class ThreadLocal{
private:
    ThreadLocal(ThreadLocal & r){
    }
public:
    typedef Value * ValuePtr; //weak_ptr
    static std::shared_ptr<ThreadLocal<Value>> make(){
        return BuilderSptr<ThreadLocal<Value>>::make();
    }

    ThreadLocal(){
       assert(0 == pthread_key_create(&_key, NULL));
    }
    ~ThreadLocal(){
        assert(0 == pthread_key_delete(_key));
    }

    void set(ValuePtr ptr){
        _ptr = ptr;
        assert(0 == pthread_setspecific(_key, (void*)_ptr)); //TODO: error_log
    }

    ValuePtr get(){
        _ptr = static_cast<ValuePtr>(pthread_getspecific(_key));
        return (ValuePtr)_ptr;
    }
private:
    pthread_key_t _key;
    ValuePtr _ptr;
};

#endif   /* THREADLOCAL_H */
