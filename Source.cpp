#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
using namespace std;

// STRUCT AND CLASS DECLARATIONS-------------------------------------------
struct Node {
	string animeTitle = " ";
	Node* next = NULL;
	Node(string data) :animeTitle(data) {}
};

class Set {
private:
	Node* head = NULL;
	Node* tail = NULL;
	int currentTitleCount = 0;
	string displayName = " ";

public:
	void storeNames();
	int getItemCount();
	string stringToLowerCase(string);

	void searchStart();
	bool autoComplete(string input);
	void appendIfTitleNotFound(string input, string titleToAppend);
	void displayAll();

};


// CLASS SET: FUNCTION DEFINITIONS------------------------------------------------
void Set::storeNames() {
	ifstream infile;
	infile.open("titles.txt");

	while (getline(infile, displayName)) {
		Node* newNode = new Node(displayName);

		if (head != NULL) {
			tail->next = newNode;
			tail = newNode;
			currentTitleCount++; //increment counter
		}
		else {
			head = newNode;
			tail = newNode;
			currentTitleCount++; //increment counter
		}
	}
	infile.close();
}


int Set::getItemCount() {
	return currentTitleCount;
}


string Set::stringToLowerCase(string strng) {
	string temp = " ";
	for (int i = 0; i < strng.length(); i++) {
		temp += tolower(strng.at(i));
	}
	return temp;
}


void Set::searchStart() {
	char ch = ' ';
	int charCount = 0;
	char charArray[100] = { ' ' };
	int i = 0;

	cout << "Search: " << endl << endl;
	displayAll();
	while (1) {

		if (_kbhit()) {
			system("cls");

			ch = _getch();
			if (ch == '\b') {	//if user presses backspace, do instructions below:

				string UserInput_chartoString = "";
				if (charCount > 0) {
					charCount--;
					charArray[charCount] = NULL;

					cout << "Search: ";

					for (i = 0; i < charCount; i++) {
						cout << charArray[i];
						UserInput_chartoString += charArray[i]; //converts char array into string
					}
					cout << endl << endl;
					autoComplete(UserInput_chartoString);
					continue;

				}
				else {

					cout << "Search: " << endl;

					if (charCount > 2) {
						autoComplete(UserInput_chartoString);
						continue;
					}
					else {
						cout << endl;
						displayAll();
					}
				}
				//continue;
			}

			//IGNORE----------------------------------------------------------
			//else if (ch == '\n') { 
			//	string UserInput_chartoString = "";
			//	for (i = 0; i < charCount; i++) {
			//		cout << charArray[i];
			//		UserInput_chartoString += charArray[i];
			//	}
			//	cout << "TESTING" << endl;
			//	/*if (autoComplete(UserInput_chartoString) == false) {

			//	}*/
			//}
			//IGNORE----------------------------------------------------------

			else {	//if user does not press backspace, do instructions below:
				charArray[charCount] = ch;
				charCount++;
				cout << "Search: ";
				string UserInput_chartoString = "";
				for (i = 0; i < charCount; i++) {
					cout << charArray[i];
					UserInput_chartoString += charArray[i];
				}
				cout << endl << endl;

				//if charCount is less than 3, display all
				if (charCount < 3) {
					displayAll();
				}
				//else, call autocomplete function to match user's search
				else {
					autoComplete(UserInput_chartoString);
					continue;
				}
			}
		}
	}
		//return true;
}



bool Set::autoComplete(string input) {
	int resultsMatched = 0;

	Node* current = head;
	while (current != NULL) {
		if (stringToLowerCase(current->animeTitle).find(stringToLowerCase(input), 0) != string::npos) {
			cout << current->animeTitle << endl;	
			resultsMatched++;
		}
		current = current->next;
	}
	if (resultsMatched == 0) { //no matches found
		return false;
	}
	return true;
}


void Set::appendIfTitleNotFound(string response, string titleToAppend) { //ask user if they want to add title if their search is not found
	if (response == "Yes" || response == "YES" || response == "yes" || response == "YeS" || response == "YEs" || response == "yES") {
		Node* newNode = new Node(titleToAppend);

		if (head != NULL) {
			tail->next = newNode;
			tail = newNode;
			currentTitleCount++; //increment counter
		}
		else {
			head = newNode;
			tail = newNode;
			currentTitleCount++; //increment counter
		}
		return;
	}
	else if (response == "No" || response == "NO" || response == "no" || response == "nO") {
		return;
	}
	else
		cout << "ERROR! UNNACEPTABLE INPUT!" << endl;
	//return true;
}


void Set::displayAll() {
	Node* current = head;
	while (current != NULL){
		cout << current->animeTitle << endl;
		current = current->next;
	}

}



// MAIN FUNCTION--------------------------------------------------------------------
int main() {
	Set searchEngine;
	searchEngine.storeNames();
	searchEngine.searchStart();


	return 0;
}