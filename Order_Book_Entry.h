#pragma once

#include<string>
#include<iostream>
using namespace std;

enum class OrderBookType{bid,ask};


class Order_Book_Entry{
 public:
    string TimeStamp;
    string product;
    OrderBookType OrderType;
    double price;
    double amount;
    string username;
    

   

    Order_Book_Entry(string time,string p,OrderBookType type,double Priz,double amnt);
    
};