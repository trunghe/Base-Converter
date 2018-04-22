/*
 * main.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: T
 */

#include <cstdlib>	/*for fpurge*/
#include <stdio.h>	/*for printf, scanf*/
#include <string>	/*for string io*/
#include <iostream>	/*for cout, cin*/
#include <istream>	/*for cin.clear, cin.ignore*/
#include <limits>	/*for numeric_limits<streamsize>::max()*/
#include <algorithm>/*for reverse*/
#include <vector>	/*for vector*/
#include <climits>	/*for LONG_MIN, LONG_MAX*/
/*WARNING: scanf didn't work correctly when this program was written*/

using namespace std;

namespace Print {
	/* Namespace: Print
	 *
	 * Purpose: groups functions to display messages together
	 * */
	void Intro() {
		/* Function: Intro
		 *
		 * Purpose: displays names of program and author
		 * */
		printf( "Base Conversion Program\n"
				"\n"
				"by TrungVT HE130284\n"
				"\n");
	}
	void Menu() {
		/* Function: Menu
		 *
		 * Purpose: displays instructions and options for user input
		 * */
		printf( "This program lets you input a number in 1 of 4 bases and\n"
				"gives you the corresponding numbers in the other 3.\n"
				"\n"
				"Please choose 1 of the following options:\n"
				"0) Convert a BINARY (base 2) number\n"
				"1) Convert an OCTAL (base 8) number\n"
				"2) Convert a HEXADECIMAL (base 16) number\n"
				"3) Convert a DECIMAL (base 10) number\n"
				"\n"
				"Enter 0, 1, 2, or 3 to proceed. No extra character allowed.\n");
	}
	void Error() {
		/* Function: Error
		 *
		 * Purpose: displays generic error-input notification and
		 * 			prompts user to re-enter
		 * */
		printf( "Error input. Please try again.\n");
	}
	void Range(long int MIN, long int MAX) {
		/* Function: Range
		 *
		 * Purpose: displays the allowed range and prompts user to re-enter
		 * */
		printf( "Please enter a value in range from %ld to %ld.\n",
				MIN, MAX);
	}
	void Choice(string baseName, int baseNum) {
		printf( "Please enter your %s number (base %d): ",
				baseName.c_str(), baseNum);
	}
	void Result(string baseName) {
		printf( "%s: ", baseName.c_str());
	}
}; // end of namespace Print

long int InputInt(long int MIN, long int MAX) {
	//	/* Function: InputInt
	//	 *
	//	 * Purpose: takes input number from console, check and return value iff
	//	 * 			input is valid (no error, correct characters, in range);
	//	 * 			else prompt user to re-enter
	//	 * Calls: PrintError, PrintRange
	//	 * */

	long int num;		// input number
	int check;		// scanf 2 variables must return value 2
	char lastChar;	// last character must be '\n'
	do {
		fpurge(stdin);
		check = scanf("%ld%c", &num, &lastChar);
		if (lastChar != '\n' || check != 2)
			Print::Error();
		else if (num < MIN || num > MAX)
			Print::Range(MIN, MAX);
		else
			return num;
	} while (1);
} // end of long int InputInt(long int MIN, long int MAX)

string InputStr(int base) {
	//	/* Function: InputStr
	//	 *
	//	 * Purpose: takes input string from console, check and return string iff
	//	 * 			input is valid (no error, correct characters, correct digits);
	//	 * 			else prompt user to re-enter
	//	 * Calls: PrintError, PrintRange
	//	 * */

	string str;	// input string
	char temp;
	bool notValid;	// flag if invalid characters found
	int firstDigitPos;	// if negative, start checking from str[1]
	do {				//...else start from str[0]
		str = "";
		notValid = false;
		firstDigitPos = 0;
		fpurge(stdin);
		temp = getchar();
		while (temp != '\n') {
			if (isalpha(temp))
				temp = toupper(temp);
			str += temp;
			temp = getchar();
		}
		if (str[0] == '-')	// if minus sign found start from str[1]
			firstDigitPos = 1;
		if (base == 2 || base == 8) {	// if bases 2 and 8
			for (unsigned int i = firstDigitPos; i < str.length(); i++) {
				if (str[i] < '0' || str[i] > ('0' + base - 1)) {
					notValid = true;   // digits above '7' are skipped
					break;
				}
			}
		}
		else {
			for (unsigned int i = firstDigitPos; i < str.length(); i++) {
				if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
					str[i] > 'F') {	// ignore digits between '9' and 'A'
					notValid = true;
					break;
				}
			}
		}
		if (notValid)
			Print::Error();
		else
			break;
	} while (1);
	return str;
} // end of string InputStr(int base)

string ConvertStr(long int decimal, int base) {
	//	/* Function: ConvertStr
	//	 *
	//	 * Purpose: takes an int and output base, process and return string of
	//	 * 			corresponding number in said base, accepts negatives
	//	 *
	//	 * Calls: reverse (method of class string)
	//	 * */

	string str;	// output string
	bool isNegative = false;	// flag to add '-' if negative
	char digit = '0';
	if (decimal == 0) {
		str += '0';
		return str;
	}
	if (decimal < 0) {
		isNegative = true;
		decimal = abs(decimal);	// can only process positive number
	}
	if (base == 2 || base == 8) {
		while (decimal > 0) {
			digit = (decimal % base) + '0';
			str += digit;
			decimal /= base;
		}
	}
	else {
		int remainder;
		while (decimal > 0) {
			remainder = decimal % base;
			if (remainder < 10)
				digit = (decimal % base) + '0';
			else
				digit = (decimal % base) + 'A' - 10;
			str += digit;
			decimal /= base;
		}
	}
	if (isNegative)
		str += '-';
	reverse(str.begin(), str.end());
	return str;
} // end of string ConvertStr(long int decimal, int base)

/********************************************************************************/
int main() {
	int baseNum[4] = {2, 8, 16, 10}, choice;
	vector <string> baseName = {"BINARY", "OCTAL", "HEXADECIMAL", "DECIMAL"};
	string str, bin, oct, hex;
	long int dec;

	Print::Intro();
	Print::Menu();
	choice = InputInt(0, 3);
	Print::Choice(baseName[choice], baseNum[choice]);

	if (choice < 3) {
		str = InputStr(baseNum[choice]);
		dec = strtol(str.c_str(), NULL, baseNum[choice]);
	}
	else {
		dec = InputInt(LONG_MIN, LONG_MAX);
	}
	cout << "   DECIMAL  : " << dec << endl;
	bin = ConvertStr(dec, 2);
	cout << "   BINARY   : " << bin << endl;
	oct = ConvertStr(dec, 8);
	cout << "   OCTAL    : " << oct << endl;
	hex = ConvertStr(dec, 16);
	cout << "HEXADECIMAL : " << hex << endl;
	cin.get();
	return 0;
} // end of int main()
/********************************************************************************/
