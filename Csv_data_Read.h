#pragma once

#include"Order_Book_Entry.h"
#include<sstream>
#include<fstream>
#include<string>
#include<exception>
#include<vector>

class Csv_data_Read{
public: 
Csv_data_Read(string filename){
readingCsvFile(filename);
}
      static vector<Order_Book_Entry> csvFileData; // this vector stores whole orderbook data
      OrderBookType orderType(string bid_ask);
      Order_Book_Entry tokenise(string line);
      void readingCsvFile(string filename);


};



