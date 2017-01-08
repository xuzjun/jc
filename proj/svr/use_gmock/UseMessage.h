
#ifndef  USEMESSAGE_H
#define  USEMESSAGE_H

#include <string>
 
class Message;
class UseMessage  
{  
public:  
    UseMessage();  
    virtual ~UseMessage();  
    std::string getMessage(Message* msg);  
};  

#endif   /* USEMESSAGE_H */
