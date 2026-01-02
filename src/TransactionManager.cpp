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

    bool contains_keyword(const string & keyword){
        if(id.find(keyword) != string::npos) return true;
        if(type.find(keyword) != string::npos) return true;
        if(category_id.find(keyword) != string::npos) return true;
        if(date.find(keyword) != string::npos) return true;
        if(note.find(keyword) != string::npos) return true;
        return false;
    }
};

struct Category {
    int id;
    string name;
    
};

class sortType {
    public:
    sortType(string choice, map<string, Transaction *> &db) :  sort_choice(choice) , print_db(db){}

    bool operator()(string d1 , string d2){
        if(sort_choice == "date") 
            cout << print_db[d1]->date << " " << print_db[d2]->date << " " << (print_db[d1]->date < print_db[d2]->date  ) << endl;
            return print_db[d1]->date < print_db[d2]->date;
        if(sort_choice == "amount_cents")  
            return print_db[d1]->amount_cents > print_db[d2]->amount_cents;
        return false;
    }

    private:
    string sort_choice;
    map<string, Transaction *> &print_db;
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
    void list_Transactions_default(string sort_choice, vector<string> filter_list){

        //Check if DB is empty
        if(transaction_db.size() == 0){
            cout << "No Transactions to Display" << endl;
            return;
        }

        map<string, Transaction *> print_db = transaction_db; //Make a copy to preserve original data  

        //Get Unsorted IDs
        vector<string> id_list = get_transaction_ids();

        //Sorting Sorting Logic Here
        if(sort_choice != ""){

            cout << "here" << endl;

            //Validate Sort Choice
            if(sort_choice != "date" && sort_choice != "amount_cents"){
                cout << "Invalid Sort Choice" << endl;
                return;
            }

            sortType sorter(sort_choice, print_db);
            sort(id_list.begin(), id_list.end(), [&](string d1, string d2){
                return sorter(d1, d2);
            });

            //Reorder the map based on sorted IDs
            map<string, Transaction *> sorted_map;
            for(string id : id_list){
                sorted_map.insert(make_pair(id, transaction_db[id]));
            }
            transaction_db = sorted_map;   

        }

        //Display Transactions
        cout << "_________________________" << endl;
        for(pair<string, Transaction *> pr : transaction_db){
            //Filter by not printing if filter_list is not empty & transaction does not match any filter
            if(!filter_list.empty()){
                bool match = false;
                for(string filter : filter_list){
                    if(pr.second->contains_keyword(filter)){
                        match = true;
                        break;
                    }
                }
                if(!match) continue; 
            }
            Transaction * tx = pr.second;
            cout << "ID: " << tx->id << " \t| Amount (cents): " << tx->amount_cents << " \t| Type: " << tx->type << " \t| Category ID: " << tx->category_id << " \t| Date: " << tx->date << " \t| Note: " << tx->note << endl;
        }   
    }

    // List Transactions Filtered
    void list_Transactions_filtered(string sort_choice, vector<string> filter_list){

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

    vector <string> get_transaction_ids(){
        vector<string> ids;
        for(pair<string, Transaction *> pr : transaction_db){
            ids.push_back(pr.first);
        }
        return ids;
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