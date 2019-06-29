// Assignment3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"pch.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

void romanAssignment();
void RomantoBase10();
void RomanAddition();
void RemoveSubtractives(string& roman);
void AddSubtractives(string& roman);
void Base10ToRoman();
int decode(char t);
void encodeAssignment();
void sortString(string& roman);
bool replace(std::string& str, const std::string& from, const std::string& to);

using namespace std;

class Encrypt {

private:
	string original = "";
	string encrypted = "";
	string prepared = "";

public:
	void display() {
		cout << "\n\nThe encrypted data: " << encrypted;
		cout << "\n\nThe original data: " << original;

	}

	void display_encryption(string key) {

		cout << "\n\nOriginal Text: " << this->original;
		cout << "\nKey: " << key;
		cout << "\nPrepared Text: " << this->prepared;
		cout << "\nEncrypted Text: " << this->encrypted;
	}

	void display_decryption(string key, string decrypted) {
		cout << "\n\nKey: " << key;
		cout << "\nEncrypted Text: " << this->encrypted;
		cout << "\nOriginal Text: " << decrypted;
	}

	void set_original(string original) {
		this->original = original;
	}

	void set_encrypted(string encrypted) {
		this->encrypted = encrypted;
	}

	void set_prepared(string prepared) {
		this->prepared = prepared;
	}

	bool is_origin_exist() {
		return this->original.length() > 0;
	}

	bool is_encrypted_exist() {
		return this->encrypted.length() > 0;
	}


	void XOR_encrypt(char key) {
		this->encrypted = "";

		this->prepared = this->original;

		for (unsigned int i = 0; i < prepared.length(); i++) {
			if (this->prepared[i] != ' ')
				this->encrypted += string(1, (tolower(this->prepared[i]) ^ key));
			else
				this->encrypted += string(" ");
		}
		string s(1, key);
		display_encryption(s);
	}

	string XOR_decrypt(char key) {
		string result = "";

		for (unsigned int i = 0; i < encrypted.length(); i++) {
			if (this->encrypted[i] != ' ')
				result += string(1, (tolower(this->encrypted[i]) ^ key));
			else
				result += " ";
		}
		string s(1, key);
		display_decryption(s,result);
		return result;
	}

	void Caesar_encrypt(int key) {
		
		this->encrypted = "";

		this->prepared = this->original;

		for (unsigned int i = 0; i < prepared.length(); i++) {
			if (this->prepared[i] != ' ')
				this->encrypted += string(1, (isupper(this->prepared[i]) ? (this->prepared[i] - 'A' + key) % 26 + 'A' : (this->prepared[i] -'a' + key) % 26 + 'a'));
			else
				this->encrypted += string(" ");
		}

		display_encryption(to_string(key));
	}

	string Caesar_decrypt(int key) {
		string result = "";

		for (unsigned int i = 0; i < encrypted.length(); i++) {
			if (this->encrypted[i] != ' ')
				result += string(1, (isupper(this->encrypted[i]) ? (this->encrypted[i] - 'A' + 26 - key) % 26 + 'A' : (this->encrypted[i] - 'a' +26 - key) % 26 + 'a'));
			else
				result += " ";
		}
		display_decryption(to_string(key), result);
		return result;
	}

	void Vigenere_encrypt(string key) {
		this->encrypted = "";

		this->prepared = this->original;
		this->prepared.erase(remove_if(this->prepared.begin(), this->prepared.end(), isspace), this->prepared.end());
		
		transform(this->prepared.begin(), this->prepared.end(), this->prepared.begin(), ::tolower);
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		string concatKey;
		for (unsigned int i = 0; i < prepared.length(); i++)
			concatKey += key[i%key.length()];

		//concatKey = concatKey.substr(0, prepared.length());

		for (unsigned int i = 0; i < prepared.length(); i++) {
			this->encrypted += string(1,((this->prepared[i]) - 'a' + (concatKey[i]) - 'a')%26+'a');
		}

		display_encryption(concatKey);
	}

	string Vigenere_decrypt(string key) {

		string concatKey;
		for (unsigned int i = 0; i < encrypted.length(); i++)
			concatKey += tolower( key[i%key.length()]);


		string result = "";

		for (unsigned int i = 0; i < encrypted.length(); i++) {
			result += string(1, (tolower(this->encrypted[i]) - (concatKey[i]) +26) % 26 + 'a');
		}

		display_decryption(concatKey,result);
		return result;
	}
};

void encription_menu(Encrypt& encrypt);
void decription_menu(Encrypt& encrypt);

