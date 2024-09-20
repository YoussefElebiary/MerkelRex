#include "OrderBook.h"
#include "CSVReader.h"
#include "MerkelMain.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.getProduct()] = true;
    }

    for (const auto& it : prodMap)
    {
        products.push_back(it.first);
    }
    products.shrink_to_fit();
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_;
    for (OrderBookEntry& e : orders)
    {
        if (e.getOrderType() == type && e.getProduct() == product && e.getTimeStamp() == timestamp)
        {
            orders_.push_back(e);
        }
    }
    orders_.shrink_to_fit();
    return orders_;
}

double OrderBook::getHighestPrice(std::vector<OrderBookEntry>& _orders)
{
    double mx = _orders[0].getPrice();
    for (OrderBookEntry& e : _orders)
    {
        mx = std::max(e.getPrice(), mx);
    }
    return mx;
}

double OrderBook::getLowestPrice(std::vector<OrderBookEntry>& _orders)
{
    double mn = _orders[0].getPrice();
    for (OrderBookEntry& e : _orders)
    {
        mn = std::min(e.getPrice(), mn);
    }
    return mn;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].getTimeStamp();
}

std::string OrderBook::getNextTime(std::string time)
{
    for (OrderBookEntry& e : orders)
    {
        if (e.getTimeStamp() > time)
        {
            return e.getTimeStamp();
        }
    }
    return orders[0].getTimeStamp();
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTime);
}

std::vector<OrderBookEntry> OrderBook::macthAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceASC);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDESC);

    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids)
        {
            if (bid.getPrice() >= ask.getPrice())
            {
                OrderBookEntry sale{ask.getPrice(), 0, timestamp, product, OrderBookType::asksale};
                if (bid.getUsername() == "simuser")
                {
                    sale.setUsername("simuser");
                    sale.setOrderType(OrderBookType::bidsale);
                }
                if (ask.getUsername() == "simuser")
                {
                    sale.setUsername("simuser");
                    sale.setOrderType(OrderBookType::asksale);
                }

                if (bid.getAmount() == ask.getAmount())
                {
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(0);
                    break;
                }

                if (bid.getAmount() > ask.getAmount())
                {
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(bid.getAmount() - ask.getAmount());
                    break;
                }

                if (0 < bid.getAmount() && bid.getAmount() < ask.getAmount())
                {
                    sale.setAmount(bid.getAmount());
                    sales.push_back(sale);
                    ask.setAmount(ask.getAmount() - bid.getAmount());
                    bid.setAmount(0);
                    continue;
                }
            }
        }
    }

    return sales;
}

// // Implemented in the OrderBook class
// double OrderBook::changeByTimeStamp(std::string prev_time, std::string product)
// {
//     // Gets all the orders of the passed time
//     std::vector<OrderBookEntry> prev = getOrders(OrderBookType::ask, product, prev_time);    // getOrders() -> filters the order book
//     double prev_ = 0.0;
//     int num = 0;
//     // Gets the sum of the prices
//     for (OrderBookEntry& e : prev)
//     {
//         prev_ += e.getPrice();    // getPrice() -> returns the price of that object
//         ++num;
//     }
//     // Gets the average price
//     prev_ /= num;
//     // Gets all the orders of the same type butt at the current time
//     std::vector<OrderBookEntry> curr = getOrders(OrderBookType::ask, product, app.currentTime);
//     double p = 0.0;
//     num = 0;
//     // Gets the sum of prices
//     for (OrderBookEntry& e : curr)
//     {
//         p += e.getPrice();
//         ++num;
//     }
//     // Gets the average price
//     p /= num;
//     // Returns the difference
//     return p - prev_;
// }