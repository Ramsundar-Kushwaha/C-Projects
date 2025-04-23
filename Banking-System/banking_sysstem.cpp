//C++ - Project - 01 - Banking Program - Console Application
#include<iostream>
using namespace std;

class Bank{
  private:
    // static double deposite = 0;
    double deposite = 0;
    double withDraw;

  public:
    //method for depositing balance
    void depositeBalance(){

      double tempMoneyHolder;
      // double* ptr = &deposite;

      cout << "Enter the balance to be deposite:\t";
      cin >> tempMoneyHolder;
      if(tempMoneyHolder <= 0){
        cout<<endl;
        cout<<"------------------------------Deposite Balance------------------------------"<<endl;
        cout<<endl;
        cout << "[Invalid Deposite\t\t"<<"status:\tUnsuccefull]";
        cout<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------"<<endl;
      }
      else{

        deposite = deposite + tempMoneyHolder;
        // *ptr = *ptr + tempMoneyHolder;//problem
        cout<<endl;
  
        cout<<"------------------------------Deposite Balance------------------------------"<<endl;
        cout<<endl;
        cout<<"[Deposited Amount:\t"<<tempMoneyHolder<<"$\t\t";
        cout<<"Status:\t"<<"Successfull.]"<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------"<<endl;
      }

    }

    //method to Show Balance the balance
    void ShowBalance(){
      cout<<endl;

      cout<<"------------------------------Current Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Current Balance:\t"<<deposite<<"$]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

    }
    
    //method for balance withDraw
    void drawBalance(){
      cout<<"Enter Amount($):\t";
      cin >> withDraw;
      cout<<endl;

      if( withDraw > deposite){

        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Insufficient Balance.]";
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

      }

      if(withDraw <= 0 && deposite >= 0){
        
        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Invalid Input.]";
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

      }

      if(withDraw <= deposite && withDraw > 0){

        deposite = deposite - withDraw;

        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Withdraw Amount:\t"<<withDraw<<"$\t\t";
        cout<<"Status:\t"<<"Successfull.]"<<endl;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

      }

    }

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

      return action;
    }

    //verify condition and performs menu action provided by user
    int performActions(int action) {

      if(action == 1){

        depositeBalance();
        cout<<endl;
        return 1;

      }

      if(action == 2){

        ShowBalance();
        cout<<endl;
        return 1;

      }

      if(action == 3){

        drawBalance();
        cout<<endl;
        return 1;

      }

      else{

        return 0;
      }
    }

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

int main(){
  cout<<"**************************** BANKING PROGRAM ****************************";
  Bank menu;
  menu.bankFacilities();
  return 0;
}