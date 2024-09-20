#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(const double& _price, const double& _amount,
                               const std::string& _time, const std::string& _product,
                               const OrderBookType& _orderType, std::string _username)
: price(_price), amount(_amount), time(_time), product(_product), orderType(_orderType), username(_username) {};

OrderBookType OrderBookEntry::str2OrderBookType(std::string str)
{
    if (str == "ask")
    {
        return OrderBookType::ask;
    }
    if (str == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}

OrderBookType OrderBookEntry::getOrderType()
{
    return orderType;
}

void OrderBookEntry::setOrderType(OrderBookType _type)
{
    orderType = _type;
}

std::string OrderBookEntry::getProduct()
{
    return product;
}

std::string OrderBookEntry::getTimeStamp()
{
    return time;
}

double OrderBookEntry::getPrice()
{
    return price;
}

double OrderBookEntry::getAmount()
{
    return amount;
}

void OrderBookEntry::setAmount(double _amount)
{
    amount = _amount;
}

void OrderBookEntry::setUsername(std::string _username)
{
    username = _username;
}

std::string OrderBookEntry::getUsername()
{
    return username;
}