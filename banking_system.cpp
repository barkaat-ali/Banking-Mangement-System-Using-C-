// first we are adding the header files
using namespace std;
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
//making the char array constant
const int SIZE = 100;

//Structure that will be used for making records
struct Account
{

	int accountNO = 0;
	//using the char array instead of string
	//because string class objects contain implicit pointers

	char name[SIZE] = "";
	char city[SIZE] = "";
	char state[SIZE] = "";
	char zip[SIZE] = "";
	char telephoneNo[SIZE] = "";
	double accountBalance = 0;
	int day = 0;
	int month = 0;
	int year = 0;
};

//adding prototypes
void Enter_record(string);

void SearchAndDispalay_record(string);

void SearchAndDelete_record(string);

void SearchAndChange_record(string);

void ViewCustomerList(string);

void BalanceInquiry(string);

void DepositAmmount(string);

void WithdrawAmount(string);

void TransferAmount(string);

//Only the menu and repetition of program will be done in main
//Along with giving a string as input to other functions
int main()
{
	//storing the name of data file in string 
	//taking binary data file beacuse txt file store data in
	//ASCII text and problem occur during operation

	string user_data = "dafile.dat";
	Account user_account;
	int option;

	do {
		cout << "\t\t\t*********WELCOME TO ABN BANK ACCOUNT**********\n";

		cout << " ==============================================================================================================\n";

		cout << "|| For entering new record in a file press 1           ||";

		cout << " For search and display existing record press 2      ||\n";

		cout << "||_____________________________________________________||_____________________________________________________||\n";

		cout << "|| For search and delete existing record press 3       ||";

		cout << " For search and change the existing record press 4   ||\n";

		cout << "||_____________________________________________________||_____________________________________________________||\n";

		cout << "|| To view the customer list press 5                   ||";

		cout << " For balance inquiry press 6                         ||\n";

		cout << "||_____________________________________________________||_____________________________________________________||\n";

		cout << "|| To deposit ammount in account press 7               ||";

		cout << " To withdraw amount press 8                          ||\n";

		cout << "||_____________________________________________________||_____________________________________________________||\n";

		cout << "|| For tranferring amount to the other account press 9 ||";

		cout << " To exit the system press 10                         ||\n";

		cout << " ==============================================================================================================\n";

		//The input taken by the user from the given menu

		cin >> option;
		while (option < 1 || option>10)
		{
			cout << "you Enter an invalid option enter the option again\n";
			cin >> option;

		}
		switch (option)
		{
		case 1:
			system("CLS");
			Enter_record(user_data);
			system("CLS");

			break;

		case 2:
			system("CLS");
			SearchAndDispalay_record(user_data);
			system("CLS");
			break;
		case 3:
			system("CLS");
			SearchAndDelete_record(user_data);
			system("CLS");
			break;

		case 4:
			system("CLS");
			SearchAndChange_record(user_data);
			system("CLS");
			break;
		case 5:
			system("CLS");
			ViewCustomerList(user_data);
			system("CLS");
			break;
		case 6:
			system("CLS");
			BalanceInquiry(user_data);
			system("CLS");
			break;
		case 7:
			system("CLS");
			DepositAmmount(user_data);
			system("CLS");
			break;
		case 8:
			system("CLS");
			WithdrawAmount(user_data);
			system("CLS");
			break;
		case 9:
			system("CLS");
			TransferAmount(user_data);
			system("CLS");
			break;
		}
	} while (option != 10);




}
//Function for entering new record in the system
void Enter_record(string user_data)
{
	//declaring fstream object
	fstream userdata;
	//opening file in fstream object
	userdata.open(user_data, ios::out | ios::app | ios::binary);
	//using structre as data type for user account
	Account user_account;
	//getting number of bytes
	userdata.seekg(0, ios::end);
	//giving every account number a unique name by using number total number of bytes of file/bytes of structure
	user_account.accountNO = userdata.tellg() / sizeof(Account);
	cout << "You have account number is " << user_account.accountNO << endl;
	cout << "Enter your name\n";
	//cin.ignore to eradicate file buffer data
	cin.ignore();
	cin.getline(user_account.name, SIZE);
	cout << "Enter your city\n";
	cin.getline(user_account.city, SIZE);
	cout << "Enter your state\n";
	cin.getline(user_account.state, SIZE);
	cout << "Enter your zip\n";
	cin.getline(user_account.zip, SIZE);
	cout << "Enter your telephone number\n";
	cin.getline(user_account.telephoneNo, SIZE);
	//account balance validation
	cout << "Enter your account balance\n";
	while (!(cin >> user_account.accountBalance))
	{
		cout << "Enter numeric data only\n";
		cin.clear();
		cin.ignore(99, '\n');

	}
	while (user_account.accountBalance < 0)
	{
		cout << "Invalid Input. Enter again \n";
		cin >> user_account.accountBalance;
	}
	cout << "Enter your last payment day\n";
	cin >> user_account.day;
	while (user_account.day > 31 || user_account.day <= 0)
	{
		cout << "Invalid Input . Enter again ";
		cin >> user_account.day;
	}
	cout << "Enter your last payment month\n";
	cin >> user_account.month;
	while (user_account.month > 12 || user_account.month <= 0)
	{
		cout << "Invalid Input . Enter again ";
		cin >> user_account.month;
	}
	cout << "Enter your last payment year\n";
	cin >> user_account.year;
	userdata.write(reinterpret_cast<char*>(&user_account), sizeof(user_account));

	userdata.close();

	system("pause");
}



