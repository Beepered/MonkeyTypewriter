#define SPACE 32
#define ESCAPE 27

#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdlib>


bool CheckNumber(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i]) == false)
			return false;
	}
	return true;
}

void LowercaseString(std::string& str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
}

void RemoveSpace(std::string& str) {
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

void MonkeyStart() {
	system("cls");

	int retries = 0; int type = 0; // 0 = print everything, 1 = print only stuff that advances and ends
	std::string goal = "Two households both alike in dignity";
	std::string currText = "";
	LowercaseString(goal);
	RemoveSpace(goal);

	std::string input;
	std::cout << "Custom goal to type to? (Y/N): ";
	std::cin >> input;
	if (input == "Yes" || input == "yes" || input == "Y" || input == "y") { // yeah this is dumb
		do {
			std::cout << "Give goal to type to (use letters only): ";
			input = ""; // reset input
			std::cin >> input;
		} while (CheckNumber(input));
		goal = input;
	}
	LowercaseString(goal);
	RemoveSpace(goal);

	std::cout << "Type 0: Print every try\n";
	std::cout << "Type 1: Print retries that have characters in goal\n";
	std::cout << "Type 2: Print retries that advance towards goal\n";
	std::cout << "Choose Print type 0, 1, or 2: ";
	std::cin >> input;
	if (input == "1")
		type = 1;
	else if (input == "2")
		type = 2;
	else
		type = 0;
	input = "";


	unsigned int seed; // Ask user input for seed value
	std::cout << "Enter the Seed Value: ";
	std::cin >> input;
	if (CheckNumber(input))
		seed = atoi(input.c_str());
	else
		seed = time(NULL);
	
	srand(seed);

	system("cls");

	int iterator = 0;
	std::string closestTry = "", farthestTry = "";
	while (1) { // don't know why but can't use   while(currText != goal)
		char x = 97 + rand() % 26;
		currText += x;
		if (type == 0) {
			std::cout << currText << "\n";
		}
		if (currText == goal) {
			std::cout << currText << "\n";
			break;
		}
		if (x != goal[iterator]) {
			if (type == 2) {
				if(currText.length() > farthestTry.length() && (currText.length() > 1))
					std::cout << currText << "\n";
				closestTry = "";
			}
			currText = "";
			iterator = 0;
			retries++;
		}
		else {
			if (type == 1) {
				std::cout << currText << " | retries: " << retries << "\n";
			}
			else if (type == 2) {
				closestTry += x;
				if (closestTry.length() > farthestTry.length()) {
					farthestTry = closestTry;
					std::cout << farthestTry << "\n";
				}
			}
			iterator++;
		}
	}

	std::cout << "\nRetries taken: " << retries << "\n\n";

	std::cout << "Press Escape to EXIT\tPress Space to go again\n";
	bool valid = false;
	while (!valid) {
		switch (char key = _getch()) {
		case SPACE:
			valid = true;
			MonkeyStart();
			break;
		case ESCAPE:
			std::cout << "\n\nEXITED\n";
			valid = true;
			break;
		}
	}
}

int main()
{
	MonkeyStart();
}