int main()
{
	int pick;
	std::cout << "Welcome to the assignment 3, please pick a task to run:";

	do {
		std::cout << "\n1 - Roman";
		std::cout << "\n2 - Encode";
		std::cout << "\n3 - Quit";
		std::cout << "\n Please select the action: ";
		std::cin >> pick;

		switch (pick) {
		case 1:
			romanAssignment();
			break;
		case 2:
			encodeAssignment();
			break;
		case 3:
			break;
		default:
			std::cout << "/nWrong input, please try again";
		}
	} while (pick != 3);

	std::cout << "\nThank you for using the application.";

}


void romanAssignment() {
	int pick;

	cout << "\n\nGratissimum whoever you are!";

	do {
		cout << "\n\nPlease select one of the following: ";
		cout << "\n\n1 - Roman to Base 10";
		cout << "\n2 - Base 10 to Roman";
		cout << "\n3 - Add 2 Roman numbers";
		cout << "\n4 - Exit";
		cout << "\n\nIndicate your selection :";

		cin >> pick;

		switch (pick) {
		case 1:
			RomantoBase10();
			break;
		case 2:
			Base10ToRoman();
			break;
		case 3:
			RomanAddition();
			break;
		case 4:
			break;

		default:
			std::cout << "\nWrong input, please try again";
		}
	} while (pick != 4);

	std::cout << "\nThank you for using the application";

}

void RomantoBase10() {
	string roman;
	int result = 0;

	cout << "\n\nInput the Roman number: ";

	//getline(cin, roman);
	cin >> roman;
	RemoveSubtractives(roman);

	cout << "\nStep1 - removing substractives, the resulting Romanian number is " << roman;

	cout << "\nStep2 - making summation of letters:";

	for (unsigned int i = 0; i < roman.length(); i++) {
		result += decode(roman[i]);
	}

	cout << "\nIn Base 10 this is: " << result;
}


void Base10ToRoman() {
	string result = "";
	int decimal;

	cout << "\n\nInput the base 10 number (< 9999 and > 0): ";
	cin >> decimal;

	cout << "\nStep1, creating value without applying of substraction";

	for (int i = 0; i < decimal / 1000; i++)
		result += "M";

	decimal -= (decimal / 1000) * 1000;

	for (int i = 0; i < decimal / 500; i++)
		result += "D";

	decimal -= (decimal / 500) * 500;

	for (int i = 0; i < decimal / 100; i++)
		result += "C";

	decimal -= (decimal / 100) * 100;


	for (int i = 0; i < decimal / 50; i++)
		result += "L";

	decimal -= (decimal / 50) * 50;

	for (int i = 0; i < decimal / 10; i++)
		result += "X";

	decimal -= (decimal / 10) * 10;


	for (int i = 0; i < decimal / 5; i++)
		result += "V";

	decimal -= (decimal / 5) * 5;


	for (int i = 0; i < decimal; i++)
		result += "I";

	cout << "\nThe Romanian number equivalent is " << result;
	
	cout << "\nStep2, applying substraction";
	AddSubtractives(result);
	cout << "The Roman number is: " << result;
}

void sortString(string& roman) {
	char tmp;

	for (unsigned int i=0;i<roman.length();i++)
		for (unsigned int j = 0; j < i; j++) {
			if (decode(roman[i]) > decode(roman[j]))
			{
				tmp = roman[i];
				roman[i] = roman[j];
				roman[j] = tmp;
			}
		}
}

void AddSubtractives(string& roman) {
	// first reducing unnecessary duplications, It will be used in addition of 2 romans
	replace(roman, "IIIII", "V");
	replace(roman, "VV", "X");
	replace(roman, "XXXXX", "L");
	replace(roman, "LL", "C");
	replace(roman, "CCCCC", "D");
	replace(roman, "DD", "M");

	// then perform standard reduction
	replace(roman, "DCCCC", "CM");
	replace(roman, "CCCC", "CD");
	replace(roman, "LXXXX", "XC");
	replace(roman, "XXXX", "XL");
	replace(roman, "VIIII", "IX");
	replace(roman, "IIII", "IV");
}

void RemoveSubtractives(string& roman) {
	replace(roman, "CM", "DCCCC");
	replace(roman, "CD", "CCCC");
	replace(roman, "XC", "LXXXX");
	replace(roman, "XL", "XXXX");
	replace(roman, "IX", "VIIII");
	replace(roman, "IV", "IIII");
}

void RomanAddition() {
	string val1, val2;
	cout << "\n\nInput the first Roman number :";
	//getline(cin, val1);
	cin >> val1;
	cout << "\nInput the second Roman number : ";
	//getline(cin , val2);
	cin >> val2;


	RemoveSubtractives(val1);
	cout << "\nStep1: removing substractives from the addend 1: "<<val1;
	RemoveSubtractives(val2);
	cout << "\nStep2: removing substractives from the addend 2: " << val2;
	string result = val1 + val2;
	cout << "\nStep3: concatenating both: " << result;
	sortString(result);
	cout << "\nStep4: sort letters: " << result;
	AddSubtractives(result);
	cout << "\nStep5: add substractives";
	cout << "The sum of " << val1<< " + " << val2 <<" = "<<result;

}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

