
#ifndef  MESSAGE_H
#define  MESSAGE_H

#include <string>  
class Message  
{  
public:  
    virtual ~Message() {}  
    virtual std::string getMessage() = 0;  
};  

#endif   /* MESSAGE_H */
