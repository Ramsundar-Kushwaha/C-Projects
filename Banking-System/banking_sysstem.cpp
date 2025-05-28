//C++ - Project - 01 - Banking Program - Console Application
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Bank{
  private:
    double deposite = 0;
    double withDraw;

  public:
    //method for depositing balance
    void depositeBalance(){

      double tempMoneyHolder;

      cout << "Enter the balance to be deposite:\t";
      cin >> tempMoneyHolder;

      //Exception handling or Error handling
      try{
        if(cin.fail()){
          throw invalid_argument("Invalid Input");
        }

        else if(tempMoneyHolder <= 0){
          throw out_of_range("Deposite Must be greater than 0 $");
        }
      }
      catch(...){
        cout<<endl;
        cout<<"------------------------------Deposite Balance------------------------------"<<endl;
        cout<<endl;
        cout << "[Invalid Deposite\t\t"<<"status:\tUnsuccefull]";
        cout<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------"<<endl;
        exit(0);
      }

      //file hanling for loading previous balance
      fstream dload("deposite.txt", ios::in);
      if(!dload.is_open()){
        cerr << "File Processing | status: Failed" << endl;
      }
      else{
        string line;
        getline(dload, line);
        if(!line.empty()){
          try{
            deposite = stod(line);
          }
          catch(const exception& e){
            cerr << "Invalid Number Format in file" << endl;
            exit(0);
          }
        }
      }

      dload.close();
      
      deposite = deposite + tempMoneyHolder;

      cout<<endl;
      cout<<"------------------------------Deposite Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Deposited Amount:\t"<<tempMoneyHolder<<"$\t\t";
      cout<<"Status:\t"<<"Successfull.]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

      //file handling
      fstream dfin("deposite.txt", ios::out);
      if(!dfin.is_open()){
        cerr << "File Processing | status: Failed" << endl;
      }
      else{
        dfin << deposite;
      }

      dfin.close();

      //history file handling
      fstream hfin("history.txt", ios::app);
      if(!hfin.is_open()){
        cerr << "File Processing | status : Failed"<<endl;
      }
      else{
        hfin << endl;
        hfin << "------------------------------Deposite Balance------------------------------" << endl;
        hfin << endl;
        hfin << "[Deposited Amount:\t"<<tempMoneyHolder << "$\t\t";
        hfin << "Status:\t"<<"Successfull.]" << endl;
        hfin << endl;
        hfin << "----------------------------------------------------------------------------" << endl;
        hfin << endl;
      }
      hfin.close();

    }


// ---------------------------------------------------------------------------------------------------------------------------
    //method to Show Balance the balance
    void showBalance(){

      fstream dfr("deposite.txt", ios::in);
      if(!dfr.is_open()){
        cerr << "File Processing | status: unsuccessful" << endl;
      }
      else{
        string line;
        getline(dfr, line);
        try{
          deposite = stod(line);
        }
        catch(const exception& e){
          cerr << "Invalid Number Format in file" << endl;
          exit(0);
        }

        // deposite += acbalance;
      }
      dfr.close();

      cout<<endl;
      cout<<"------------------------------Current Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Current Balance:\t"<<deposite<<"$]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

      //history file handling
      fstream hfr("history.txt", ios::app);
      if(!hfr.is_open()){
        cerr << "File Processing | status : Failed" << endl;
      }
      else{
        hfr << endl;
        hfr << "------------------------------Current Balance------------------------------" << endl;
        hfr << endl;
        hfr << "[Current Balance:\t"<<deposite<<"$]" << endl;
        hfr << endl;
        hfr << "----------------------------------------------------------------------------" << endl;
        hfr << endl;
      }

      hfr.close();
    }


// ---------------------------------------------------------------------------------------------------------------------------    
    //method for balance withDraw
    void drawBalance(){
      cout<<"Enter Amount($):\t";
      cin >> withDraw;

      //Exception handling or Error handling
      try{
        if(cin.fail()){
          throw invalid_argument("Invalid input");
        }
        else if( withDraw > deposite){
          throw out_of_range("out of range");
        }
        else if(withDraw <= 0 /*&& deposite >= 0*/){
          throw logic_error("Invalid amount");  
        }
      }

      catch(const invalid_argument& e){
        cout << "Invalid Input";
        exit(0);
      }
      catch(const out_of_range& e){
        cout<<endl;
        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Insufficient Balance.]" << e.what();
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        exit(0);
      }
      catch(const logic_error& e){
        cout<<endl;
        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Invalid Input.]" << e.what();
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        exit(0);
      }


      if(withDraw <= deposite && withDraw > 0){

        deposite = deposite - withDraw;

        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Withdraw Amount:\t"<<withDraw<<"$\t\t";
        cout<<"Status:\t"<<"Successfull.]"<<endl;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

        //file handling
        fstream dfile("deposite.txt", ios::out);
        if(!dfile.is_open()){
          cerr << "File Processing | status : unsuccessful";
        }
        else{
          dfile << deposite;
        }

        dfile.close();

        //history file handling
        fstream hfile("history.txt", ios::app);
        if(!hfile.is_open()){
          cerr << "File Processing | status : Failed" << endl;
        }
        else{
          hfile << endl;
          hfile << "---------------------------------Withdraw---------------------------------" << endl;
          hfile << endl;
          hfile << "[Withdraw Amount:\t" << withDraw << "$\t\t";
          hfile << "Status:\t" << "Successfull.]" << endl;
          hfile << endl;
          hfile << "---------------------------------------------------------------------------" << endl;
          hfile << endl;
        }

        hfile.close();

      }

    }


