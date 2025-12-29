#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility> 
#include <fstream>
#include <sstream>

using namespace std;

class Transaction {    
    public:
    string id;
    int amount_cents;
    string type;
    string category_id;
    string date;
    string note;

    //Ctor
    Transaction(){
        id = "";
        amount_cents = 0;
        type = "";
        category_id = "";
        date = "";
        note = "";
    }

    //Dtor
    ~Transaction(){}

    //Copy Ctor
    Transaction(const Transaction & other){
        if(this == &other) return;
        id = other.id;
        amount_cents = other.amount_cents;
        type = other.type;
        category_id = other.category_id;
        date = other.date;
        note = other.note;
    }

    //Assignment Operator
    Transaction & operator=(const Transaction & other){
        if(this == &other) return *this;
        id = other.id;
        amount_cents = other.amount_cents;
        type = other.type;
        category_id = other.category_id;
        date = other.date;
        note = other.note;
        return *this;
    } 

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
        load_transactions("data/transactions.csv");
    }

    //Dtor
    ~TransactionManager(){

        save_transactions("data/transactions.csv");

        for(pair<string, Transaction *> pr : transaction_db){
            delete_Transaction(pr.second);
        }
    }

    //Load From File
    void load_transactions(string filepath){

        fstream fin;
        fin.open(filepath, ios::in);
        if(!fin.is_open()){
            cout << "Error Opening File" << endl;
            return;
        }

        vector<string> row;
        string line, word, temp;

        while(fin >> line){
            row.clear();

            stringstream sstream (line);

            while(getline(sstream, word, ',')){
                row.push_back(word);
            }

            Transaction * newT = new Transaction();
            newT->id = row[0];
            newT->amount_cents = stoi(row[1]);
            newT->type = row[2];
            newT->category_id = row[3];
            newT->date = row[4];
            newT->note = row[5];

            transaction_db.insert(make_pair(newT->id, newT));
            map_size += 1;
        }

    }

    //Upload To File
    void save_transactions(string filepath){
        fstream fout;
        fout.open(filepath, ios::out);

        if(!fout.is_open()){
            cout << "Error Opening File" << endl;
            return;
        }   

        //delete existing content
        fout << "";

        for(pair<string, Transaction *> pr : transaction_db){
            Transaction * tx = pr.second;
            fout << tx->id << "," << tx->amount_cents << "," << tx->type << "," << tx->category_id << "," << tx->date << "," << tx->note << endl;
        }
    }

    //Add Transaction
    void add_Transaction(){

        cout << "_________________________" << endl;

        Transaction * newT = new Transaction();

        //ID
        newT->id = "tx_" + to_string(map_size + 1);

        //Amt
        string amount_raw;
        cout << "Dollar Amount ex. (12.34) $" ;
        get_input(amount_raw);
        newT->amount_cents = clean_amount(amount_raw); //Helper 1

        //Type
        string type;
        cout << "What Type of Transaction Is This?" << endl;
        cout << "1) Expense, 2) Earning, 3) Transfer : " ;
        get_input(type);
        type = transfer_type(type); //Helper 2
        newT->type = type;

        //category_id
        cout << "Category id: ";
        get_input(newT->category_id);


        //Date
        cout << "Date (YYYY-MM-DD): ";
        get_input(newT->date);

        //Note
        cout << "Note: ";
        get_input(newT->note);

        transaction_db.insert(make_pair(newT->id, newT));   

        map_size += 1;
    }

    //Delete Transaction by Pointer
    void delete_Transaction(Transaction * tx){
        delete tx;
        map_size -= 1;
    }

    //Delete Transaction by ID
    void delete_Transaction(string tx_id){
        auto it = transaction_db.find(tx_id);
        if(it != transaction_db.end()){
            delete it->second;
            transaction_db.erase(it);
            map_size -= 1;
        }
    }

    //List Transactions
    void list_Transactions(){
        for(pair<string, Transaction *> pr : transaction_db){
            cout << endl << "------------------------" << endl;
            cout << "ID: " << pr.second->id << endl;
            cout << "Amount (cents): " << pr.second->amount_cents << endl;
            cout << "Type: " << pr.second->type << endl;
            cout << "Category ID: " << pr.second->category_id << endl;
            cout << "Date: " << pr.second->date << endl;
            cout << "Note: " << pr.second->note << endl;
            cout << "------------------------" << endl << endl;
        }
    }

    //Modify Transaction
    void modify_Transaction(){
        string tx_id;
        cout << "Enter Transaction ID to Modify: ";
        get_input(tx_id);

        auto it = transaction_db.find(tx_id);
        if(it == transaction_db.end()){
            cout << "Transaction Not Found" << endl;
            return;
        }

        Transaction * tx = it->second;

        cout << "Modifying Transaction ID: " << tx->id << endl;

        //Amt
        string amount_raw;
        cout << "New Dollar Amount ex. (12.34) $";
        get_input(amount_raw);
        tx->amount_cents = clean_amount(amount_raw); //Helper 1

        //Type
        string type;
        cout << "What Type of Transaction Is This?" << endl;
        cout << "1) Expense, 2) Earning, 3) Transfer : ";
        get_input(type);
        type = transfer_type(type); //Helper 2
        tx->type = type;

        //category_id
        cout << "New Category id: ";
        get_input(tx->category_id);

    }

    private:

    //Main data sctructure for storage of all transactions
    map<string, Transaction *> transaction_db;
    int map_size;

    //Helper 1
    int clean_amount(string raw){
        double amt = stod(raw);
        amt *= 100;
        return amt;
    }

    //Helper 2
    string transfer_type(string type){
        int int_type = stoi(type);
        if(int_type == 1) return "Expense";
        if(int_type == 2) return "Earning";
        if(int_type == 3) return "Transfer";
        else return "error";
    }

    //Input Validation Template
    template <typename T>
    void get_input(T &input){
        while(!(cin >> input)){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input" << endl;
        }
    }



};