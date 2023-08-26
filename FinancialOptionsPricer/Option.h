
#ifndef OPTIONSTRACKER_OPTION_H
#define OPTIONSTRACKER_OPTION_H
class Option{
    protected:
        double stockPrice;
        double volatility;
        double strikePrice;
        double time;
        double intRate;

    public:
        // parameterized constructor
        Option(double stockPrice, double volatility, double strikePrice, double time, double
        intRate)
                : stockPrice(stockPrice), volatility(volatility), strikePrice(strikePrice), time(time), intRate(intRate) { }

        // default constructor
        Option(): stockPrice(0), volatility(0), strikePrice(0), time(0), intRate(0) { }

        // these are pur virtual functions for the option classes to inherit from
        virtual double callOptionPrice() = 0; // pure virtual function
        virtual double putOptionPrice() = 0;  // pure virtual function


};




#endif //OPTIONSTRACKER_OPTION_H