//Function for performing search and display of information of a specific record
void SearchAndDispalay_record(string user_data)
{

	fstream userdata;
	//opening file in fstream object
	userdata.open(user_data, ios::in | ios::binary);
	Account user_account;

	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;
	//going to particular record by multiplying size of structre with account number
	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	//reding data from binary file  and storing in structre
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		cout << "Press Enter to go to the main menu\n";
		userdata.close();
		system("pause");
		return;
	}
	else
	{
		cout << "Your name\n";
		cout << user_account.name << endl;
		cout << "Your city\n";
		cout << user_account.city << endl;
		cout << "Your state\n";
		cout << user_account.state << endl;
		cout << "Your zip\n";
		cout << user_account.zip << endl;
		cout << "Your telephone number\n";
		cout << user_account.telephoneNo << endl;
		cout << "Your account balance\n";
		cout << fixed << setprecision(2) << "Rs" << user_account.accountBalance << endl;
		cout << "Your last payment\n";
		cout << user_account.day << "\\" << user_account.month << "\\" << user_account.year << endl;
		system("pause");
		userdata.close();
		system("cls");
	}

}

//Function for deletion of a record
void SearchAndDelete_record(string user_data)
{

	fstream userdata;
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;

	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;
	//going to particular record by multiplying size of structre with account number
	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	//reading data from file and storing in structure
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << " Sorry there is no account currently on this account number\n";

		system("pause");
		userdata.close();
		return;
	}
	else
	{

		user_account = { '\0',"","","","","",0.0,0 };
		//going to particular byte to write the structure
		userdata.seekp(sizeof(user_account) * account_number, ios::beg);
		//writting struture
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(Account));
		system("pause");
		userdata.close();
	}
}

