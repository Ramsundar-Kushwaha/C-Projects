//C++ - Project - 01 - Banking Program - Console Application
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>

using namespace std;

//for storing variables only which is used by many classes
class Variables{
  protected:
  double deposite = 0;
  double withDraw;
  string userName;
  int password;
};

// ---------------------------------------------------------------------------------------------------------------------------
//Banking System - Class
class Bank:public Variables{
  public:
    //method for depositing balance
    void depositeBalance(){

      double tempMoneyHolder;
      
      cout << "Enter the balance to be deposit:\t";
      cin >> tempMoneyHolder;

      //Exception handling or Error handling
      try{
        if(cin.fail()){
          throw invalid_argument("Invalid Input");
        }

        else if(tempMoneyHolder <= 0){
          throw out_of_range("Deposit Must be greater than 0 $");
        }
      }
      catch(...){
        cout<<endl;
        cout<<"------------------------------Deposit Balance------------------------------"<<endl;
        cout<<endl;
        cout << "[Invalid Deposit\t\t"<<"status:\tUnsucceful]";
        cout<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------"<<endl;
        exit(0);
      }

      //file handling for loading previous balance
      fstream dload("D_" + userName + ".txt", ios::in);
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
      cout<<"Status:\t"<<"Successful.]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

      //file handling
      fstream dfin("D_" + userName + ".txt", ios::out);
      if(!dfin.is_open()){
        cerr << "File Processing | status: Failed" << endl;
      }
      else{
        dfin << deposite;
      }

      dfin.close();

      //history file handling
      fstream hfin("H_" + userName + ".txt", ios::app);
      if(!hfin.is_open()){
        cerr << "File Processing | status : Failed"<<endl;
      }
      else{
        hfin << endl;
        hfin << "------------------------------Deposit Balance------------------------------" << endl;
        hfin << endl;
        hfin << "[Deposited Amount:\t"<<tempMoneyHolder << "$\t\t";
        hfin << "Status:\t"<<"Successful.]" << endl;
        hfin << endl;
        hfin << "----------------------------------------------------------------------------" << endl;
        hfin << endl;
      }
      hfin.close();

    }

    
    // ---------------------------------------------------------------------------------------------------------------------------
    //method to Show Balance the balance
    void showBalance(){

      fstream dfr("D_" + userName + ".txt", ios::in);
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

      }
      dfr.close();

      cout<<endl;
      cout<<"------------------------------Current Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Current Balance:\t"<<deposite<<"$]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

      //history file handling
      fstream hfr("H_" + userName + ".txt", ios::app);
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

