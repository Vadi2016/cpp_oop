#include "lesson1.hpp"

using namespace std;

class Power
{
private:
	float a;
	float b;
public:

	Power() : a(2.34), b(3.55) {}
	Power(float a, float b) : a(a), b(b) { }

	void set(float new_a, float new_b) 
	{
	   a = new_a;
	   b = new_b;
	}	

	float calculate()
	{
	  return pow(a, b);
	}
};


class RGBA 
{
private:
	std::uint8_t m_red;
	std::uint8_t m_green;
	std::uint8_t m_blue;
  	std::uint8_t m_alpha;
public:
	RGBA() : m_red(0), m_green(0), m_blue(0), m_alpha(255) { }

	RGBA(uint8_t red, uint8_t green, uint8_t blue,uint8_t alpha) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) { }

	~RGBA() { }

	void print() 
	{
	  cout << m_red << ", " << m_green << ", " << m_blue << ", " << m_alpha << endl; 
	}
};


class Stack
{
private:
    int arr[10];
    int length;
public:
    
    void reset()
    {
        for (int i = 0; i < 10; ++i)
        {
            arr[i] = 0;
        }
        length = 0;
    }
    
    bool push(int n)
    {
        if (length <= 10) {
            arr[length] = n;
            length++;
            return true;
        }
        return false;
    }
    
    int pop()
    {
        if (length != 0) {
            --length;
            arr[length] = 0;
            return 0;
        }
        cout << "Stack is empty!" << endl;
        return 1;
    }
    
    void print()
    {
        cout << "(";
        for (int i = 0; i < 10; ++i)
        {
            if (arr[i] != 0)
            {
              cout << arr[i] ;
            }
        }
        cout << ")" << endl;
    }
};


int main(int argc, char** args) 
{
    // task 1
    Power power;
    cout << power.calculate() << endl;
  
    // task 2
    RGBA rgba(65, 66, 123, 255);
    rgba.print();
  
    // task 3
    Stack stack;
    
    stack.reset();
    stack.print();
    
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    
    stack.pop();
    stack.print();
    
    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}
