#include <random>
#include <boost/math/distributions/normal.hpp>
#include "MonteCarlo.h"

/**
 * Constructor for the MonteCarlo class. This method initializes the properties of the class.
 *
 * @param stockPrice The initial stock price.
 * @param volatility The volatility of the stock.
 * @param strikePrice The strike price of the option.
 * @param time The time to expiry of the option.
 * @param intRate The risk-free interest rate.
 * @param simulations The number of simulations to run in the Monte Carlo simulation.
 */
MonteCarlo::MonteCarlo(double stockPrice, double volatility, double strikePrice, double time,
                       double intRate, int simulations) :
        Option(stockPrice, volatility, strikePrice, time, intRate), simulations
        (simulations) {

}

/**
 * This method computes the price of a put option using the Monte Carlo method.
 *
 * @return The calculated price of the put option.
 */
double MonteCarlo::putOptionPrice() {
    double sumPayoffs =0;
    std::default_random_engine nums(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> norm(0.0, 1.0);

    // Loop over the number of simulations
    for(size_t i =0;i<simulations;i++){
        // Simulate a stock price path
        double simPrice = stockPrice * std::exp((intRate - 0.5 * pow(volatility,2)) *time
                                                + volatility * sqrt(time) * norm(nums));
        // Compute the payoff of the put option
        double payoff = std::max(strikePrice - simPrice,0.0);
        sumPayoffs += payoff;

    }

    // Calculate the price of the put option
    double price = sumPayoffs/simulations * std::exp(-intRate*time);
    return price;
}

/**
 * This method computes the price of a call option using the Monte Carlo method.
 *
 * @return The calculated price of the call option.
 */
double MonteCarlo::callOptionPrice() {
    double sumPayoffs =0;
    std::default_random_engine nums(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> norm(0.0, 1.0);

    // Loop over the number of simulations
    for(size_t i =0;i<simulations;i++){
        // Simulate a stock price path
        double simPrice = stockPrice * std::exp((intRate - 0.5 * pow(volatility,2)) *time
                                                + volatility * sqrt(time) * norm(nums));
        // Compute the payoff of the call option
        double payoff = std::max(simPrice - strikePrice,0.0);
        sumPayoffs += payoff;

    }

    // Calculate the price of the call option
    double price = sumPayoffs/simulations * std::exp(-intRate*time);
    return price;
}
