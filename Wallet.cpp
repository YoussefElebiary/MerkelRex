#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0)
    {
        currencies[type] = amount;
    }
    else
    {
        currencies[type] += amount;
    }
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0)
    {
        return false;
    }
    else
    {
        if (containsCurrency(type, amount))
        {
            currencies[type] -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0 || currencies[type] < amount)
    {
        return false;
    }
    else
    {
        return (currencies[type] >= amount);
    }
}

std::string Wallet::toString()
{
    std::string s = "";
    for (std::pair<std::string, double> pair : currencies)
    {
        s += pair.first + " : " + std::to_string(pair.second) + '\n';
    }
    return s;
}

bool Wallet::canFulfillOrder(OrderBookEntry& order)
{
    std::vector<std::string> currs = CSVReader::tokenize(order.getProduct(), '/');
    if (order.getOrderType() == OrderBookType::ask)
    {
        return containsCurrency(currs[0], order.getAmount());
    }
    if (order.getOrderType() == OrderBookType::bid)
    {
        return containsCurrency(currs[1], order.getAmount() * order.getPrice());
    }
    return false;
}

void Wallet::processSale(OrderBookEntry& order)
{
    std::vector<std::string> currs = CSVReader::tokenize(order.getProduct(), '/');
    if (order.getOrderType() == OrderBookType::asksale)
    {
        double lose = order.getAmount();
        double gain = order.getAmount() * order.getPrice();
        std::string loseCurrency = currs[0];
        std::string gainCurrency = currs[1];

        currencies[gainCurrency] += gain;
        currencies[loseCurrency] -= lose;
    }
    if (order.getOrderType() == OrderBookType::bidsale)
    {
        double lose = order.getAmount() * order.getPrice();
        double gain = order.getAmount();
        std::string loseCurrency = currs[1];
        std::string gainCurrency = currs[0];

        currencies[gainCurrency] += gain;
        currencies[loseCurrency] -= lose;
    }
}