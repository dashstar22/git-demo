#include <iostream>
using namespace std;

class Stack 
{
private:
    int* arr;        
    int top;         
    int capacity;    

public:
    
    Stack(int s) : capacity(s), top(-1) 
{
        arr = new int[capacity];
        cout << "constructor 2" << endl;
    }

   
    ~Stack() 
{
        delete[] arr;
        cout << "destructing" << endl;
    }

    void push(int value) 
{
        if (top + 1 >= capacity) 
	{
            return; 
        }
        arr[++top] = value;
    }

   
    void pop() 
{
        if (top >= 0) 
	{
            --top;
        }
    }

  
    int topValue() 
{
        if (top >= 0) 
	{
            return arr[top];
        }
        return -1; 
    }

   
    bool isEmpty() 
{
        return top == -1;
    }
};

int main() {
    int s, n;
    cin >> s ;
    cin >> n;
    Stack stack(s);

    for (int i = 0; i < n; ++i) 
{
        int command;
        cin >> command;
        
        if (command == 1)
	 { 
            int value;
            cin >> value;
            stack.push(value);
        } else if (command == 2)
 	{ 
            stack.pop();
        } else if (command == 3) 
	{ 
            if (!stack.isEmpty()) 
	{
                cout << stack.topValue() << endl;
            }
        } else if (command == 4)
	 { 
            cout << (stack.isEmpty() ? 0 : 1) << endl;
        }
    }
    return 0;
}
