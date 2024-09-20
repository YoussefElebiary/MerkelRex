#pragma once

#include <string>

/** Data type to store the type of order placed (BID / ASK / ASKSALE / BIDSALE / UNKNOWN) */
enum class OrderBookType {bid, ask, asksale, bidsale, unknown};

/** Data type to store the data of each order placed */
class OrderBookEntry
{
// Data Members
private:
    double price;
    double amount;
    std::string time;
    std::string product;
    OrderBookType orderType;
    std::string username;

// Methods
public:
    /** Constructor to assign all the data members to the passed values */
    OrderBookEntry(const double& _price, const double& _amount,
                   const std::string& _time, const std::string& _product,
                   const OrderBookType& _orderType, std::string _username = "dataset");
    
    /** Convert strings to OrderBookType */
    static OrderBookType str2OrderBookType(std::string str);
    /** Get OrderBookType */
    OrderBookType getOrderType();
    /** Set OrderBookType */
    void setOrderType(OrderBookType _type);
    /** Get Product */
    std::string getProduct();
    /** Get Timestammp */
    std::string getTimeStamp();
    /** Get Price */
    double getPrice();
    /** Get Amount */
    double getAmount();
    /** Set Amount */
    void setAmount(double _amount);
    /** Set Username */
    void setUsername(std::string _username);
    /** Get Username */
    std::string getUsername();
    /** Compares between two entries by time */
    static bool compareByTime(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.time < e2.time;
    }
    /** Compares between two entries by price ascendingly */
    static bool compareByPriceASC(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }
    /** Comapres between two entries by price descendingly */
    static bool compareByPriceDESC(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }
};