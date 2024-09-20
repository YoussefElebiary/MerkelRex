#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenize(std::string line, char separator);
    static OrderBookEntry strToOrderBookEntry(std::string _price, std::string _amount, std::string timestamp,
                                              std::string product, OrderBookType type);
private:
    static OrderBookEntry strToOrderBookEntry(std::vector<std::string> tokens);
};