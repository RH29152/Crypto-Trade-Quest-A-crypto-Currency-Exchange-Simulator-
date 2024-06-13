#include"Crypto_Trade_Quest.h"
#include<iostream>
using namespace std;




//Operator of whole project
    void Crypto_Trade_Quest::app(){
    while(true){
        
    printMenu();
try{

    int input=getUserOption();
    processUserOption(input);
  }
catch(exception&e){
    cout<<"caught an exception: "<<e.what()<<endl;
 }
    }

}


//This function prints help for user
void Crypto_Trade_Quest::printHelp(){
    cout<<"Market looks good \n Go and make offer"<<endl;
}

//This function prints menu for our crypto exchange
void Crypto_Trade_Quest::printMenu(){
    cout<<"\033[1;36m***************************************\033[0m"<<endl;
    cout<<"\033[1;33m1-print Help\033[0m"<<endl;
    cout<<"\033[1;33m2-print Market statistics\033[0m"<<endl;
    cout<<"\033[1;33m3-Enter ask(i.e sell trade)\033[0m"<<endl;
    cout<<"\033[1;33m4-Enter bid(i.e buy trade)\033[0m"<<endl;
    cout<<"\033[1;33m5-print Wallet statistics\033[0m"<<endl;
    cout<<"\033[1;33m6-Withdraw assets\033[0m"<<endl;
    cout<<"\033[1;33m7-Deposit assets\033[0m"<<endl;
    cout<<"\033[1;33m8-continue(go to next TimeFrame)\033[0m"<<endl;
    cout<<"\033[1;32mCurrent time is:  "<<helperFunc.CurrentTime<<"\033[0m"<<endl;
    cout<<"\033[1;36m***************************************\033[0m"<<endl;
}

//This function asks user to enter his choice
 int Crypto_Trade_Quest::getUserOption(){
    int input;
    cout<<"Enter you choice"<<endl;
    if(!(cin>>input)){
        throw runtime_error("Bad input");
    }

    return input;
    }


    //this function prints market stats
     void Crypto_Trade_Quest::printMarketStats(){
         string type;
         { //prompt user to enter which type of orders stats needed(bids or asks);
           cout<<"Enter stats type: (Enter bids or asks): "<<endl;
           cin>>type;
         }
         OrderBookType OType=CsvFile.orderType(type);
        cout<<"\033[1;32m"<<"Current Time: "<<"\033[1;34m"<<helperFunc.CurrentTime<<"\033[0m"<<endl;
        for(const string& p:helperFunc.getKnownProducts()){
         cout<<"Product: "<<p<<endl;

        vector<Order_Book_Entry> entries=helperFunc.getOrders(p,OrderBookType::bid,helperFunc.CurrentTime);
         if(type=="asks"){
       cout<<"\033[1;32m"<<"********** ASK STATS **********"<<"\033[0m"<<endl;
       cout<<"Total number of asks: "<<"\033[1;34m"<<entries.size()<<"\033[0m"<<endl;
       cout<<"Min Ask:"<<"\033[1;34m"<<helperFunc.getLowestPrice(entries)<<"\033[0m"<<endl;
       cout<<"Max Ask:"<<"\033[1;34m"<<helperFunc.getHigestPrice(entries)<<"\033[0m"<<endl;
       cout<<"********************************" <<endl;
}

     if(type=="bids"){
    cout<<"\033[1;32m"<<"********** BID STATS **********"<<"\033[0m"<<endl;
    cout<<"Total number of bids: "<<"\033[1;34m" << entries.size() << "\033[0m"<<std::endl;
    cout<<"Min Bid:"<<"\033[1;34m"<< helperFunc.getLowestPrice(entries)<<"\033[0m"<<endl;
    cout<<"Max Bid:"<<"\033[1;34m"<< helperFunc.getHigestPrice(entries)<<"\033[0m"<<endl;
    cout<<"********************************" << std::endl << std::endl;
}



        }
        
     }


//This function ask from user to enter his ask(sell trade)
     void Crypto_Trade_Quest::enterAsk(){
        try{
      string input=helperFunc.EnterTradeData();
      string line=helperFunc.Concatenation(input,"ask",helperFunc.CurrentTime);

      Order_Book_Entry e=CsvFile.tokenise(line);
     e.username="Currentseller";

     if(Assets.CanFulfilOrder(e)){

     if(helperFunc.insertOrder(e)){
     cout<<"Order placed successfully."<<endl;
     cout<<"Order is: "<<e.TimeStamp<<","<<e.product<<","<<"ask"<<","<<e.price<<","<<e.amount<<endl;
     }

   } 
else {
    cout<<"Order Failed Due to Insufficient Balance."<<endl;
     } 
}catch(exception&e){
        cout<<"Caught an exception: "<<e.what()<<endl;
      }
}



