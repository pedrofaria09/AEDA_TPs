# include <iostream>
# include <stack>

using namespace std;

template<class T>
class StackExt {
	stack<T> stack, min;

public:
	StackExt() {
	}
	;
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template<class T>
bool StackExt<T>::empty() const {
	if (stack.empty())
		return true;
	else
		return false;
}

template<class T>
T& StackExt<T>::top() {
	if (!stack.empty()) {
		return stack.top();
	}
}

template<class T>
void StackExt<T>::pop() {

	if (!stack.empty() && !min.empty()) {
		if(stack.top() == min.top())
			min.pop();
		stack.pop();
	}
}

template<class T>
void StackExt<T>::push(const T& val) {
	stack.push(val);

	if (!min.empty()) {
		if (val < min.top())
			min.push(val);
	} else {
		min.push(val);
	}
}

template<class T>
T& StackExt<T>::findMin() {
	if (!min.empty()) {
		return min.top();
	}
}
