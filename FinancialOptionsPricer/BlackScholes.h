
#ifndef OPTIONSTRACKER_BLACKSCHOLES_H
#define OPTIONSTRACKER_BLACKSCHOLES_H
#include <boost/math/special_functions.hpp>
#include <boost/math/distributions.hpp>
#include "Option.h"
/**
 * This class uses all of the generic Option private variables and does not require anything else
 * to calculate the option pricing.
 */
class BlackScholes : public Option{
private:


public:
    using Option::Option;

    /**
     * Calculates the call option price using the BlackScholes formula
     * @return the value of the call option
     */
    double callOptionPrice() override;

    /**
     * Calculates the put option price using the BlackScholes formula
     * @return  the value of the put option
     */
    double putOptionPrice() override;
};
#endif
