#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <map>

class Wallet
{
public:
    Wallet();
    /** Adds currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** Removes currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** Checks if the wallet contains the given amount of currency or more */
    bool containsCurrency(std::string type, double amount);
    /** Checks if wallet has enough money to fulfill an order */
    bool canFulfillOrder(OrderBookEntry& order);
    /** Process the sale and updates the wallet */
    void processSale(OrderBookEntry& order);
    /** Generate string representation of the wallet */
    std::string toString();
private:
    std::map<std::string, double> currencies;
};