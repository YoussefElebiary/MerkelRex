#pragma once

#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <vector>

class MerkelMain
{
public:
    MerkelMain();

    void init();

private:
    // Data members
    std::string currentTime;
    /** Prints the main menu */
    void PrintMenu();

    /** Get the user's input */
    int getUserOption();

    /** Displays the help menu */
    void PrintHelp();

    void MarketStats();

    void MakeAsk();
    
    void MakeBid();

    void PrintWallet();

    void NextTimeFrame();

    /** Performs action based on the user's input */
    void HandleChoice(int UserOption);

    OrderBook orderBook{"20200317.csv"};

    Wallet wallet;
};