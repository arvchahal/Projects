#ifndef OPTIONSTRACKER_BINOMIALOPTION_HPP
#define OPTIONSTRACKER_BINOMIALOPTION_HPP

#include "Option.h"

/**
 * Binomial option pricing model class that inherits from the Option base class.
 */
class Binomial: public Option {
private:
    /**
     * Inner struct representing the nodes of the binomial tree.
     * Each node has a left and right child, corresponding to the downward and upward moves in the tree,
     * and a value representing the stock price at that point in time.
     */
    struct bnNode {
        bnNode* left;
        bnNode* right;
        double val;
    };

    bnNode* root;  // Root node of the binomial tree, representing the current stock price.

    double upSz;   // Upward move size.
    double downSz; // Downward move size.
    double upMv;   // Upward move probability.
    double downMv; // Downward move probability.
    int steps;     // Number of time steps in the binomial tree.
    double stepSize; // Size of each step in terms of time.

    /**
     * Recursive function to build the binomial tree.
     *
     * @param currNode Current node being populated.
     * @param timeStep Current time step.
     * @param currPrice Current stock price.
     */
    void populateTree(bnNode* currNode, double timeStep, double currPrice);

    /**
     * Recursive function to calculate call option payout.
     *
     * @param node Node at which to calculate payout.
     * @param timeStep Time step of node.
     * @param remTime Remaining time to option expiration.
     */
    void calculateCallPayout(bnNode* node, double timeStep, double remTime);

    /**
     * Recursive function to calculate put option payout.
     *
     * @param node Node at which to calculate payout.
     * @param timeStep Time step of node.
     * @param remainingTime Remaining time to option expiration.
     */
    void calculatePutPayout(bnNode* node, double timeStep, double remainingTime);

    /**
     * Recursive function to delete the binomial tree.
     *
     * @param node Node at which to start deletion.
     */
    void deleteTree(bnNode* node);

public:
    using Option::Option;

    /**
     * Default constructor that initializes all variables to 0.
     */
    Binomial();

    /**
     * Constructor that initializes the option and the binomial tree.
     *
     * @param stockPrice Initial stock price.
     * @param volatility Stock price volatility.
     * @param strikePrice Option strike price.
     * @param time Option time to expiration.
     * @param intRate Risk-free interest rate.
     * @param steps Number of time steps in the binomial tree.
     */
    Binomial(double stockPrice, double volatility, double strikePrice, double time, double intRate,
             int steps);

    /**
     * Calculate the price of a European call option using the binomial model.
     *
     * @return The price of the call option.
     */
    double callOptionPrice() override;

    /**
     * Calculate the price of a European put option using the binomial model.
     *
     * @return The price of the put option.
     */
    double putOptionPrice() override;

    /**
     * Destructor that deletes the binomial tree.
     */
    ~Binomial();

};

#endif //OPTIONSTRACKER_BINOMIALOPTION_HPP
