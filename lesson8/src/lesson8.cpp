#include "lesson8.hpp"

using namespace std;

class DivisionByZero {
private:
    string m_msg;
public:
    DivisionByZero(string msg): m_msg(msg) { }
    
    friend ostream& operator<<(ostream& os, DivisionByZero& ex);
};

ostream& operator<<(ostream& os, DivisionByZero& ex)
{
    os << ex.m_msg.c_str() << endl;
    return os;
}

double divide(int numerator, int denominator)
{
    if (denominator == 0) throw DivisionByZero("Division by zero!");
    return (numerator / denominator);
}


class Ex
{
private:
    double x;
    
public:
    Ex(double ay): x(ay) { }
    
    friend ostream& operator<<(ostream& os, Ex& ex);
};

ostream& operator<<(ostream& os, Ex& ex)
{
    os << ex.x;
    return os;
}

class Bar
{
private:
    double y;
public:
    Bar() {
        y = 0;
    }
    
    void set(double a) {
        if ((y + a) > 100) {
            throw Ex(a + y);
        }
        else
            y = a;
    }
    
};


class OffTheField
{
private:
    int m_x;
    int m_y;
    string m_direction;
public:
    OffTheField(int x, int y, string direction): m_x(x), m_y(y), m_direction(direction) {}
    virtual ~OffTheField() {}
    
    friend ostream& operator<<(ostream& os, OffTheField& ex);
};

ostream& operator<<(ostream& os, OffTheField& ex)
{
    os << "Your robot out of the field.\nPosition of robot: " << ex.m_x << " : " << ex.m_y << "\nDirection: " << ex.m_direction;
    return os;
}

class IllegalCommand
{
private:
    int m_x;
    int m_y;
public:
    IllegalCommand(int x, int y): m_x(x), m_y(y) {}
    virtual ~IllegalCommand() {}
    friend ostream& operator<<(ostream& os, IllegalCommand& ex);
};

ostream& operator<<(ostream& os, IllegalCommand& ex)
{
    os << "The direction is not in the right range!\nPosition of robot: " << ex.m_x << " : " << ex.m_y;
    return os;
}


enum Command {
    UP = 1, DOWN, LEFT, RIGHT, EXIT = 0
};

class Robot
{
private:
    
    int m_x;
    int m_y;
    const int width;
    const int height;
public:
    Robot(): width(10), height(10)  {
        m_x = 0;
        m_y = 0;
    }
    
    virtual ~Robot() {}
    
    void step(int command)
    {
        switch (command) {
            case UP:
                m_y++;
                if (m_y > height){
                    m_y--;
                    throw OffTheField(m_x, m_y, "UP");
                }
                    
                cout << "Direction: UP\n" << "Position: " << m_x << " : " << m_y << endl;
                break;
            case DOWN:
                m_y--;
                if (m_y < 0){
                    m_y++;
                    throw OffTheField(m_x, m_y, "DOWN");
                }
                cout << "Direction: DOWN\n" << "Position: " << m_x << " : " << m_y << endl;
                break;
            case LEFT:
                m_x--;
                if (m_x < 0) {
                    m_x++;
                    throw OffTheField(m_x, m_y, "LEFT");
                }
                cout << "Direction: LEFT\n" << "Position: " << m_x << " : " << m_y << endl;
                break;
            case RIGHT:
                m_x++;
                if (m_x > width) {
                    m_x--;
                    throw OffTheField(m_x, m_y, "RIGHT");
                }
                cout << "Direction: RIGHT\n" << "Position: " << m_x << " : " << m_y << endl;
                break;
            case EXIT:
                cout << "Goodbye!" << endl;
                break;
            default:
                throw IllegalCommand(m_x, m_y);
                break;
        }
    }
};


int main(int argc, char** args)
{
    try
    {
        divide(2, 0);
    } catch (DivisionByZero ex) {
        cerr << ex;
    }
    Bar bar;
    int n = 0;
    do {
        cout << "Enter a number: ";
        cin >> n;
        try
        {
            bar.set(n);
        }
        catch(Ex &ex)
        {
            cerr << "Exception number: " << ex << endl;
        }
    } while(n != 0);
    
    Robot robot;
    int command;
    
    do {
        cout << "Enter direction of robot (UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4) in the field 10x10 (for exit enter 0): " << endl;
        try {
            cin >> command;
            robot.step(command);
        }
        catch (IllegalCommand& il)
        {
            cout << il << endl;
        }
        catch (OffTheField& ex)
        {
            cout << ex << endl;
        }
        catch (...)
        {
            cout << "Error " << endl;
        }
        
    } while (command != EXIT);
    
    return 0;
}

