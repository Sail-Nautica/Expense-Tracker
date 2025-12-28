#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility> 

using namespace std;


class Transaction {    
    public:
    string id;
    int amount_cents;
    string type;
    string category_id;
    string date;
    string note;
};

struct Category {
    int id;
    string name;
};

class TransactionManager {

    public:
    
    //Default Ctor
    TransactionManager(){
        map_size = 0;
    }

    //Dtor
    ~TransactionManager(){
        for(pair<string, Transaction *> pr : transaction_db){
            delete_Transaction(pr.second);
        }
    }

    //Copy Ctor

    //Add Transaction
    Transaction * add_Transaction(){

        Transaction newT;

        //ID
        newT.id = "tx_" + to_string(map_size + 1);

        //Amt
        string amount_raw;
        cout << "Dollar Amount ex. (12.34) $" ;
        getline(cin, amount_raw);
        newT.amount_cents = clean_amount(amount_raw); //Helper 1

        //Type
        string type;
        cout << "What Type of Transaction Is This?" << endl;
        cout << "1) Expense, 2) Earning, 3) Transfer : " ;
        cin >> type;
        type = transfer_type(type); //Helper 2
        newT.type = type;

        //category_id
        cout << "Category id: ";
        getline(cin, newT.category_id);

        //Date
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, newT.date);

        //Note
        cout << "Note: ";
        getline(cin, newT.note);

        transaction_db[newT.id] = &newT;

    }

    //Delete Transaction
    Transaction * delete_Transaction(Transaction * tx){
        delete tx;
    }



    



    private:

    //Main data sctructure for storage of all transactions
    map<string, Transaction *> transaction_db;
    int map_size;

    //Helper 1
    int clean_amount(string raw){
        double amt = stoi(raw);
        amt *= 100;
        return amt;
    }

    //Helper 2
    string transfer_type(string type){
        int int_type = stoi(type);
        if(int_type == 0) return "Expense";
        if(int_type == 1) return "Earning";
        if(int_type == 2) return "Transfer";
        else return "error";
    }

};

int main(){

    bool flag = true;

    while(flag){
        
        TransactionManager txm;

        //Selection Menu
        cout << "Welcome to Expense Tracker " << endl;
        cout << "Select an Option"<< endl;
        cout << "1) Add Transaction " << endl;
        cout << "2) List Transactions" << endl;
        cout << "3) Modify Transaction" << endl;
        cout << "4) Exit" << endl;

        //Choice validation
        int choice;
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input" << endl;
            continue;
        }

        //Adding Transaction
        if(choice == 1){
            txm.add_Transaction();
        }
        




    }




    return 0;
}