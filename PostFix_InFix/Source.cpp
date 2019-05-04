#include <iostream>
#include <string>
#include "Evaluate.h"

using namespace std;

const string pF = "Post-fix", iF = "In-fix";

void doNotation(string notation) {
	cout << endl << endl << notation << endl << "====================================================" << endl;
	if (notation == pF)
		cout << " * There should be spaces between operands,\n   so multi-digit operands can be counted as one." << endl;
	cout << " * Enter 'b' at any time to go back to the main menu" << endl;

	bool goBack = false;
	while (goBack == false) {
		string expression;
		cout << endl << "Enter " << notation << " expression: ";
		getline(cin, expression);

		if (expression == "B" || expression == "b") {
			goBack = true;
			continue;
		}

		if (!parenthesisIsBalanced(expression))
			cout << " (!) Cannot Evaluate: Parenthesis are NOT balanced." << endl << endl;
		else {
			try {
				if (notation == pF)
					cout << "  " << expression << " = " << EvaluatePostFix(expression) << endl;
				if (notation == iF)
					cout << "  " << expression << " = " << EvaluateInFix(expression) << endl;
			}
			catch (...) {
				cout << " (!) Cannot Evaluate: Values and operators are NOT balanced. " << endl;
			}
		}
	}
}

void doConversion() {
	cout << endl << endl << iF << " to " << pF << endl << "====================================================" << endl;
	cout << " * Enter 'b' at any time to go back to the main menu" << endl;

	bool goBack = false;
	while (goBack == false) {
		string expression;
		cout << endl << "Enter " << iF << " expression: ";
		getline(cin, expression);

		if (expression == "B" || expression == "b") {
			goBack = true;
			continue;
		}

		if (!parenthesisIsBalanced(expression))
			cout << " (!) Cannot Convert: Parenthesis are NOT balanced." << endl << endl;
		else {
			try {
				cout << "  " << expression << " -> " << infixToPostfix(expression) << endl;
			}
			catch (...) {
				cout << " (!) Cannot Convert: Values and operators are NOT balanced. " << endl;
			}
		}
	}
}

int main() {
	bool exit = false;
	while (exit == false) {
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
		cout << "*               - It's a Calculator -               *" << endl;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
		cout << "1. In-fix notation" << endl;
		cout << "2. Post-fix notation" << endl;
		cout << "3. In-fix to post-fix conversion" << endl;
		cout << "4. Exit" << endl << endl;
		cout << "Make a selection: " << endl;
		int selection;
		cin >> selection;
		cin.ignore();

		while (selection < 1 || selection > 4) {
			cout << "Invalid input. Try again. ";
			cin >> selection;
			cin.ignore();
		}

		if (selection == 1)
			doNotation(pF);
		if (selection == 2)
			doNotation(iF);
		if (selection == 3)
			doConversion();
		if (selection == 4)
			exit = true;

		cout << endl << endl;
	}

	return 0;
}