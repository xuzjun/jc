#ifndef  THREADLOCAL_H
#define  THREADLOCAL_H

#include <pthread.h>
#include <cassert>

template <typename Value>
class ThreadLocal{
protected:
    ThreadLocal(){
       assert(0 == pthread_key_create(&_key, NULL));
    }
public:
    typedef Value * ValuePtr;
    static ThreadLocal<Value> * make(){
        return new ThreadLocal<Value>();
    }
    static ThreadLocal<Value> & makeRef(){
        return *(new ThreadLocal<Value>());
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
