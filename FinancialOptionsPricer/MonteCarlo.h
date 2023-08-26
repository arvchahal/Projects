
#ifndef OPTIONSTRACKER_MONTECARLO_H
#define OPTIONSTRACKER_MONTECARLO_H


#include "Option.h"
/**
 * This class simulates the option price using the montecarlo method
 * It will estimate the price using random values and as such will change each run
 * the more simulations the better but the longer the program will take
 *
 */
class MonteCarlo : public Option{
private:
    //number of simulations
    int simulations;


public:
    //uses the options private variables
    using Option::Option;

    //constructor for the option
    //the only difference is the number of simulations
    //uses the options constructor and then initializes the simulations
    MonteCarlo(double stockPrice, double volatility, double strikePrice, double time,
               double intRate, int simulations);
    //overrrides the callOptionPrice from the options base class
    double callOptionPrice() override;

    //overrrides the putOptionPrice from the options base class
    double putOptionPrice() override;
};



#endif //OPTIONSTRACKER_MONTECARLO_H
