#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	double loanAmount, annIntRate,annIntRatePerc;
	int years,adprinc;

	cout << "Enter loan amount  (0-9999999), for example 300000.90: ";
	cin >> loanAmount;
	while (loanAmount < 0 || loanAmount>9999999)
	{
		cout << "Error: Input out of range. \n" << "Enter loan amount  (0-9999999), for example 300000.90: ";
		cin >> loanAmount;
	}

	cout << "Enter annual interest rate (0-30), for example 4.25 meaning 4.35%: ";
	cin >> annIntRate;
	while (annIntRate < 0 || annIntRate>30)
	{
		cout << "Error: Input out of range. \n" << "Enter annual interest rate (0-30), for example 4.25 meaning 4.35%: ";
		cin >> annIntRate;
	}
	annIntRatePerc = annIntRate / 100;

	cout << "Enter number of years as integer (1-99), for example 30: ";
	cin >> years;
	while (years < 1 || years>99)
	{
		cout<< "Error: Input out of range. \n" << "Enter number of years as integer (1-99), for example 30: ";
		cin >> years;
	}

	cout << "Enter additional principle per month (0-9999999), for example 200: ";
	cin >> adprinc;
	while (adprinc < 0 || adprinc>9999999)
	{
		cout<< "Error: Input out of range. \n" << "Enter additional principle per month (0-9999999), for example 200: ";
		cin >> adprinc;
	}

	double actualPay;
	double monthlyIntRate;
	double monthlyPay;

	if (annIntRate == 0)
	{
		monthlyPay = loanAmount / (years * 12);
		monthlyIntRate = 0;
		actualPay = monthlyPay + adprinc;

	}

	else
	{
		monthlyIntRate = annIntRatePerc / 12;
		monthlyPay = (loanAmount * annIntRatePerc / 12) / (1 - 1 / pow(1 + annIntRatePerc / 12, years * 12));
		actualPay = monthlyPay + adprinc;
	}

	
	string userFile;

	cout << "Send the mortgage amortization table to a file. Enter name of file: ";
	cin >> userFile;

	ofstream file(userFile);

	file << "\t\tMortgage Amortization Table \n\n";
	file << "Amount:                \t" << "$" << setprecision(2) << fixed << showpoint << loanAmount << "\n";
	file << "Interest Rate:         \t" << setprecision(4) << showpoint << annIntRate << "%\n";
	file << "Term (Years):          \t" << setprecision(2) << fixed << years << "\n";
	file << "Monthly Payment:       \t" << "$" << setprecision(2) << fixed << monthlyPay << "\n";
	file << "Additional Principal:  \t" << "$" << setprecision(2) << fixed << adprinc << "\n";
	file << "Actual Payment:        \t" << "$" << setprecision(2) << fixed << actualPay << "\n\n";


	int months = years * 12;

	file << "\tPrincipal\t" << "Interest\t" << "Balance\n\n";

	double principal,interest;
	double balance=loanAmount;


	for (int i = 1; i < months && balance>0; i++)
	{
		
		interest = balance * monthlyIntRate;
		principal = actualPay - interest;
		balance = balance - principal;

		if (balance < 0)
			balance = 0;
		file << i << "\t" << principal << "\t\t" << interest << "\t\t" << balance << endl;			
	}

	file.close();

	system("pause");

	return 0;

}



