#include "UseMessage.h"
#include "Message.h"

UseMessage::UseMessage(){
}  
  
UseMessage::~UseMessage(){  
}  
  
std::string UseMessage::getMessage(Message* msg){  
    return msg->getMessage();  
}  

