#include "BlackScholes.h"
#include <boost/math/distributions.hpp>

/**
 * Computes the price of a call option using the Black-Scholes model.
 *
 * @return The calculated price of the call option.
 */
double BlackScholes::callOptionPrice(){
    double callPrice;
    double d1 = (log(stockPrice/strikePrice) + time * (intRate+(pow(volatility,2) ) / 2))/
                (volatility * pow(time,.5));
    double d2 = d1 - volatility*std::sqrt(time);

    // Call option price formula in Black-Scholes model
    callPrice = stockPrice * boost::math::cdf(boost::math::normal(),d1) -
                strikePrice * std::exp(-intRate*time)*
                boost::math::cdf(boost::math::normal(),d2);

    return callPrice;
}

/**
 * Computes the price of a put option using the Black-Scholes model.
 *
 * @return The calculated price of the put option.
 */
double BlackScholes::putOptionPrice(){
    double putPrice;
    double d1 = (log(stockPrice/strikePrice) + time * (intRate+(pow(volatility,2) ) / 2))/
                (volatility * pow(time,.5));
    double d2 = d1 - volatility*std::sqrt(time);

    // Put option price formula in Black-Scholes model
    putPrice = strikePrice*std::exp(-intRate*time)*boost::math::cdf(boost::math::normal(),-d2) -
               stockPrice*boost::math::cdf(boost::math::normal(),-d1);

    return putPrice;
}
