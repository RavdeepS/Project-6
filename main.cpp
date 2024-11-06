
#include<iostream>
#include <cstdlib>
using namespace std;

class Stack {
private:
    static const int STACK_SIZE = 128;
    int _stack[STACK_SIZE], _top;
public:
    Stack() : _top(-1) {}
    void push(int val) { if (_top < STACK_SIZE - 1) _stack[++_top] = val; }
    int pop() { if (_top == -1) exit(1); return _stack[_top--]; }
};

int main() {
    struct TabEnt { int type, value; };
    Stack stk; int size = 0, value; char op;
    TabEnt Tab[128];

    // Input and parsing loop
    while (true) {
        cout << "Enter 1 for integer, 2 for operand, 0 to terminate: ";
        int code; cin >> code; if (!code) break;
        if (code == 1) {
            cout << "Enter integer: "; cin >> value;
            Tab[size++] = {1, value};
        } else if (code == 2) {
            cout << "Enter operator (+, -, *, /): "; cin >> op;
            Tab[size++] = {2, (op == '+') ? 1 : (op == '-') ? 2 : (op == '*') ? 3 : 4};
        }
    }

    // Print postfix expression
    cout << "Postfix expression: ";
    for (int i = 0; i < size; i++) {
        cout << (Tab[i].type == 1 ? to_string(Tab[i].value) : 
                 (Tab[i].value == 1 ? "+" : Tab[i].value == 2 ? "-" : 
                 Tab[i].value == 3 ? "*" : "/")) << " ";
    }
    cout << endl;

    // Evaluate postfix expression
    for (int i = 0; i < size; i++) {
        if (Tab[i].type == 1) {
            stk.push(Tab[i].value);
        } else {
            int b = stk.pop(), a = stk.pop();
            stk.push(Tab[i].value == 1 ? a + b : 
                     Tab[i].value == 2 ? a - b : 
                     Tab[i].value == 3 ? a * b : a / b);
        }
    }

    // Output result
    cout << "Answer: " << stk.pop() << endl;
    return 0;
}

