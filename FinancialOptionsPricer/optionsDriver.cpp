#include <iostream>
#include "string"
#include "Binomial.h"
#include "BlackScholes.h"
#include "MonteCarlo.h"
int main() {
    int choice;
    double stockPrice, volatility, strikePrice, time, intRate;
    int steps, simulations;

    std::cout << "Welcome to the Option Pricer. Please choose the type of pricer:" << std::endl;
    std::cout << "1. Black Scholes" << std::endl;
    std::cout << "2. Binomial" << std::endl;
    std::cout << "3. Monte Carlo" << std::endl;
    std::cout <<"Enter your choice: ";
    std::cin >> choice;
    std::cout << std::endl;

    if (choice < 1 || choice > 3  ) {
        std::cout << "Invalid Choice Exiting...";
        return -1;
    }

    std::cout << "Enter the Stock Price: ";
    std::cin >> stockPrice;
    std::cout << std::endl;

    std::cout << "Enter the Volatility as a %: ";
    std::cin >> volatility;
    std::cout << std::endl;


    std::cout << "Enter the Strike Price: ";
    std::cin >> strikePrice;
    std::cout << std::endl;

    std::cout << "Enter the Time in years: ";
    std::cin >> time;
    std::cout << std::endl;

    std::cout << "Enter the Interest Rate as a percent %: ";
    std::cin >> intRate;
    std::cout << std::endl;

    if (choice == 1) {
        BlackScholes blackScholesPrice(stockPrice, volatility, strikePrice, time, intRate);
        std::cout << "Call Option Price: " << blackScholesPrice.callOptionPrice() << std::endl;
        std::cout << "Put Option Price: " << blackScholesPrice.putOptionPrice() << std::endl;
    }

    else if (choice == 2) {
        std::cout << "Enter the number of steps for the binomial option pricer tree (Perferably "
                     "less than 5): ";
        std::cin >> steps;
        Binomial binomial(stockPrice, volatility, strikePrice, time, intRate, steps);
        std::cout << "Call Option Price: " << binomial.callOptionPrice() << std::endl;
        std::cout << "Put Option Price: " << binomial.putOptionPrice() << std::endl;
    }

    else if (choice == 3) {
        std::cout << "Enter the number of simulations for the MonteCarlo Simulation"
                     " the more simulations the more accurate the price will be: ";
        std::cin >> simulations;
        MonteCarlo mc(stockPrice, volatility, strikePrice, time, intRate, simulations);
        std::cout << "Call Option Price: " << mc.callOptionPrice() << std::endl;
        std::cout << "Put Option Price: " << mc.putOptionPrice() << std::endl;
    }
}