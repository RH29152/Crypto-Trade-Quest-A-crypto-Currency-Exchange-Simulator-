#include"Wallet.h"


Wallet::Wallet(){}


void Wallet::PrintWallet(){
        cout<<"\033[32m$|#######~~~~~~~~~~~#Wallet#~~~~~~~~~~~~~~######$\033[0m"<<endl;
        cout<<"\033[35m#|"<<"\033[34m             Product:Amount\033[0m"<<endl;
        for(auto&e:Currencies){
        cout<<"\033[35m#|\033[0m"<<"\033[33m               "<<e.first<<string(" ",max(0,4-(int)(e.first.length())))<<" : "<<e.second<<endl;
        }
        cout<<"\033[32m$$|####~~~~~~~~~~~~~~########~~~~~~~~~~~~~~~#####$\033[0m"<<endl;

    }
 

     void Wallet::UpdateWallet(const Order_Book_Entry obe){

         int i=obe.product.find('/');
         string ProdAdd;
         string ProdRemove;
         if(obe.OrderType==OrderBookType::bid){
          ProdAdd=obe.product.substr(0,i);
          ProdRemove=obe.product.substr(i+1);

          Currencies[ProdAdd]+=obe.amount; 
          Currencies[ProdRemove]-=(obe.amount*obe.price);
         }
         else{
                ProdAdd=obe.product.substr(i+1);
                ProdRemove=obe.product.substr(0,i);

                Currencies[ProdAdd]+=(obe.amount*obe.price); 
                Currencies[ProdRemove]-=obe.amount;
                
            }
    }


    bool Wallet::CanFulfilOrder(const Order_Book_Entry obe){
        string prod;
        if(obe.OrderType==OrderBookType::bid) {
             prod=obe.product.substr(obe.product.find('/')+1);
             if(Currencies[prod]>=(obe.amount*obe.price)){
             return true;
       }
}
        else{
            prod=obe.product.substr(0,obe.product.find('/'));
            if(Currencies[prod]>=(obe.amount)){
            return true;
            } 
          }
        
       return false;
    }