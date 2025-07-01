// 
// GenericOption.cpp

#include "GenericOption.h" 
#include <iostream>

// the std namespace in C++ contains many standard library components (functions, objects etc.)
// note that std is shortform for 'standard', the std namespace contains built in classes and functions

// thus the object 'cout' is part of the c++ iostream used to display/output values to the console screen
using std::cout; 
// endl is also used when outputting values to the console screen, but it is used to insert a new line and/or
// flush the output buffer
using std::endl;

// the first of the 4 canonical class functions/constructors is defined, this being the main constructor 
// which will be used to build any GenericOption objects instantiated from the GenericOption class template definition
// note the 3 variables passed into the constructor (a strike price an option type and a cost)
// utlised to build/instantiate the GenericOption object from the GenericOption class template
// a strike price, definition of option type and a cost are 3 typical attributes of an options contract
// we wil note (in passing) that the parameter 'OptionType' has been defined in the header file for this class 
// as a type 'enum' (i.e. an enumerator or an array) with two possible values, namely: OptionType_Call, OptionType_Put
// the standard 'enum' object in C++ allows users to define a set of named values 
GenericOption::GenericOption(double strike, OptionType type, double cost)
: m_strike(strike),
  m_type(type),
  m_cost(cost) 
{ 

} 

// the second of the 4 canonical class functions/constructors is defined, namely a constructor which builds a 
// GenericOption object from an existent GenericOption object rather than from a GenericOption class
GenericOption::GenericOption(const GenericOption &p)
: m_strike(p.m_strike),
  m_type(p.m_type), 
  m_cost(p.m_cost) 
{

}

// the third of the 4 canonical class functions/constructors is defined, namely the destructor 
// thus when an object is destroyed using a deletion the destructor will release any resources allocated
// to it during its lifetime such as memory, network connections etc. 
GenericOption::~GenericOption() 
{ 
} 

// 
// assignment operator
// the fourth of the 4 canonical class functions which is used to copy the variable values from one object
// to another object
// note the check to verify whether the values in the current (this) object match the values in the parameter
// object  (&p) before setting the type, cost and strike variables of the current object to be that of the parameter
// object
GenericOption &GenericOption::operator=(const GenericOption &p) 
{ 
if (this != &p)
{ 
m_type = p.m_type;
m_strike = p.m_strike;
m_cost = p.m_cost; 
} 
return *this; 
} 

// 
// A function to compute the value of the option at expiration date.
// how the value is computed depends on the type of option (CALL or PUT) and the strike price.
// note that by default the value of the option at expiry is set to be zero i.e. to expire worthless.
// if the option type is a call option, the option will only have value if the value of the underlying 
// is greater than the strike price at expiry
// and if the option type is a put option then the option will only have value if the value of the underlying
// is less than the strike price at expiry
double GenericOption::valueAtExpiration(double underlyingAtExpiration)
{ 
double value = 0.0; 

if (m_type == OptionType_Call)
{ 
if (m_strike < underlyingAtExpiration)
{ 
value = underlyingAtExpiration - m_strike; 
} 
} 
else  // it is an OptionType_Put 
{ 
if (m_strike > underlyingAtExpiration) 
{ 
value = m_strike - underlyingAtExpiration; 
} 
} 
return value; 
} 

//
// return the profit (value at expiration minus option cost) 
// the overall profit has to take account of whatever we originally paid for the option
// thus only if the final computed value of the option at expiry exceeds what the option cost 
// us to buy originally can we be said to have made a profit
// profit then (here returned as the variable 'value') is defaulted to zero pending value at expiry 
// exceeding the initial cost and (therefore) resulting in profit
//
 double GenericOption::profitAtExpiration(double underlyingAtExpiration)
{ 
double value = 0.0; 
double finalValue = valueAtExpiration(underlyingAtExpiration);

if (finalValue > m_cost) 
{ 
value = finalValue - m_cost;
}
return value;
} 

//the main method: this is the engine of the GenericOption class, it is the bit that does all of the work
//here we see that a GenericOption object is created with astrike price of 100, a type of Put
// noting again that the parameter 'OptionType' has been defined in the header file for this class 
// as a type 'enum' (i.e. an enumerator or an array) with two possible values, namely: OptionType_Call, OptionType_Put
// here then the option type is set to OptionType_Put and the cost of the option is set to 1.1
// a first hypothetical price (price 1) of the underlying is set to 120 and the standard console output object cout
// is used to print out the profit from this scenario which is computed using the function valueAtExpiration
// a second hypothetical price (price 2) is similarly used to compute the option value scenario
// and finally a 'for loop' construct is used to traverse a range of hypothetical prices of the underlying
// at expiry from 80 to 120 (incrementing by 0.1) for 
// each loop and outputing the profit for each scenario before outputting the profit per price of the underlying 
// to the console/terminal, note the use of endl per iteration to create a new line/carraige return

int main() 
{ 
GenericOption option(100.0, OptionType_Put, 1.1);
double price1 = 120.0;
double value = option.valueAtExpiration(price1);
cout     << " For 100PUT, value at expiration for price "
<<  price1
<<  "  is "
<<  value  << endl;
double price2 = 85.0;
value = option.valueAtExpiration(85.0); 
cout     << " For 100PUT, value at expiration for price " 
<< price2
<< " is "
<< value << endl;

// test profitAtExpiration 
auto limit = 120.0;
for (auto price = 80.0; price <= limit; price += 0.1) 
{ 
value = option.profitAtExpiration(price);
cout << price << ", " << value <<  endl;
} 

return 0; 
}