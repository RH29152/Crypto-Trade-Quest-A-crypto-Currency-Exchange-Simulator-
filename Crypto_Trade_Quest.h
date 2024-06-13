#pragma once
#include"Csv_data_Read.h"
#include"MarketHelper.h"
#include"Wallet.h"
class Crypto_Trade_Quest{

    public:
    Csv_data_Read CsvFile{"trades.csv"};
    MarketHelper helperFunc;
     Wallet Assets;
     
    Crypto_Trade_Quest(){}

    void app();
    void printHelp();
    void printMenu();
    int getUserOption();
    void processUserOption(int input);
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void withdraw(string product,double amount);
    void Deposit(string product,double amount);
    
};