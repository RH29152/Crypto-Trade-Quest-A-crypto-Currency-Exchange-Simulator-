#pragma once

#include<set>
#include<string>
#include<iostream>
#include"Csv_data_Read.h"
#include"Order_Book_Entry.h"
#include <climits>
#include<algorithm>
#include"Wallet.h"
using namespace std;

class MarketHelper{
  public:


// Here we are assigning current time to earliest time in orderBook By default
string CurrentTime=getEarliestTime(); 

/*Sub functions used in print market stats*/

 set<string> getKnownProducts();
 vector<Order_Book_Entry> getOrders(string Product,OrderBookType type,string timestamp);
 double getHigestPrice(vector<Order_Book_Entry> &Suborders);
 double getLowestPrice(vector<Order_Book_Entry> &Suborders);


/*TIme related Functions*/

string getEarliestTime();
string goToNextTime(string timestamp);


/*functions related to enter ask and bid*/

bool insertOrder(Order_Book_Entry &e);
string EnterTradeData();
string Concatenation(string line,string type,string time);



/*Matching engine : Heart of a Crypto Exchange simulator*/

  vector<Order_Book_Entry> BidOrders;
  vector<Order_Book_Entry> AskOrders;
  void filteringOrderBook();
  void SortingOrders();
  map<string,int> TotalSales(vector<Order_Book_Entry> sales);
  map<string,int> matchingEngine(Wallet &Assets);

};