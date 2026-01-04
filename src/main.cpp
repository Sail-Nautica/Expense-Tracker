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

    bool main_loop_flag = true;

    TransactionManager txm;

    load_from_file(txm);
    system("clear");

    string sort_choice;
    vector<string> filter_list;

    while(main_loop_flag){

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
            bool view_db_flag = true;
                while(view_db_flag){
                cout << "_________________________" << endl;
                cout << "1) DB List" << endl;
                cout << "2) Sort by ..." << endl;
                cout << "3) Filter by ..." << endl;
                cout << "4) Search ..." << endl;
                cout << "5) Reset View" << endl;
                cout << "6) Back to Main Menu" << endl;
                cout << "_________________________" << endl;
                cout << "Active Sorting/Filtering: " << sort_choice << endl;
                cout << "Active Filters: ";
                for(string filter : filter_list){
                    cout << filter << " ";
                }
                cout << endl << "Choice: ";

                int list_choice;
                get_input(list_choice);

                if(list_choice == 1){
                    txm.list_Transactions_default(sort_choice, filter_list);
                    continue;
                }
                if(list_choice == 2){
                    cout << "Sort by (date or amount_cents): ";
                    get_input(sort_choice);
                    cout << "Sorted by " << sort_choice << endl;
                    txm.list_Transactions_default(sort_choice, filter_list);
                    continue;
                }
                if(list_choice == 3){
                    string filter;
                    cout << "Enter filter keyword: ";
                    get_input(filter);
                    filter_list.push_back(filter);
                    cout << "Filter Added!" << endl;
                    txm.list_Transactions_default(sort_choice, filter_list);
                    continue;
                }
                if(list_choice == 4){
                    string search_term;
                    cout << "Enter search keyword: ";
                    get_input(search_term);
                    filter_list.push_back(search_term);
                    cout << "Search Added!" << endl;
                    txm.list_Transactions_default(sort_choice, filter_list);
                    continue;
                }
                if(list_choice == 5){   
                    sort_choice = "";
                    filter_list.clear();
                    cout << "View Reset!" << endl;
                    continue;  
                }
                if(list_choice == 6){
                    system("clear");
                    view_db_flag = false;
                    continue;
                }
            }
        }

        //Edit Transactions
        if(choice == 2){
            cout << "_________________________" << endl;
            cout << "Select an Option"<< endl;
            cout << "1) Add Transaction" << endl;
            cout << "2) Edit Transactions" << endl;
            cout << "3) Delete Transactions" << endl;
            cout << "4) Back to Main Menu" << endl;
            cout << "_________________________" << endl;
            cout << "Choice: ";

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
            if(tx_choice == 4){
                system("clear");
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
            main_loop_flag = false;
            cout << "Exiting Program..." << endl;
            save_to_file(txm);
        }

        system("clear");

        //Invalid Choice
        if(choice < 1 || choice > 4){
            cout << "Invalid Choice, Try Again" << endl;
        }
        

    }




    return 0;
}



 



