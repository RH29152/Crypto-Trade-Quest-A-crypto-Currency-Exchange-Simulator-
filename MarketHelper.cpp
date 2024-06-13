#include"MarketHelper.h"


vector<Order_Book_Entry> Csv_data_Read::csvFileData;

// This function return a set of all the products(i.e trading pair) in data
set<string> MarketHelper::getKnownProducts(){

    set<string> products;

        for(int i=0;i<Csv_data_Read::csvFileData.size();i++){
            products.insert(Csv_data_Read::csvFileData[i].product);

        } 


return products;
        
}


//This function filters the csv data according to given filters
vector<Order_Book_Entry> MarketHelper::getOrders(string Product,OrderBookType type,string timestamp){
    vector<Order_Book_Entry> subOrders;
      
     for(const Order_Book_Entry &e:Csv_data_Read::csvFileData){
        if(e.product==Product && e.OrderType==type && e.TimeStamp== timestamp){
            subOrders.push_back(e);
        }
     } 

return subOrders;
}


//This function return highest price from a filtered csv data vector where a specific(i.e one) product available
double MarketHelper::getHigestPrice(vector<Order_Book_Entry> &Suborders){
double max=INT_MIN;

for(const Order_Book_Entry&e:Suborders){
    if(e.price>max){
        max=e.price;
    }
}

return max;

}


//This function return lowest price from a filtered csv data vector where a specific(i.e one) product available
double MarketHelper::getLowestPrice(vector<Order_Book_Entry> &Suborders){
double min=INT_MAX;

for(const Order_Book_Entry&e:Suborders){
    if(e.price<min){
        min=e.price;
    }
}

return min;

}



//**********************************Time functions************************************************


//This function return first time in the csv data 
string MarketHelper::getEarliestTime()
{
    return Csv_data_Read::csvFileData[0].TimeStamp;
}

//This function return the next time against the given time to it
string MarketHelper::goToNextTime(string timestamp){
    
for(Order_Book_Entry&e: Csv_data_Read::csvFileData){
    if(e.TimeStamp>timestamp){
        return e.TimeStamp;
    }
}
return getEarliestTime();

}





//**********************************bid ask  functions************************************************


//This function takes users input/desired trade to buy currencies
string MarketHelper::EnterTradeData(){
  cin.ignore();
  string line;
cout<<"Enter the Product,price,amount:(e.g:ETH/USDT,117.73683245,63.56)"<<endl;
if(!getline(cin,line)){
  throw runtime_error("Error in getting user input");
}
return line;
}



//This function concatenate a string to make it a complete csv file string line
string MarketHelper::Concatenation(string line,string type,string time){

int index=line.find(',');
line.insert(index+1,((type)+','));

return (time+','+line);
}



//this function takes an order and insert it in csvFile data vector
bool MarketHelper::insertOrder(Order_Book_Entry &e){
  bool isDone=true;
  try{
 Csv_data_Read::csvFileData.push_back(e);
  }
  catch(exception&e){
    isDone=false;
     throw e;
  }
return isDone;
} 





//**********************************Matching Engine  functions************************************************

//This function filters The orderBook and store all bids orders and asks orders in two different vectors w.r.t current time
 void MarketHelper::filteringOrderBook(){
      BidOrders.clear();
      AskOrders.clear();
    for(auto i: MarketHelper::getKnownProducts()){
     
      vector<Order_Book_Entry> Buys=getOrders(i,OrderBookType::bid,CurrentTime);
      vector<Order_Book_Entry> sells=getOrders(i,OrderBookType::ask,CurrentTime);
      BidOrders.insert(BidOrders.end(),Buys.begin(),Buys.end());
      AskOrders.insert(AskOrders.end(),sells.begin(),sells.end());

    }

 }

 //This function Sorts the obtained two vectors w.r.t price for different priorities for each vector using lambdas
  void MarketHelper::SortingOrders(){
    auto descending=[](auto i,auto j){return i.price>j.price;};
    auto ascending=[](auto i,auto j){return i.price<j.price;};
    sort(BidOrders.begin(),BidOrders.end(),descending);
    sort(AskOrders.begin(),AskOrders.end(),ascending);
  }


    map<string,int> MarketHelper::TotalSales(vector<Order_Book_Entry> sales){
            map<string,int> result;
             
             for(const auto &i: sales){
               result[i.product]+=1;
             }

             return result;

    }


map<string,int> MarketHelper::matchingEngine(Wallet &Assets){
    filteringOrderBook();
    SortingOrders();
    vector<Order_Book_Entry> Sales;

    for(auto &i:BidOrders){
        for(auto &j: AskOrders){
            if(i.price>=j.price && i.product==j.product && i.amount <= j.amount && i.amount!=0 && j.amount!=0){

                if(i.amount==j.amount){

                if(i.username=="CurrentBuyer"){
                 Assets.UpdateWallet(i);  }
                 else if(j.username=="Currentseller"){
                  i.OrderType=OrderBookType::ask;
                  Assets.UpdateWallet(i);
                  i.OrderType=OrderBookType::bid;}

                    Sales.push_back(i);
                    i.amount=0;
                    j.amount=0;

                    break;
                }

                if(i.amount<j.amount){
                  if(i.username=="CurrentBuyer"){
                  Assets.UpdateWallet(i);}
                  else if(j.username=="Currentseller"){
                    i.OrderType=OrderBookType::ask;
                  Assets.UpdateWallet(i);
                  i.OrderType=OrderBookType::bid;
                  }

                    Sales.push_back(i);
                     j.amount-= i.amount;
                     i.amount=0;
                     break;
                }


                if(i.amount>j.amount){

                  if(i.username=="CurrentBuyer"){
                   Assets.UpdateWallet(i);}
                  else if(j.username=="Currentseller"){
                    i.OrderType=OrderBookType::ask;
                    Assets.UpdateWallet(i);
                    i.OrderType=OrderBookType::bid;
                  }
                   
                    Sales.push_back(i);
                     i.amount-= j.amount;
                     j.amount=0;
                    break;
                }
                
            }

        }
    }
    map<string,int> salesData=TotalSales(Sales);

      return salesData; 
}






