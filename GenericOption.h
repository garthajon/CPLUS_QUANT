// 
// GenericOption.h
// serving as a template description (header) of the actual GenericOption class GenericOption.cpp

#ifndef __CppOptions__GenericOption__
#define __CppOptions__GenericOption__ 

#include <stdio.h>

// 
// option types based on direction: call or put
enum OptionType {
    OptionType_Call,
    OptionType_Put 
}; 

//
// class that represents a generic option 
// we apply the rigor of the 4 stahdard member functions of a C++ class, namely:
//         1) the constructor (used to initialise the class in a standard way) from the class definition
//         2) the copy constructor: initialising a GenericOption object from an existent GenericOption object
//         3) the destructor used to delete the object (the tilde symbol befoe the function denotes a destructor)
//         4) assignment constructor used to copy the data contents of one object to another object
class GenericOption {
public: 
    GenericOption(double strike, OptionType type, double cost); 
    GenericOption(const GenericOption &p);
    ~GenericOption(); 
    GenericOption &operator=(const GenericOption &p); 

    double valueAtExpiration(double underlyingAtExpiration); 
    double profitAtExpiration(double underlyingAtExpiration); 
private: 
    double m_strike; 
    OptionType m_type; 
    double m_cost; 
}; 

#endif /* defined(__CppOptions__GenericOption__) */
