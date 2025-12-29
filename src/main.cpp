#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility> 
#include "TransactionManager.cpp"

using namespace std;

template <typename T>
void get_input(T &input){
    while(!(cin >> input)){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input" << endl;
    }
}

void load_from_file(TransactionManager & txm){

    string filepath = "data/transactions.csv";

    txm.load_transactions(filepath);
}

void save_to_file(TransactionManager & txm){ 
    
    string filepath = "data/transactions.csv";

    txm.save_transactions(filepath);
}


int main(){

    bool flag = true;

    TransactionManager txm;

    load_from_file(txm);

    while(flag){

        //Selection Menu
        cout << "_________________________" << endl;
        cout << "Welcome to Expense Tracker " << endl;
        cout << "Select an Option"<< endl;
        cout << "1) Show Database " << endl;
        cout << "2) Edit Transactions" << endl;
        cout << "3) Sync File" << endl;
        cout << "4) Exit" << endl;
        cout << "_________________________" << endl;
        cout << "Choice: ";

        //Choice validation
        int choice;
        get_input(choice);

        //Listing DB
        if(choice == 1){
            txm.list_Transactions();    
            continue;
        }

        //Edit Transactions
        if(choice == 2){
            cout << "Select an Option"<< endl;
            cout << "1) Add Transaction" << endl;
            cout << "2) Edit Transactions" << endl;
            cout << "3) Delete Transactions" << endl;

            int tx_choice;
            get_input(tx_choice);

            if(tx_choice == 1){
                txm.add_Transaction();
            }
            if(tx_choice == 2){
                txm.modify_Transaction();
            }
            if(tx_choice == 3){
                string tx_id;
                cout << "Enter Transaction ID to Delete: ";
                get_input(tx_id);
                txm.delete_Transaction(tx_id);
            }

            continue;
        }

        //Sync File
        if(choice == 3){
            save_to_file(txm);
            cout << "File Synced!" << endl;
            continue;
        }

        //Exiting Loop
        if(choice == 4){
            flag = false;
            cout << "Exiting Program..." << endl;
            save_to_file(txm);
        }




        




    }




    return 0;
}