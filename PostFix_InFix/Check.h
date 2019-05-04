#include<iostream>
#include<string>
using namespace std;

bool isOpenPar(char a) {
	if (a == '(' ||
		a == '[' ||
		a == '{')
		return true;
	else
		return false;
}
bool isClosePar(char a) {
	if (a == ')' ||
		a == ']' ||
		a == '}')
		return true;
	else
		return false;
}

int getPrecedence(char op) {
	if (isOpenPar(op))
		return 0;
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else
		return -1;
}

bool isDig(char a) {
	if (a == '0' ||
		a == '1' ||
		a == '2' ||
		a == '3' ||
		a == '4' ||
		a == '5' ||
		a == '6' ||
		a == '7' ||
		a == '8' ||
		a == '9')
		return true;
	else
		return false;
}

bool isOp(char a) {
	if (a == '+' ||
		a == '-' ||
		a == '*' ||
		a == '/' ||
		a == '^')
		return true;
	else
		return false;
}

bool parenthesisIsBalanced(string s) {
	Dstack <char> myStack;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
			myStack.Push(s[i]);
		if (s[i] == ')' || s[i] == '}' || s[i] == ']') {

			if (myStack.isEmpty() != true) {
				char oB = myStack.getTop();
				if (!((oB == '(' && s[i] == ')') ||
					(oB == '{' && s[i] == '}') ||
					(oB == '[' && s[i] == ']')))
					return false;
				else
					myStack.Pop();
			}
			else
				return false;
		}
	}
	if (myStack.isEmpty() == true)
		return true;
	else
		return false;
}