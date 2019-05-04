#include<iostream>
using namespace std;

template <typename T>
class Dstack {
private:
	struct StackNode {
		T value;
		StackNode *next;

		StackNode(T v, StackNode *n = nullptr) {
			value = v;
			next = n;
		}
	};

	StackNode *top;
	StackNode *bottom;
	int size = 0;

public:
	Dstack() {

	}

	T getTop();
	int getSize();
	bool isEmpty();

	void Push(T);
	void Pop();

	void Display();
};

template <typename T>
T Dstack<T>::getTop() {
	if (top == nullptr)
		throw "Stack is empty [ Dstack.getTop() ]";
	else
		return top->value;
}

template <typename T>
int Dstack<T>::getSize() {
	return size;
}

template <typename T>
bool Dstack<T>::isEmpty() {
	if (top == nullptr)
		return true;
	else
		return false;
}

template <typename T>
void Dstack<T>::Push(T val) {
	if (isEmpty()) {
		top = new StackNode(val);
		bottom = top;
	}
	else
		top = new StackNode(val, top);
	size++;
}
template <typename T>
void Dstack<T>::Pop() {
	if (isEmpty())
		throw "Stack is empty [ Dstack.Pop() ]";
	else {
		StackNode *temp = top->next;
		delete top;
		top = temp;
		if (top == nullptr)
			bottom = nullptr;
		size--;
	}
}

template <typename T>
void Dstack<T>::Display() {
	if (isEmpty())
		throw "Stack is empty [ Dstack.Display() ]";
	else {
		for (StackNode *temp = top; temp != nullptr; temp = temp->next)
			cout << temp->value << " ";
		cout << endl;
	}
}
