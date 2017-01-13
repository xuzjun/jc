#include <iostream>
#include "TestCaseHelper.h"

_Base::_Base(){
    std::cout << "constructor of _Base" << std::endl;
}
_Base::~_Base(){
    std::cout << "destructor of _Base" << std::endl;
}

_Sub::_Sub(int id):_id(id){
    std::cout<< "_Sub constructor: " << _id << std::endl;
}
_Sub::~_Sub(){
    std::cout << "_Sub destructor: "<< _id << std::endl;
}
void _Sub::f(){
    std::cout << "override the _If 's functions" << _id << std::endl;
}
