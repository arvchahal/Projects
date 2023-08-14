#include <boost/math/distributions.hpp>
#include "Binomial.h"

/**
 * Default constructor for Binomial.
 * Initializes the class with default values.
 */
Binomial::Binomial()
        : Option(0, 0, 0, 0, 0), steps(0), upSz(0), downSz(0), upMv(0), downMv(0) {
    root = new bnNode;
    root->val = stockPrice;
}

/**
 * Parameterized constructor for Binomial.
 * Initializes the class with user-defined values.
 *
 * @param stockPrice Initial price of the underlying stock.
 * @param volatility Volatility of the underlying stock.
 * @param strikePrice Strike price of the option.
 * @param time Time until the option's expiration.
 * @param intRate Risk-free interest rate.
 * @param steps Number of steps in the binomial tree.
 * and it calculates the upSize, downSize, and sets the root node to the stockPrice
 * and it calcualtes the stepSize
 */
Binomial::Binomial(double stockPrice, double volatility, double strikePrice, double time,
                   double intRate, int steps)
        : Option(stockPrice, volatility, strikePrice, time, intRate), steps(steps) {
    upSz = std::exp(volatility * std::sqrt((time) / steps));
    downSz = 1 / upSz;
    root = new bnNode;
    root->val = stockPrice;

    root->left = nullptr;
    root->right = nullptr;
    stepSize = time / steps;
}

/**
 * Computes the price of a call option.
 *
 * @return The calculated price of the call option.
 */
double Binomial::callOptionPrice() {
    populateTree(root, 0, stockPrice);
    calculateCallPayout(root, 0, time);
    return root->val;
}

/**
 * Computes the price of a put option.
 *
 * @return The calculated price of the put option.
 */
double Binomial::putOptionPrice() {
    populateTree(root, 0, stockPrice);
    calculatePutPayout(root, 0,time);
    return root->val;
}

/**
 * Populates the binomial tree with nodes representing possible future stock prices.
 *
 * @param currNode Current node in the tree.
 * @param timeStep Current time step in the tree.
 * @param currPrice Current price of the underlying stock.
 */
void Binomial::populateTree(bnNode *currNode, double timeStep, double currPrice) {
    currNode->val = currPrice;
    currNode->left = nullptr;
    currNode->right = nullptr;
    if(timeStep >= steps){
        return;
    }

    currNode->left = new bnNode;
    currNode->right = new bnNode;

    populateTree(currNode->left, timeStep+1,currPrice*downSz);
    populateTree(currNode->right, timeStep+1,currPrice*upSz);
}

/**
 * Calculates the payout of a call option.
 *
 * @param node Current node in the tree.
 * @param timeStep Current time step in the tree.
 * @param remainingTime Remaining time until the option's expiration.
 */
void Binomial::calculateCallPayout(Binomial::bnNode *node, double timeStep, double remainingTime) {
    upMv = (std::exp(intRate * remainingTime) - downSz) / (upSz - downSz);
    downMv = 1 - upMv;

    if(timeStep == steps){
        node->val = std::max(node->val - strikePrice, 0.0);
    }
    else {
        remainingTime -= stepSize;
        calculateCallPayout(node->left, timeStep + 1, remainingTime);
        calculateCallPayout(node->right, timeStep + 1, remainingTime);
    }

    if(node->left != nullptr && node->right != nullptr) {
        double expectedValue = upMv * node->left->val + downMv * node->right->val;
        node->val = std::exp(-intRate * stepSize) * expectedValue;
    }
}

/**
 * Calculates the payout of a put option.
 *
 * @param node Current node in the tree.
 * @param timeStep Current time step in the tree.
 * @param remainingTime Remaining time until the option's expiration.
 */
void Binomial:: calculatePutPayout(Binomial::bnNode *node, double timeStep, double remainingTime){
    upMv = (std::exp(intRate*remainingTime )-downSz)/(upSz-downSz);
    downMv = 1 - upMv;
    if(timeStep == steps){
        node->val = std::max(strikePrice - node->val,0.0);
    }
    else{
        remainingTime -=stepSize;
        calculatePutPayout(node->left,timeStep+1,remainingTime);
        calculatePutPayout(node->right,timeStep+1,remainingTime);
    }
    if(node->left != nullptr && node->right!= nullptr) {
        double expectedValue = upMv * node->left->val + downMv * node->right->val;
        node->val = std::exp(-intRate * stepSize) * expectedValue;
    }
}

/**
 * Destructor for the Binomial class.
 * Deallocates memory used by the binomial tree.
 */
Binomial::~Binomial() {
    deleteTree(root);
}

/**
 * Deletes a node and all its child nodes from the binomial tree.
 *
 * @param node, Node to be deleted.
 */
void Binomial::deleteTree(bnNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}
