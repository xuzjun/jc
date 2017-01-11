
#ifndef  BUILDERHELPER_H
#define  BUILDERHELPER_H

#include <memory>

//builderPtr : * ptr = make(arg...) &&  * ptr = make(const arg...)
template <typename T>
class BuilderPtr{
public:
    //For the non-const type  ref
    static T * 
    make(){
        return new T();
    }
    template <typename Arg1>
    static T * 
    make(Arg1 & arg1){
        return new T(arg1);
    }
    template <typename Arg1, typename Arg2>
    static T * 
    make(Arg1 & arg1, Arg2 & arg2){
        return new T(arg1, arg2);
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static T * 
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3){
        return new T(arg1, arg2, arg3);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static T * 
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3
        , Arg4 & arg4){
        return new T(arg1, arg2, arg3, arg4);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static T * 
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3
        , Arg4 & arg4, Arg5 & arg5){
        return new T(arg1, arg2, arg3, arg4, arg5);
    }


    //for const ref type
    template <typename Arg1>
    static T * 
    make(const Arg1 & arg1){
        return new T(arg1);
    }
    template <typename Arg1, typename Arg2>
    static T * 
    make(const Arg1 & arg1, const Arg2 & arg2){
        return new T(arg1, arg2);
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static T * 
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3){
        return new T(arg1, arg2, arg3);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static T * 
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3
        , const Arg4 & arg4){
        return new T(arg1, arg2, arg3, arg4);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static T * 
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3
        , const Arg4 & arg4, const Arg5 & arg5){
        return new T(arg1, arg2, arg3, arg4, arg5);
    }
};

//builderSptr : sp = make(args...); &&  sp = make(const args ...)
template <typename T>
class BuilderSptr{
public:
    //For the non-const type  ref
    static std::shared_ptr<T>
    make(){
        return std::make_shared<T>();
    }
    template <typename Arg1>
    static std::shared_ptr<T>
    make(Arg1 & arg1){
        return std::make_shared<T>(arg1);
    }
    template <typename Arg1, typename Arg2>
    static std::shared_ptr<T>
    make(Arg1 & arg1, Arg2 & arg2){
        return std::make_shared<T>(arg1, arg2);
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static std::shared_ptr<T>
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3){
        return std::make_shared<T>(arg1, arg2, arg3);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static std::shared_ptr<T>
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3
        , Arg4 & arg4){
        return std::make_shared<T>(arg1, arg2, arg3, arg4);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static std::shared_ptr<T>
    make(Arg1 & arg1, Arg2 & arg2, Arg3 & arg3
        , Arg4 & arg4, Arg5 & arg5){
        return std::make_shared<T>(arg1, arg2, arg3, arg4, arg5);
    }


    //for const ref type
    template <typename Arg1>
    static std::shared_ptr<T>
    make(const Arg1 & arg1){
        return std::make_shared<T>(arg1);
    }
    template <typename Arg1, typename Arg2>
    static std::shared_ptr<T>
    make(const Arg1 & arg1, const Arg2 & arg2){
        return std::make_shared<T>(arg1, arg2);
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static std::shared_ptr<T>
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3){
        return std::make_shared<T>(arg1, arg2, arg3);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static std::shared_ptr<T>
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3
        , const Arg4 & arg4){
        return std::make_shared<T>(arg1, arg2, arg3, arg4);
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static std::shared_ptr<T>
    make(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3
        , const Arg4 & arg4, const Arg5 & arg5){
        return std::make_shared<T>(arg1, arg2, arg3, arg4, arg5);
    }
};

//builderSptrSptr : sp = make(sp); &&  sp = make(sp)
template <typename T>
class BuilderSptrSptr{
public:
    static std::shared_ptr<T> make(){
        return std::make_shared<T>();
    }

    //for sptr
    template <typename Arg1>
    static std::shared_ptr<T> 
    make(std::shared_ptr<Arg1> & arg1){
        return std::make_shared<T>(arg1.get());
    }
    template <typename Arg1, typename Arg2>
    static std::shared_ptr<T> 
    make(std::shared_ptr<Arg1> & arg1
        , std::shared_ptr<Arg2> & arg2){
        return std::make_shared<T>(arg1.get(), arg2.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static std::shared_ptr<T> 
    make(std::shared_ptr<Arg1> & arg1
        , std::shared_ptr<Arg2> & arg2
        , std::shared_ptr<Arg3> & arg3){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static std::shared_ptr<T> 
    make(std::shared_ptr<Arg1> & arg1
        , std::shared_ptr<Arg2> & arg2
        , std::shared_ptr<Arg3> & arg3
        , std::shared_ptr<Arg4> & arg4){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get(), arg4.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static std::shared_ptr<T> 
    make(std::shared_ptr<Arg1> & arg1
        , std::shared_ptr<Arg2> & arg2
        , std::shared_ptr<Arg3> & arg3
        , std::shared_ptr<Arg4> & arg4
        , std::shared_ptr<Arg5> & arg5){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get(), arg4.get(), arg5.get());
    }

    //for const sptr
    template <typename Arg1>
    static std::shared_ptr<T> 
    make(const std::shared_ptr<Arg1> & arg1){
        return std::make_shared<T>(arg1.get());
    }
    template <typename Arg1, typename Arg2>
    static std::shared_ptr<T> 
    make(const std::shared_ptr<Arg1> & arg1
        , const std::shared_ptr<Arg2> & arg2){
        return std::make_shared<T>(arg1.get(), arg2.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3>
    static std::shared_ptr<T> 
    make(const std::shared_ptr<Arg1> & arg1
        , const std::shared_ptr<Arg2> & arg2
        , const std::shared_ptr<Arg3> & arg3){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4>
    static std::shared_ptr<T> 
    make(const std::shared_ptr<Arg1> & arg1
        , const std::shared_ptr<Arg2> & arg2
        , const std::shared_ptr<Arg3> & arg3
        , const std::shared_ptr<Arg4> & arg4){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get(), arg4.get());
    }
    template <typename Arg1, typename Arg2, typename Arg3
        , typename Arg4, typename Arg5>
    static std::shared_ptr<T> 
    make(const std::shared_ptr<Arg1> & arg1
        , const std::shared_ptr<Arg2> & arg2
        , const std::shared_ptr<Arg3> & arg3
        , const std::shared_ptr<Arg4> & arg4
        , const std::shared_ptr<Arg5> & arg5){
        return std::make_shared<T>(arg1.get(), arg2.get()
            , arg3.get(), arg4.get(), arg5.get());
    }
};

#endif   /* BUILDERHELPER_H */
