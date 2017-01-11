#ifndef  IRUNNABLE_H
#define  IRUNNABLE_H

class IRunnable{
public:
    IRunnable(){}
    virtual ~IRunnable(){}
    virtual void run()  = 0;
};

#endif   /* IRUNNABLE_H */