//Function for making changes in an existing record
void SearchAndChange_record(string user_data)
{
	fstream userdata;
	//opening file in fstream object

	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;

	int account_number;
	cout << "Enter the record no which you want to change\n";
	cin >> account_number;
	userdata.seekg((sizeof(user_account) * account_number), ios::beg);
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		userdata.close();
		system("pause");

	}
	else
	{

		cout << "Your current name\n";
		cout << user_account.name << endl;
		cout << "Your current city\n";
		cout << user_account.city << endl;
		cout << "Your current state\n";
		cout << user_account.state << endl;
		cout << "Your current zip\n";
		cout << setw(4) << user_account.zip << endl;
		cout << "Your current telephone number\n";
		cout << setw(11) << user_account.telephoneNo << endl;
		cout << "Your current account balance is Rs\n";
		cout << fixed << setprecision(2) << user_account.accountBalance << endl;
		cout << "Your current last payment\n";
		cout << fixed << user_account.day << "\\" << user_account.month << "\\" << setw(4) << user_account.year << endl;


		cout << "Enter your name\n";
		cin.ignore();
		cin.getline(user_account.name, SIZE);

		cout << "Enter your city\n";
		cin.ignore();
		cin.getline(user_account.city, SIZE);

		cout << "Enter your state\n";
		cin.ignore();
		cin.getline(user_account.state, SIZE);

		cout << "Enter your zip\n";
		cin.ignore();
		cin.getline(user_account.zip, SIZE);

		cout << "Enter your telephone number\n";
		cin.ignore();
		cin.getline(user_account.telephoneNo, SIZE);

		cout << "Enter your account balance in Rs\n";
		while (!(cin >> user_account.accountBalance))
		{
			cout << "Enter numeric data only\n";
			cin.clear();
			cin.ignore(99, '\n');

		}
		while (user_account.accountBalance < 0)
		{
			cout << "Invalid Input. Enter again \n";
			cin >> user_account.accountBalance;
		}
		cout << "Enter your last payment day\n";
		cin.ignore();
		cin >> user_account.day;
		while (user_account.day > 30 || user_account.day < 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.day;
		}
		cout << "Enter your last payment month\n";
		cin.ignore();
		cin >> user_account.month;
		while (user_account.month > 12 || user_account.month < 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.month;
		}
		cout << "Enter your last payment year\n";
		cin.ignore();
		cin >> user_account.year;

		userdata.seekp(sizeof(user_account) * account_number, ios::beg);
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(user_account));
	}
	userdata.close();
	system("pause");


}

//Function for veiwing list of all customers and their accounts
void ViewCustomerList(string user_data)
{
	fstream userdata;
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;


	userdata.seekg(0, ios::beg);
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(user_account));
	//For diplaying each record in file
	if (userdata.fail())
	{
		cout << "There are no records\n";
		userdata.close();
	}
	else
	{
		cout << "Account number     Name                 Balance\n";
		cout << "---------------------------------------------\n";

		while (!userdata.eof())
		{
			cout << setw(4);
			cout << user_account.accountNO;
			cout << setw(25);
			cout << user_account.name;
			cout << setw(19);
			cout << fixed << setprecision(2) << "Rs " << user_account.accountBalance << endl;
			userdata.read(reinterpret_cast<char*>(&user_account), sizeof(user_account));
		}
	}
	userdata.close();
	system("pause");

}

//Function for inquiring balance of a specific record
void BalanceInquiry(string user_data)
{

	fstream userdata;
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;

	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;
	//getting record from particular byte in file
	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		system("pause");
		userdata.close();
		return;
	}
	else
	{

		cout << "The account number " << account_number << " has\n";
		cout << user_account.accountBalance << " Rs balance\n";

	}
	userdata.close();
	system("pause");

}

//Function for depositing balance to a certain record
void DepositAmmount(string user_data)
{

	fstream userdata;
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;

	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;
	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		cout << "Press Enter to go to the main menu\n";
		system("pause");
		userdata.close();
		return;
	}
	else
	{
		double deposit_amount;
		cout << "Your current ammount is = Rs " << user_account.accountBalance << endl;
		cout << "Enter the amount you want to deposit\n";
		cin >> deposit_amount;
		//deposit ammount not be negative
		while (deposit_amount < 0)
		{
			cout << "Enter the amount again\n";
			cin >> deposit_amount;
		}
		//adding value to account balance
		user_account.accountBalance += deposit_amount;
		cout << "Enter your last payment day\n";

		cin >> user_account.day;
		while (user_account.day > 31 || user_account.day <= 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.day;
		}
		cout << "Enter your last payment month\n";
		cin >> user_account.month;
		while (user_account.month > 12 || user_account.month <= 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.month;
		}
		cout << "Enter your last payment year\n";
		cin >> user_account.year;
		//going to particular byte to put data
		userdata.seekp(sizeof(user_account) * account_number, ios::beg);
		//writing data to file from structure
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(Account));
		cout << "Your new account balance is Rs " << user_account.accountBalance << endl;
	}
	userdata.close();
	system("pause");

}

