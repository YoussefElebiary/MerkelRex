#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <limits>
#include <vector>

MerkelMain::MerkelMain()
{
    
}

void MerkelMain::init()
{
    int choice;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    while (true)
    {
        PrintMenu();
        choice = getUserOption();
        HandleChoice(choice);
    }
}

void MerkelMain::PrintMenu()
{
    std::cout << std::endl << "    Welcome to the MerkelRex trading platform" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "1:  Print help" << std::endl;
    std::cout << "2:  Print exchange stats" << std::endl;
    std::cout << "3:  Make an ask" << std::endl;
    std::cout << "4:  Make a bid" << std::endl;
    std::cout << "5:  Print wallet" << std::endl;
    std::cout << "6:  Continue" << std::endl;
    std::cout << "7:  Exit" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "Current Time : " << currentTime << std::endl;
}

int MerkelMain::getUserOption()
{
    int UserOption;
    std::cout << "Select a number from 1 to 6" << std::endl;
    std::cin >> UserOption;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "You chose " << UserOption << std::endl << std::endl;
    return UserOption;
}

void MerkelMain::PrintHelp()
{
    std::cout << std::endl << "Help - Your aim is to make money. Analyse the market and make bids and offers" << std::endl << std::endl;
}

void MerkelMain::MarketStats()
{
    std::vector<std::string> knownProducts = orderBook.getKnownProducts();
    
    for (const std::string& p : knownProducts)
    {
        std::cout << "Products  :   " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen :   " << entries.size() << std::endl;
        std::cout << "Max ask   :   " << OrderBook::getHighestPrice(entries) << std::endl;
        std::cout << "Min ask   :   " << OrderBook::getLowestPrice(entries) << std::endl << std::endl;
    }
    // unsigned int asks = 0;
    // unsigned int bids = 0;

    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.getOrderType() == OrderBookType::ask)
    //     {
    //         ++asks;
    //     }
    //     else if (e.getOrderType() == OrderBookType::bid)
    //     {
    //         ++bids;
    //     }
    // }

    // std::cout << std::endl << "The market contains :    ";
    // std::cout << orders.size() << " entries" << std::endl
    // << "                         " << asks << " asks" << std::endl
    // << "                         " << bids << " bids" << std::endl << std::endl; 
}

void MerkelMain::MakeAsk()
{
    std::string input;
    std::cout << std::endl << "Make an ask - Enter the amount (product, price, amount) eg. \"ETH/BTC,200,0.5\"" << std::endl;
    std::cin.ignore(1);
    std::getline(std::cin, input);
    std::cout << std::endl;

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cerr << "MerkelMain::MakeAsk  -  Invalid Input :    " << input << std::endl << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obj = CSVReader::strToOrderBookEntry(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            obj.setUsername("simuser");
            if (wallet.canFulfillOrder(obj))
            {
                orderBook.insertOrder(obj);
            }
            else
            {
                std::cout << "Insufficient funds" << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "MerkelMain::MakeAsk  -  Invalid Input" << std::endl;
        }
    }
}

void MerkelMain::MakeBid()
{
    std::string input;
    std::cout << std::endl << "Make a bid - Enter the amount (product, price, amount) eg. \"BTC/USDT,150,0.2\"" << std::endl;
    std::cin.ignore(1);
    std::getline(std::cin, input);
    std::cout << std::endl;

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cerr << "MerkelMain::MakeBid  -  Invalid Input :    " << input << std::endl << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obj = CSVReader::strToOrderBookEntry(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obj.setUsername("simuser");
            if (wallet.canFulfillOrder(obj))
            {
                orderBook.insertOrder(obj);
            }
            else
            {
                std::cout << "Insufficient funds" << std::endl;
            }

        }
        catch (const std::exception& e)
        {
            std::cerr << "MerkelMain::MakeBid  -  Invalid Input" << std::endl;
        }
    }
}

void MerkelMain::PrintWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::NextTimeFrame()
{
    std::cout << std::endl << "Going to the next time frame" << std::endl << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.macthAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales done : " << sales.size() << std::endl;
    for (OrderBookEntry& order : sales)
    {
        std::cout << "Sale price : " << order.getPrice() << " amount : " << order.getAmount() << std::endl;
        if (order.getUsername() == "simuser")
        {
            wallet.processSale(order);
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::HandleChoice(int UserOption)
{
    if (UserOption == 0)
    {
        std::cout << "Invalid Input" << std::endl << std::endl;
    }
    else if (UserOption == 1)
    {
        PrintHelp();  
    }
    else if (UserOption == 2)
    {
        MarketStats();
    }
    else if (UserOption == 3)
    {
        MakeAsk();
    }
    else if (UserOption == 4)
    {
        MakeBid();
    }
    else if (UserOption == 5)
    {
        PrintWallet();
    }
    else if (UserOption == 6)
    {
        NextTimeFrame();
    }
    else if (UserOption == 7)
    {
        std::cout << "Exiting...";
        exit(0);
    }
}