//This function ask from user to enter his bid(buy trade)
    void Crypto_Trade_Quest::enterBid(){
       try{
      string input=helperFunc.EnterTradeData();
      string line=helperFunc.Concatenation(input,"bid",helperFunc.CurrentTime);

      Order_Book_Entry e=CsvFile.tokenise(line);
      e.username="CurrentBuyer";
      
    if(Assets.CanFulfilOrder(e)){
     if(helperFunc.insertOrder(e)){
     cout<<"Order placed successfully."<<endl;
     cout<<"Order is: "<<e.TimeStamp<<","<<e.product<<","<<"bid"<<","<<e.price<<","<<e.amount<<endl;
      } 
    }
else {
    cout<<"Order Failed Due to Insufficient Balancce."<<endl;
     }
}catch(exception&e){
        cout<<"Caught an exception: "<<e.what()<<endl;
      }
}


//This function prints wallet containings
    void Crypto_Trade_Quest::printWallet(){
    Assets.PrintWallet();
    }

//This function changed to next TimeFrame
    void Crypto_Trade_Quest::gotoNextTimeframe(){
        
        //matching engine calling
        map<string,int> Sales=helperFunc.matchingEngine(Assets);
        for(auto i:helperFunc.getKnownProducts()){
         if(Sales.find(i)==Sales.end()){
            Sales[i]=0;
         }
        }
           cout<<"\033[1;32mCurrent Time:\033[0m"<<"\033[1;34m"<<helperFunc.CurrentTime<<"\033[0m"<< endl;
         for(const auto i:Sales){
           cout<<"\033[1;33m******************************\033[0m"<<endl;
           cout<<"\033[1;32mProduct: \033[0m"<<"\033[1;34m"<<i.first<<"\033[0m"<<endl;
           cout<<"\033[1;32mSales: \033[0m"<<"\033[1;34m"<<i.second<<"\033[0m"<<endl;
           cout<<"\033[1;33m******************************\033[0m"<<endl;
}

        helperFunc.CurrentTime=helperFunc.goToNextTime(helperFunc.CurrentTime);  //this updates time
        cout<<"Going to next timeFrame"<<endl;

    }


    void Crypto_Trade_Quest::withdraw(string product,double amount){
        if(amount<=0){
            throw invalid_argument("Amount is less than or equal to 0.");
        }
        Assets.Currencies[product]-=amount;

    }
    void Crypto_Trade_Quest::Deposit(string product,double amount){
        if(amount<=0){
            throw invalid_argument("Amount is less than or equal to 0.");
        }
        Assets.Currencies[product]+=amount;

    }

    //This function process user options
    void  Crypto_Trade_Quest::processUserOption(int input){

if(input==1){
    printHelp();
}
else if(input==2){
    printMarketStats();
}
else if(input==3){
    enterAsk();
}
else if(input==4){
    enterBid();
}
else if(input==5){
    printWallet();
}
else if(input==6){
    string prod;
    double amount;
    cout<<"Enter currency name:(BTC,USDT,ETH,DOGE):"<<endl;
    cin>>prod;
    if(prod!="BTC" && prod!="USDT" && prod!="ETH" && prod!="DOGE"){
        throw invalid_argument("Invalid currency name");
    }
    cout<<"Enter amount:"<<endl;
    cin>>amount;
    withdraw(prod,amount);
    cout<<"Withdrawn Successfully!"<<endl;

}
else if(input==7){
string prod;
    double amount;
    cout<<"Enter currency name:(BTC,USDT,ETH,DOGE):"<<endl;
    cin>>prod;
    if(prod!="BTC" && prod!="USDT" && prod!="ETH" && prod!="DOGE"){
        throw invalid_argument("Invalid currency name");
    }
    cout<<"Enter amount:"<<endl;
    cin>>amount;
    Deposit(prod,amount);
    cout<<"Deposited Successfully!"<<endl;
}
else if(input==8){
    gotoNextTimeframe();
}
else {
    cout<<"Invalid input,,,,,,,,Try Again....."<<endl;
}

    }


    