// ---------------------------------------------------------------------------------------------------------------------------
    //Bank Menu
    int bankMenu(void){
      int action;

      cout<<endl;

      cout<<"-------------------------"<<endl;
      cout<<"|1. Deposite Balance    |"<<endl;
      cout<<"|2. Show Balance        |"<<endl;
      cout<<"|3. Withdraw Balance    |"<<endl;
      cout<<"|4. Exit (press any key)|"<<endl;
      cout<<"-------------------------"<<endl;

      cout << "Choose Action:(1 - 3)\t";
      cin >> action;
      try{
        if(cin.fail()){
          throw invalid_argument("invalid input");
        }
        else if(action <=0 || action > 4){
          throw out_of_range("out of range");
        }
      }

      catch(invalid_argument& e){
        cout << "Invalid Input" << e.what() << endl;
        return 0;
      }
      catch(out_of_range& e){
        cout << "out of range" << e.what() << endl;
        return 0;
      }
      return action;
    }


// ---------------------------------------------------------------------------------------------------------------------------
    //verify condition and performs menu action provided by user
    int performActions(int action) {

      if(action == 1){

        depositeBalance();
        cout<<endl;
        return 1;

      }

      if(action == 2){

        showBalance();
        cout<<endl;
        return 1;

      }

      if(action == 3){

        drawBalance();
        cout<<endl;
        return 1;

      }

      else{
        fstream hfile("history.txt", ios::app);
        if(!hfile.is_open()){
          cerr << "File Processing | status : Failed" << endl;
        }
        else{
          hfile << endl;
          hfile << "------------------------------Exit | Successfull------------------------------" << endl;
          hfile << endl;
        }
        return 0;
      }
    }


// ---------------------------------------------------------------------------------------------------------------------------
    //functions for calling other functions to integrate the modules
    void bankFacilities(void){

      int x = bankMenu();
      int y = performActions(x);

      if(y == 1){

        bankFacilities();

      }

      else{

        cout<<"Exit Done";
      }
    }
};



// ---------------------------------------------------------------------------------------------------------------------------
int main(){
  cout<<"**************************** BANKING PROGRAM ****************************";
  Bank menu;
  menu.bankFacilities();
  return 0;
}