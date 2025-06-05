//C++ - Project - 01 - Banking Program - Console Application - for study purpose only
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<limits>//for using cin.ignore(numeric_limits<stramsize>::max(), '\n')
#include<cstdlib>//for using clearScreen();

using namespace std;

//for clearing screen
void clearScreen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

//for storing variables only which is used by many classes
class Variables{
  protected:
  double deposit = 0;
  double withDraw;
  string userName;
  int password;
};

// ---------------------------------------------------------------------------------------------------------------------------
//Banking System - Class
class Bank:public Variables{
  public:
    //method for depositing balance
    void depositBalance(){

      double tempMoneyHolder;
      
      cout << "Enter the balance to be deposit:\t";
      cin >> tempMoneyHolder;

      //Exception handling or Error handling
      try{
        if(cin.fail()){
          cin.clear(); //clear error flag
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
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
        cout << "[Invalid Deposit\t\t"<<"status:\tUnsuccessful]";
        cout<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------"<<endl;
        return;
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
            deposit = stod(line);
          }
          catch(const exception& e){
            cerr << "Invalid Number Format in file" << endl;
            return;
          }
        }
      }
      
      dload.close();
      
      deposit = deposit + tempMoneyHolder;
      
      cout<<endl;
      cout<<"------------------------------deposit Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Deposited Amount:\t"<<tempMoneyHolder<<"$\t\t";
      cout<<"Status:\t"<<"Successful.]"<<endl;
      cout<<endl;
      cout<<"----------------------------------------------------------------------------"<<endl;

      //file handling -- writting to file
      fstream dfin("D_" + userName + ".txt", ios::out);
      if(!dfin.is_open()){
        cerr << "File Processing | status: Failed" << endl;
      }
      else{
        dfin << to_string(deposit);
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
        hfin << "[Deposited Amount:\t"<< to_string(tempMoneyHolder) << "$\t\t";
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
        cerr << "File Processing | status: Unsuccessful" << endl;
      }
      else{
        string line;
        getline(dfr, line);
        try{
          deposit = stod(line);
        }
        catch(const exception& e){
          cerr << "Invalid Number Format in file" << endl;
          return;
        }

      }
      dfr.close();

      cout<<endl;
      cout<<"------------------------------Current Balance------------------------------"<<endl;
      cout<<endl;
      cout<<"[Current Balance:\t"<<deposit<<"$]"<<endl;
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
        hfr << "[Current Balance:\t"<<to_string(deposit)<<"$]" << endl;
        hfr << endl;
        hfr << "----------------------------------------------------------------------------" << endl;
        hfr << endl;
      }

      hfr.close();
    }


// ---------------------------------------------------------------------------------------------------------------------------
    //method for balance withDraw
    void drawBalance(){

      if(deposit == 0){

        fstream lodB("D_" + userName + ".txt", ios::in);

        if(!lodB.is_open()){
          cerr << "unable to load deposit balance";
          return;
        }
        else{

          string line;
          int dep;
          getline(lodB, line);

          if(!line.empty()){
            try{
              dep = stod(line);
            }
            catch(...){
              cout << "balance conversion error";
              return;
            }

            deposit += dep;
            lodB.close();
          }
        }
      }
      
      cout<<"Enter Amount($):\t";
      cin >> withDraw;

      //Exception handling or Error handling
      try{
        if(cin.fail()){
          cin.clear(); // clear error fla
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
          throw invalid_argument("Invalid input");
        }
        else if( withDraw > deposit){
          throw out_of_range(" out of range");
        }
        else if(withDraw <= 0){
          throw logic_error("Invalid amount");
        }
      }

      catch(const invalid_argument& e){
        cout << "Invalid Input";
        return;
      }
      catch(const out_of_range& e){
        cout<<endl;
        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Insufficient Balance.]" << e.what();
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        return;
      }
      catch(const logic_error& e){
        cout<<endl;
        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Invalid Input.]" << e.what();
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        return;
      }


      if(withDraw <= deposit && withDraw > 0){

        deposit = deposit - withDraw;

        cout<<"---------------------------------Withdraw---------------------------------"<<endl;
        cout<<endl;
        cout<<"[Withdraw Amount:\t"<<withDraw<<"$\t\t";
        cout<<"Status:\t"<<"Successful.]"<<endl;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

        //deposit file handling
        fstream dfile("D_" + userName + ".txt", ios::out);
        if(!dfile.is_open()){
          cerr << "File Processing | sUatus : unsuccessful";
        }
        else{
          dfile << to_string(deposit);
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
          hfile << "[Withdraw Amount:\t" << to_string(withDraw) << "$\t\t";
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
          cin.clear(); //clear error flag
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
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
        clearScreen();
        depositBalance();
        cout<<endl;
        return 1;

      }

      if(action == 2){
        clearScreen();
        showBalance();
        cout<<endl;
        return 1;
        
      }

      if(action == 3){
        clearScreen();
        drawBalance();
        cout<<endl;
        return 1;

      }

      else{
        clearScreen();
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
  
  while (true){
    int action = bankMenu();
    int result = performActions(action);
    if(result == 0)
      break;
  }
  cout << "Exit Done" << endl;
}
};

//---------------------------------------------------------------------------------------------------------------------
//signUp and Login feature is under construction now
class accountLoginSignup:public Bank{
  public:
  void LoginSignup(){
    int choice;
    cout << endl << endl << endl;
    cout << "             Welcome User:       " << endl;
    cout <<"----------------------------------------"<< endl;
    cout <<"|   1. Login" << "      |     " << "   2. signUp   |" << endl;
    cout <<"----------------------------------------"<< endl << endl;
    cout << "Enter Your Choice: ";
    cin >> choice;

    try{
      if(cin.fail()){
        cin.clear(); //clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
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
      return;
    }
    catch(...){
      cout << "Number Should Be Choosen either 1 or 2";
      return;
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
        cin.clear(); //clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
        throw invalid_argument("invalid input : ");
      }
    }
    catch(invalid_argument& e){
      cout << "only numbers are allowed" << endl;
      return;
    }
    cin.ignore();

    int status = signupValidity();//it will verify wether the account is already created or not.
    if(status == 0){
      return;
    }
    else{
      
      fstream sfile("ID_" + userName + ".txt", ios::out);

      if(!sfile.is_open()){
        cerr << "file processing | status : Unsuccessful.";
      }
      else{
        cout << "wait we are processing your data:";
      }

      sfile << to_string(password);
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
  int signupValidity(){
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
        cin.clear(); //clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer upto maximum character and stoped when new line character found
        throw invalid_argument("Invalid Password : ");
      }
    }
    catch(invalid_argument& e){
      cout << "Only Numbers are Allowed.";
      return;
    }

    int status = loginValidity();

    if(status == 0){
      return;
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
      cerr << "account doesn't exist : try signUp";
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
        return 0;
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

};

// ---------------------------------------------------------------------------------------------------------------------------
int main(){
  cout<<"**************************** BANKING PROGRAM ****************************";
  accountLoginSignup obj;
  obj.LoginSignup();
  return 0;
}