int decode(char t) {
	switch (t) {
	case 'M':
		return 1000;
	case 'D':
		return 500;
	case 'C':
		return 100;
	case 'L':
		return 50;
	case 'X':
		return 10;
	case 'V':
		return 5;
	case 'I':
		return 1;
	}
}


void encodeAssignment() {

	int pick;

	Encrypt encrypt;
	string original;

	cout << "\n\nWelcome to encoder!";

	do {
		cout << "\n\n1. Enter the string data";
		cout << "\n2. Encrypt the string";
		cout << "\n3. Decrypt the string";
		cout << "\n4. Exit";
		cout << "\n\nPlease make your selection:";

		cin >> pick;

		switch (pick) {
		case 1:
			cout << "\nPlease enter your original message:";
			//cin.getline( original, 50);
			std::cin.ignore(INT_MAX,'\n');
			std::getline(std::cin, original);
			//cin >> original;
			encrypt.set_original(original);
			break;
		case 2:
			if (!encrypt.is_origin_exist()) {
				cout << "No original data was found.Please ensure that you enter the string prior to encrypting or decrypting";
			}
			else {
				encription_menu(encrypt);
			}
			break;
		case 3:
			if (!encrypt.is_origin_exist()) {
				cout << "No original data was found.Please ensure that you enter the string prior to encrypting or decrypting";
			}
			else if (!encrypt.is_encrypted_exist()) {
				cout << "Original data has been provided but it has not been encrypted. Please encrypt prior to decrypting.";
			}
			else {
				decription_menu(encrypt);
			}
			break;
		case 4:
			break;

		default:
			std::cout << "\nWrong input, please try again";
		}
	} while (pick != 4);

	std::cout << "\nThank you for using the application";


}


void encription_menu(Encrypt& encrypt) {

	int pick;

	char xorChar;
	int caesarShift;
	string vigenereKey;

	cout << "\n\nWhat Cypher would you like to use?";

	do {
		cout << "\n\n1. XOR Cypher";
		cout << "\n2. Caesar Cypher";
		cout << "\n3. Vigenere Cypher";
		cout << "\n\nPlease make your selection:";

		cin >> pick;

		switch (pick) {
		case 1:
			cout << "\nPlease specify the key character:";
			xorChar = getchar();
			encrypt.XOR_encrypt(xorChar);
			return;
		case 2:
			do {
			cout << "\nPlease specify the shift between 0 and 25:";
				cin >> caesarShift;
				if (caesarShift < 0 || caesarShift>25)
					cout << "Sorry this shift is invalid. It should be between 0 and 25 inclusive. Please try again.";
			} while (caesarShift<0 || caesarShift>25);
			encrypt.Caesar_encrypt(caesarShift);
			return;
		case 3:
			do {
				cout << "\nPlease enter the key word:";
				//getline(cin, vigenereKey);
				cin >> vigenereKey;
				if (vigenereKey.length() < 3) {
					cout << "Sorry this key is invalid. Please try another keyword that consists of 3 or more characters.";
				}
			}while(vigenereKey.length() < 3);

			encrypt.Vigenere_encrypt(vigenereKey);
			return;

		default:
			std::cout << "\nWrong input, please try again";
		}
	} while (true);
}

void decription_menu(Encrypt& encrypt) {

	int pick;

	char xorChar;
	int caesarShift;
	string vigenereKey;

	cout << "\n\nWhat Cypher would you like to use?";

	do {
		cout << "\n\n1. XOR Cypher";
		cout << "\n2. Caesar Cypher";
		cout << "\n3. Vigenere Cypher";
		cout << "\n\nPlease make your selection:";

		cin >> pick;

		switch (pick) {
		case 1:
			cout << "\nPlease specify the key character:";
			xorChar = getchar();
			encrypt.XOR_decrypt(xorChar);
			return;
		case 2:
			do {
				cout << "\nPlease specify the shift between 0 and 25:";
				cin >> caesarShift;
				if (caesarShift < 0 || caesarShift>25)
					cout << "Sorry this shift is invalid. It should be between 0 and 25 inclusive. Please try again.";
			} while (caesarShift < 0 || caesarShift>25);
			encrypt.Caesar_decrypt(caesarShift);
			return;
		case 3:
			do {
				cout << "\nPlease enter the key word:";
				//getline(cin , vigenereKey);
				cin >> vigenereKey;
				if (vigenereKey.length() < 3) {
					cout << "Sorry this key is invalid. Please try another keyword that consists of 3 or more characters.";
				}
			} while (vigenereKey.length() < 3);

			encrypt.Vigenere_decrypt(vigenereKey);
			return;
		default:
			std::cout << "\nWrong input, please try again";
		}
	} while (true);

}



