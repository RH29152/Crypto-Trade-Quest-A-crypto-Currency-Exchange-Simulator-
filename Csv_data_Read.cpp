
#include"Csv_data_Read.h"

       //This function takes ordertype(bid or ask) in string and return enum type of ordertype   
       OrderBookType Csv_data_Read::orderType(string bid_ask){
         OrderBookType type;

        if(bid_ask=="bid"){
            type=OrderBookType::bid;
        }
        if(bid_ask=="ask"){
        type=OrderBookType::ask;
        }
      return type;
}


   Order_Book_Entry Csv_data_Read::tokenise(string line) {

    if(line.empty()){
         throw underflow_error("This line is empty");
    }
    
    string timeSTamp, product, type;
    OrderBookType ordertype;
    double Price, amount;


    stringstream ss(line);

        // Read each field from the line into respective data types
        if (!getline(ss, timeSTamp, ',')) {
            throw invalid_argument("Problem in Reading TimeStamp in class Csv_data_Read");

        }
        if (!getline(ss, product, ',')) {
            throw invalid_argument("Problem in Reading product in class Csv_data_Read");
             
        }
        if (!getline(ss, type, ',')) {
            throw invalid_argument("Problem in Reading ordertype in class Csv_data_Read");

        }
        if (!(ss >> Price)) {
            throw invalid_argument("Problem in Reading price in class Csv_data_Read");

        }

        // Skip the comma which will cause problem in cin
        char coma;
        ss >> coma;


        if (!(ss >> amount)) {
            throw invalid_argument("Problem in Reading amount in class Csv_data_Read");
        }
        

          ordertype=orderType(type);   // converting string to enum type which is attribute of order-book-entry class
        Order_Book_Entry obe{timeSTamp, product,ordertype, Price, amount};
        obe.username="defaultUser";
        
         return obe;
}



    
    //Reads data from a CSV file and stores it in a vector.
    void Csv_data_Read::readingCsvFile(string filename){
         ifstream file(filename);

    if(!file){
        cout<<"file is'nt opened"<<endl;
        return;
    }
    string line;

    while(getline(file,line)){
        try {
        Order_Book_Entry obe=tokenise(line);

        Csv_data_Read::csvFileData.push_back(obe);

        } catch (exception& e) {

        cout << " \033[91mCaught an exception: " << e.what()<<"\033[0m"<< endl;
        }

    }
}

