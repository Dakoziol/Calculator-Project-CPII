#include <iostream>
#include <string>
#include "Dstack.h"
#include "Check.h"

double Power(double val, int pow) {
	double ans = 1;
	for (int i = 0; i < pow; i++)
		ans *= val;
	return ans;
}

double GetOperand(string exp, int& i) {
	double operand = 0;
	bool inDec = false;
	double decPlace = 10;

	while (i < exp.length() && (isDig(exp[i]) || exp[i] == '.')) {

		if (exp[i] == '.') {
			inDec = true;
			i++;
			continue;
		}
		if (!inDec)
			operand = (operand * 10) + (exp[i] - '0');
		else {
			operand += (exp[i] - '0') / decPlace;
			decPlace = decPlace * 10;
		}
		i++;
	}
	i--;
	return operand;
}

void Crunch(Dstack<double>& stack, char op) {
	double a = stack.getTop();
	stack.Pop();
	double b = stack.getTop();
	stack.Pop();
	
	if (op == '+')
		stack.Push(b + a);
	if (op == '-')
		stack.Push(b - a);
	if (op == '*')
		stack.Push(b * a);
	if (op == '/')
		stack.Push(b / a);
	if (op == '^')
		stack.Push(Power(b, a));
}
void Crunch(Dstack<double>& numStack, Dstack<char>& opStack) {
	double a = numStack.getTop();
	numStack.Pop();
	double b = numStack.getTop();
	numStack.Pop();
	char op = opStack.getTop();
	opStack.Pop();

	if (op == '+')
		numStack.Push(b + a);
	if (op == '-')
		numStack.Push(b - a);
	if (op == '*')
		numStack.Push(b * a);
	if (op == '/')
		numStack.Push(b / a);
	if (op == '^')
		numStack.Push(Power(b, a));
}

double EvaluatePostFix(string exp) {
	Dstack<double> stack;

	for (int i = 0; i < exp.length(); i++) {

		if (isDig(exp[i]) || exp[i] == '.')
			stack.Push(GetOperand(exp, i));

		else if (isOp(exp[i]))
			Crunch(stack, exp[i]);
	}
	
	if (stack.getSize() == 1)
		return stack.getTop();
	else
		throw "Imbalanced Operators";
}

double EvaluateInFix(string exp) {
	Dstack<double> numStack;
	Dstack<char> opStack;

	for (int i = 0; i < exp.length(); i++) {

		if (isDig(exp[i]) || exp[i] == '.') {
			numStack.Push(GetOperand(exp, i));
		}

		else if (isOpenPar(exp[i]))
			opStack.Push(exp[i]);

		else if (isClosePar(exp[i])) {
			while (!opStack.isEmpty() && !isOpenPar(opStack.getTop()))
				Crunch(numStack, opStack);

			opStack.Pop();
		}

		else if (isOp(exp[i])) {
			while (!opStack.isEmpty() && (getPrecedence(opStack.getTop()) >= getPrecedence(exp[i])))
				Crunch(numStack, opStack);

			opStack.Push(exp[i]);
		}
	}

	while (!opStack.isEmpty())
		Crunch(numStack, opStack);

	if (numStack.getSize() == 1 || !opStack.isEmpty())
		return numStack.getTop();
	else
		throw "Unbalanced operands and operators";
}
string infixToPostfix(string inFixExp) {
	Dstack<char> stack;
	string postFixExp;

	for (int i = 0; i < inFixExp.length(); i++) {

		if (isDig(inFixExp[i]) || inFixExp[i] == '.') {
			string operandS = to_string(GetOperand(inFixExp, i));
			while (operandS.back() == '0' || operandS.back() == '.')
				operandS.pop_back();
			postFixExp += operandS + ' ';
		}

		else if (isOpenPar(inFixExp[i]))
			stack.Push(inFixExp[i]);

		else if (isClosePar(inFixExp[i])) {
			while (!isOpenPar(stack.getTop()) && !stack.isEmpty()) {
				postFixExp += stack.getTop();
				stack.Pop();
			}
			if (isOpenPar(stack.getTop()))
				stack.Pop();
		}

		else if (isOp(inFixExp[i])) {
			while (!stack.isEmpty() && getPrecedence(stack.getTop()) >= getPrecedence(inFixExp[i])) {
				postFixExp += stack.getTop();
				stack.Pop();
			}
			stack.Push(inFixExp[i]);
		}
	}

	while (!stack.isEmpty()) {
		postFixExp += stack.getTop();
		stack.Pop();
	}
	
	return postFixExp;
}