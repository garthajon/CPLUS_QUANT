//
 //  RandomWalkGenerator.cpp
 //
 //  Simple random walk implementation.
 #include "RandomWalkGenerator.h"
 #include <cstdlib>
 #include <iostream>
 #include <ostream>

 using std::vector;
 using std::cout;
 using std::endl;
 //
 // Constructor. The supplied parameters represent the number of elements in the
 // random walk, the initial (start) price, and the step size for the random walk.
 //
 RandomWalkGenerator::RandomWalkGenerator(int size, double start, double step)
 : m_numSteps(size),
 m_stepSize(step),
 m_initialPrice(start)
 {
 }
 RandomWalkGenerator::RandomWalkGenerator(const RandomWalkGenerator &p)
 : m_numSteps(p.m_numSteps),
 m_stepSize(p.m_stepSize),
 m_initialPrice(p.m_initialPrice)
 {
 }
 RandomWalkGenerator::~RandomWalkGenerator()
 {
 }
 RandomWalkGenerator &RandomWalkGenerator::operator=(const RandomWalkGenerator &p)
 {
    if (this != &p)
    {
        m_numSteps = p.m_numSteps;
        m_stepSize = p.m_stepSize;
        m_initialPrice = p.m_initialPrice;
    }
    return *this;
 }
 //
 // the compute random step method takes the currentprice and either increases or decreases that
 // price by a 'stepsize' amount, or it does nothing at all i.e. the current price does not change at all
 // thus the compute step function is key for literally computing each step change in the random walk
 //
 double RandomWalkGenerator::computeRandomStep(double currentPrice)
 {
    const int num_directions = 3;
    // rand() in C++ generates a random integer between 0 and 32767 
    int r = rand() % num_directions;
    // the modulus operator % here will result in the remainder of dividing the random number by 3
    // thus the variable 'r' becomes the remainder of the modulus operation above
    double val = currentPrice;
    // if statement handling the various possible 'remainder' values
    if (r == 0)
    // when remainder is 0 increase the currentprice by stepsize change value
    {
        val += (m_stepSize * val);
    }
    else if (r == 1)
    // when remainder is 1 decrease the currentprice by stepsize change value
    {
        val -= (m_stepSize * val);
    }
    // for all other remainder values do nothing - i.e. no price change (the else is implicit)
    return val;
 }
 //
 // This generateWalk() method is the principle/core method to generate the walk. 
 // it used the computeRandomStep() function to generate a series of changing prices in a series of steps.
 //
 std::vector<double> RandomWalkGenerator::generateWalk()
 {
    vector<double> walk;
    double prev = m_initialPrice;
    for (int i=0; i<m_numSteps; ++i)
    {
        // the computerandomstep change function is key as it changes the price value from that of the 
        // price at the previous step
        double val =  computeRandomStep(prev);
        walk.push_back(val);
        prev = val;
    }
    return walk;
 }
 //
 // This is a testing stub. It generates a sequence of random points.
 //
int main()
{
 // 100 steps starting at $30
    RandomWalkGenerator rw(100, 30, 0.01);
    vector<double> walk = rw.generateWalk();
    for (int i=0; i<walk.size(); ++i)
    {
        cout << ", " << i << ", " << walk[i] <<  endl;
    }
    cout << endl;
    return 0;
}
        //cout << ", " << i << ", " << walk[i];