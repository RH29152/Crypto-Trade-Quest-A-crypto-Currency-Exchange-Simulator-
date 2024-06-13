#include"Order_Book_Entry.h"


Order_Book_Entry::Order_Book_Entry(string time,string p,OrderBookType type,double Priz,double amnt){
 TimeStamp=time;
 product=p;
 OrderType=type;
 price=Priz;
 amount=amnt;
}