//Function for withdrawing money from a specific account
void WithdrawAmount(string user_data)
{
	fstream userdata;
	//opening file in fstream object
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;


	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;
	//getting value from particular byte
	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	//reading value and storing in structure

	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		cout << "press Enter to go to the main menu\n";
		system("pause");
		userdata.close();
		return;
	}
	else
	{
		cout << "your current balance is=" << user_account.accountBalance << endl;
		double withdraw_amount;
		cout << "Enter the withdraw ammount\n";
		cin >> withdraw_amount;
		//withdraw amount not greater than balance
		while (withdraw_amount > user_account.accountBalance)
		{
			cout << "Enter the value again this value is greater than your account balance\n";
			cin >> withdraw_amount;
		}
		//deducting balance of withdraw
		user_account.accountBalance -= withdraw_amount;
		cout << "Enter your last payment day\n";
		cin >> user_account.day;
		while (user_account.day > 31 || user_account.day <= 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.day;
		}
		cout << "Enter your last payment month\n";
		cin >> user_account.month;
		while (user_account.month > 12 || user_account.month <= 0)
		{
			cout << "Invalid Input . Enter again ";
			cin >> user_account.month;
		}
		cout << "Enter your last payment year\n";
		cin >> user_account.year;
		userdata.seekp(sizeof(user_account) * account_number, ios::beg);
		//putting new data to file from structure
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(Account));
		cout << "Now the balance in your account is Rs " << user_account.accountBalance << endl;
	}
	userdata.close();
	system("pause");

}

//Function for transferring balance from one account to another
void TransferAmount(string user_data)
{

	fstream userdata;
	userdata.open(user_data, ios::in | ios::out | ios::binary);
	Account user_account;


	int account_number;
	cout << "Enter the account number for which you want the details\n";
	cin >> account_number;

	//getting data from particular file location

	userdata.seekg(sizeof(user_account) * account_number, ios::beg);
	//reading data from file and storing it in structure
	userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
	//If the account does not exist
	if (userdata.eof() || user_account.name[0] == '\0')
	{
		//If no such account is found
		cout << "Sorry there is no account currently on this account number\n";
		cout << "press Enter to go to the main menu\n";
		system("pause");
		return;

	}
	else
	{
		cout << "Your current ammount is = Rs " << user_account.accountBalance << endl;
		double transfer_amount;
		cout << "Enter the  ammount you want to transfer\n";
		cin >> transfer_amount;
		while (transfer_amount > user_account.accountBalance)
		{
			//If the value entered is greater than the balance in account
			cout << "Enter the value again this value is greater than your account balance\n";
			cin >> transfer_amount;
		}

		//deducting from account balance

		user_account.accountBalance -= transfer_amount;
		//putting to the account number loction by multiplying acount number with size of structure
		userdata.seekp(sizeof(user_account) * account_number, ios::beg);
		//writting from structure to file
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(Account));
		cout << "Enter the account in which you want to transfer\n";
		int account2;
		cin >> account2;
		userdata.seekg(sizeof(user_account) * account2, ios::beg);
		userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
		while (userdata.eof() || user_account.name[0] == '\0')
		{
			//If no such account is found
			cout << "No account found enter the value again\n";
			cin >> account2;
		}
		//adding value in which the balance is transfer
		user_account.accountBalance += transfer_amount;
		//seeking putting location 
		userdata.seekp(sizeof(user_account) * account2, ios::beg);
		//writing data to file from structure
		userdata.write(reinterpret_cast<char*>(&user_account), sizeof(Account));
		cout << "Now account no " << account2 << " has amount = Rs " << user_account.accountBalance << endl;

		//again getting to tell the balance of deducting account
		userdata.seekg(sizeof(user_account) * account_number, ios::beg);
		userdata.read(reinterpret_cast<char*>(&user_account), sizeof(Account));
		cout << "Now you have the ammount = Rs " << user_account.accountBalance << " in your account\n";
		system("pause");
		userdata.close();
	}
}

