
#ifndef  TESTCASEHELPER_H
#define  TESTCASEHELPER_H


class _Base{
public:
    _Base();
    virtual ~_Base();
};

class _If{
public:
    _If(){}
    ~_If(){}
    virtual void f() = 0;
};

class _Sub : public _Base , public _If{
public:
    _Sub(int id = 0);
    ~_Sub();

    virtual void f();
private:
    int _id;
};

#endif   /* TESTCASEHELPER_H */
