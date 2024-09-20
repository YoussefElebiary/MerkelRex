#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream fin{csvFile};
    std::string line;
    
    if (fin.is_open())
    {
        while (std::getline(fin, line))
        {
            try
            {
                std::vector<std::string> tokens = tokenize(line, ',');
                OrderBookEntry obj = strToOrderBookEntry(tokens);
                entries.push_back(obj);
            }
            catch (const std::exception& e)
            {
                std::cout << "CSVReader::readCSV found invalid data" << std::endl;
            }
        }
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    
    return entries;
}

std::vector<std::string> CSVReader::tokenize(std::string line, char separator)
{
    std::vector<std::string> tokens;
    int start, end;
    std::string token;

    tokens.reserve(5);
    start = line.find_first_not_of(separator, 0);

    do
    {
        end = line.find_first_of(separator, start);

        if (start == line.length() || start == end)
        {
            break;
        }

        if (end >= 0)
        {
            token = line.substr(start, end - start);
        }
        else
        {
            token = line.substr(start, line.length() - start);
        }

        tokens.push_back(token);
        start = end + 1;
    } while(end != std::string::npos);

    return tokens;
}   

OrderBookEntry CSVReader::strToOrderBookEntry(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5)
    {
        std::cerr << "CSVReader::strToOrderBookEntry  -  Invalid Line" << std::endl;
        throw std::exception{};
    }

    try
    {
        price = std::stod(tokens[3]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "CSVReader::strToOrderBookEntry  -  Error Converting " << tokens[3] << " to double" << std::endl;
        throw;
    }

    try
    {
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "CSVReader::strToOrderBookEntry  -  Error Converting " << tokens[4] << " to double" << std::endl;
        throw;
    }

    OrderBookEntry entry{price, amount, tokens[0], tokens[1], OrderBookEntry::str2OrderBookType(tokens[2])}; 

    return entry;
}

OrderBookEntry CSVReader::strToOrderBookEntry(std::string _price, std::string _amount, std::string timestamp,
                                              std::string product, OrderBookType type)
{
    double price, amount;

    try
    {
        price = std::stod(_price);
    }
    catch(const std::exception& e)
    {
        std::cerr << "CSVReader::strToOrderBookEntry  -  Error Converting " << _price << " to double" << std::endl;
        throw;
    }

    try
    {
        amount = std::stod(_amount);
    }
    catch(const std::exception& e)
    {
        std::cerr << "CSVReader::strToOrderBookEntry  -  Error Converting " << _amount << " to double" << std::endl;
        throw;
    }

    OrderBookEntry obj{price, amount, timestamp, product, type};
    
    return obj;
}