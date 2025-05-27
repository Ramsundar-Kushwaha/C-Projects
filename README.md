# C-Projects

```markdown
# Banking Program - Console Application

## Overview
This project is a **C++ console-based banking application** that provides basic financial functionalities such as depositing funds, withdrawing money, and checking account balance. The program incorporates **exception handling** to ensure reliability and prevent invalid transactions.

## Features
- Secure deposit functionality with input validation
- Balance inquiry to display current account funds
- Withdrawal processing with error handling
- Console-based interactive user interface
- Exception handling to manage invalid inputs

## Installation & Usage

### Prerequisites
Ensure that you have the following:
- A **C++ compiler** (GCC, MSVC, Clang, etc.)
- A command-line interface (**Terminal / Command Prompt**)

### Steps to Run the Program
1. **Clone the repository**:
   ```sh
   git clone https://github.com/Ramsundar-Kushwaha/Banking-Program.git
   ```
2. **Navigate to the project directory**:
   ```sh
   cd Banking-Program
   ```
3. **Compile the program**:
   ```sh
   g++ banking_program.cpp -o banking_program
   ```
4. **Run the application**:
   ```sh
   ./banking_program
   ```

## Program Workflow
Upon execution, the user is presented with the following options:
1. **Deposit Balance**
2. **Show Balance**
3. **Withdraw Balance**
4. **Exit**

Each transaction is validated through exception handling mechanisms to ensure security and accuracy.

## Code Structure

### `Bank` Class
The **`Bank`** class encapsulates all banking functionalities with the following key methods:
- `depositeBalance()`: Allows users to deposit funds with validation.
- `showBalance()`: Displays the current balance.
- `drawBalance()`: Facilitates withdrawals while enforcing transaction limits.
- `bankMenu()`: Provides a structured menu for user interaction.
- `performActions(int action)`: Executes the selected banking operation.

## Exception Handling
To enhance stability and prevent invalid transactions, the program implements error handling:
- **Invalid input protection:** Prevents non-numeric or incorrect data types.
- **Transaction limits:** Ensures withdrawals do not exceed available balance.
- **Validation checks:** Enforces that deposits must be greater than zero.

## License
This project is licensed under the **MIT License**.

## Author
- **Ramsundar Kumar Kushwaha**