      if(deposite == 0){

        fstream lodB("D_" + userName + ".txt", ios::in);

        if(!lodB.is_open()){
          cerr << "unable to load deposit balance";
          exit(0);
        }
        else{

          string line;
          int dep;
          getline(lodB, line);

          if(!line.empty()){
            try{
              dep = stoi(line);
            }
            catch(...){
              cout << "balance conversion error";
              exit(0);
            }

            deposite += dep;
            lodB.close();
          }
        }
      }
      
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
        else if(withDraw <= 0){
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
        cout<<"Status:\t"<<"Successful.]"<<endl;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

        //deposit file handling
        fstream dfile("D_" + userName + ".txt", ios::out);
        if(!dfile.is_open()){
          cerr << "File Processing | status : unsuccessful";
        }
        else{
          dfile << deposite;
        }

        dfile.close();
        
        //history file handling
        fstream hfile("H_" + userName + ".txt", ios::app);
        if(!hfile.is_open()){
          cerr << "File Processing | status : Failed" << endl;
        }
        else{
          hfile << endl;
          hfile << "---------------------------------Withdraw---------------------------------" << endl;
          hfile << endl;
          hfile << "[Withdraw Amount:\t" << withDraw << "$\t\t";
          hfile << "Status:\t" << "Successful.]" << endl;
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
      cout<<"|1. Deposit Balance     |"<<endl;
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
        fstream hfile("H_" + userName + ".txt", ios::app);
        if(!hfile.is_open()){
          cerr << "File Processing | status : Failed" << endl;
        }
        else{
          hfile << endl;
          hfile << "------------------------------Exit | Successful------------------------------" << endl;
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

//---------------------------------------------------------------------------------------------------------------------
//signUp and Login feature is under construction now
class accountLoginSignUp:public Bank{
  public:
  accountLoginSignUp(){
    int choice;
    cout << endl;
    cout << "Welcome User:" << endl;
    cout << "1.Login" << endl;
    cout << "2.signUp" << endl;
    cout << "Enter Your Choice: ";
    cin >> choice;

    try{
      if(cin.fail()){
        throw invalid_argument("Invalid Input : ");
      }
      else if(choice <= 0){
        throw -1;
      }
      else if(choice > 2){
        throw 1;
      }
    }
    catch(invalid_argument& e){
      cout << "Number Only";
      exit(0);
    }
    catch(...){
      cout << "Number Should Be Choosen either 1 or 2";
      exit(0);
    }

    if(choice == 2){
      signUp();
    }
    else{
      login();
    }
  }

  //for signUp or creating new account
  void signUp(){

    cout << "Sign Up here..." << endl;
    cout << "Enter Your Full Name: ";

    cin.ignore();
    getline(cin, userName);
    cout << "Password: ";
    cin >> password;

    try{
      if(cin.fail()){
        throw invalid_argument("invalid input : ");
      }
    }
    catch(invalid_argument& e){
      cout << "only numbers are allowed" << endl;
      exit(0);
    }
    cin.ignore();

    int status = signUpValidity();//it will verify wether the account is already created or not.
    if(status == 0){
      exit(0);
    }
    else{
      
      fstream sfile("ID_" + userName + ".txt", ios::out);

      if(!sfile.is_open()){
        cerr << "file processing | status : unsucessful.";
      }
      else{
        cout << "wait we are processing your data:";
      }

      sfile << password;
      sfile << endl;

      sfile << userName;
      cout << endl;

      cout << "Procceed Successfully";
      sfile.close();//file closed
    }
    cout << endl;
    cout << "WELCOME " << userName << endl;
    bankFacilities();

  }

  //to check wether the account is already created or not.
  int signUpValidity(){
    fstream vfile("ID_" + userName + ".txt", ios::in);
    if(vfile.is_open()){
      cerr << "already have an account : try login to your account";
      vfile.close();
      return 0;
    }
    else{
      return 1;
    }
  }

  void login(){
    cout << "Login here..." << endl;
    cout << "Enter Your Full Name: ";

    cin.ignore();
    getline(cin, userName);

    cout << "Password: ";
    cin >> password;

    try{
      if(cin.fail()){
        throw invalid_argument("Invalid Password : ");
      }
    }
    catch(invalid_argument& e){
      cout << "Only Numbers are Allowed.";
      exit(0);
    }

    int status = loginValidity();

    if(status == 0){
      exit(0);
    }
    else{
      cout << "WELCOME " << userName << endl;
      bankFacilities();
    }
  }
  //login verification method
  int loginValidity(){
    fstream lfile("ID_" + userName + ".txt", ios::in);
    if(!lfile.is_open()){
      cerr << "acoutn doesn't exist : try signUp";
      return 0;
    }else{
      string pass;
      int pas;
      getline(lfile, pass);
      try{
        pas = stoi(pass);
      }
      catch(...){
        cout << "Password Conversion Error";
        exit(0);
      }

      if(pas == password){
        lfile.close();
        return 1;
      }
      else{
        cerr << "Password Not Matched";
        return 0;
      }
    }
  }

  ~accountLoginSignUp(){
    cout << endl;
    cout << "Memory Successfully Freed By Destructor";
  }

};

// ---------------------------------------------------------------------------------------------------------------------------
int main(){
  cout<<"**************************** BANKING PROGRAM ****************************";
  accountLoginSignUp obj;
  return 0;
}
