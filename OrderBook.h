#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
private:
    std::vector<OrderBookEntry> orders;
public:
    OrderBook(std::string filename);
    /** Returns all the known products in the order book */
    std::vector<std::string> getKnownProducts();
    /** Filters the order book according to the passed parameters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    /** Gets the earliest time in the order book */
    std::string getEarliestTime();
    /** Gets the next time after the passed time, if the current time is the greatest, it will return the smallest time */
    std::string getNextTime(std::string time);
    /** Gets the highest price in the order book */
    static double getHighestPrice(std::vector<OrderBookEntry>& _orders);
    /** Gets the lowest price in the order book */
    static double getLowestPrice(std::vector<OrderBookEntry>& _orders);
    /** Inserts an order into the orders vector */
    void insertOrder(OrderBookEntry& order);
    /** Matching engine to perform trading */
    std::vector<OrderBookEntry> macthAsksToBids(std::string product, std::string timestamp);
};