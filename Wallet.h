#pragma once
#include<string>
#include<map>
#include<iostream>
#include<algorithm>
#include"Order_Book_Entry.h"
using namespace std;

class Wallet{ 
    public:
    map<string,double> Currencies;

    Wallet();
    //This function wallet stats like product:Amount
    void PrintWallet();
    
    //This function updates assets to wallet
    void UpdateWallet(const Order_Book_Entry obe);

     bool CanFulfilOrder(const Order_Book_Entry obe);


};