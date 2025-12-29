#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility> 
#include "TransactionManager.cpp"

using namespace std;


int main(){

    bool flag = true;

    TransactionManager txm;

    while(flag){

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
            continue;
        }

        //Listing Transactions
        if(choice == 2){
            txm.list_Transactions();
            continue;
        }

        //Exiting Loop
        if(choice == 4){
            flag = false;
        }




        




    }




    return 0;
}