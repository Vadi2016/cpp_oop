#include "lesson3.hpp"


using namespace std;


//task 1

class Figure
{
public:
    Figure() {}
    
    virtual double area() = 0;
};

class Parallelogram: public Figure
{
private:
    double m_baseLength;
    double m_height;
public:
    Parallelogram(double baseLength, double height): m_baseLength(baseLength), m_height(height) {}
    
    Parallelogram() {}
    
    virtual double area()
    {
        return m_baseLength * m_height;
    }
};

class Circle: public Figure
{
private:
    double m_radius;
public:
    Circle(double radius): m_radius(radius) {}
    
    double area()
    {
        return M_PI * pow(m_radius, 2);
    }
};


class Rectangle: public Parallelogram
{
private:
    double m_width;
    double m_height;
public:
    Rectangle(double width, double height): m_width(width), m_height(height) {}
    
    double area()
    {
        return m_width * m_height;
    }
};

class Square: public Parallelogram
{
private:
    double m_height;
public:
    Square(double height): m_height(height) {}
    
    double area()
    {
        return pow(m_height, 2);
    }
};

class Rhombus: public Parallelogram
{
private:
    double m_diagonal1;
    double m_diagonal2;
public:
    Rhombus(double diagonal1, double diagonal2): m_diagonal1(diagonal1), m_diagonal2(diagonal2) {}
    
    double area()
    {
        return 0.5 * m_diagonal1 * m_diagonal2;
    }
};

//task 2

class Car
{
protected:
    string m_company;
    string m_model;
public:
    Car(string company, string model): m_company(company), m_model(model) {
        cout << "Ctor Car" << endl;
    }
    
    Car () {
        cout << "Ctor Car" << endl;
    }
};

class PassengerCar: virtual public Car
{
public:
    PassengerCar() {
        cout << "Ctor PassengerCar" << endl;
    }
    
};

class Bus: virtual public Car
{
public:
    Bus() {
        cout << "Ctor Bus" << endl;
    }
};

class Minivan: public PassengerCar, public Bus
{
public:
    Minivan() {
        cout << "Ctor Minivan" << endl;
    }
};


// task 3

class Fraction
{
private:
    double numerator;
    double denominator;
public:
    Fraction(double n, double d) {
        numerator = n;
        if (d != 0)
        {
            denominator = d;
        } else {
            cout << "Знаменатель не должен быть равен нулю!" << endl;
        }
    }
    
    double getNumerator() const
    {
        return numerator;
    }
    
    double getDenominator() const
    {
        return denominator;
    }
    
    Fraction operator-()
    {
        double num = 1 - numerator/denominator;
        double zn = 1 * 1000000;
        num *= 1000000;
        cout << (int)num / 2 << endl;
        while ((int)num % 2 ==0)
        {
            num /= 2;
            zn /= 2;
        }
        
        return Fraction(num, zn);
    }
};

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getNumerator() + f2.getNumerator(), f1.getDenominator() + f2.getDenominator());
}

Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getNumerator() - f2.getNumerator(), f1.getDenominator() - f2.getDenominator());
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getNumerator() * f2.getNumerator(), f1.getDenominator() * f2.getDenominator());
}

Fraction operator/(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getNumerator() * f2.getDenominator(), f1.getDenominator() * f2.getNumerator());
}

bool operator==(const Fraction &f1, const Fraction &f2)
{
    return f1.getNumerator() == f2.getNumerator() && f1.getDenominator() == f2.getDenominator();
}

bool operator!=(const Fraction &f1, const Fraction &f2)
{
    return !(f1 == f2);
}

bool operator<(const Fraction &f1, const Fraction &f2)
{
    return (f1.getNumerator() / f1.getDenominator()) < (f2.getNumerator() / f2.getDenominator());
}

bool operator>(const Fraction &f1, const Fraction &f2)
{
    return (f1.getNumerator() / f1.getDenominator()) > (f2.getNumerator() / f2.getDenominator());
}

bool operator<=(const Fraction &f1, const Fraction &f2)
{
    return (f1.getNumerator() / f1.getDenominator()) <= (f2.getNumerator() / f2.getDenominator());
}

bool operator>=(const Fraction &f1, const Fraction &f2)
{
    return (f1.getNumerator() / f1.getDenominator()) >= (f2.getNumerator() / f2.getDenominator());
}


//task 4
class Card
{
private:
    enum suit { HEARTS, DIAMONDS, SPADES, CLUBS };
    enum value { ACE = 1, KING, QUEEN, JACK, JOKER, TEN, NINE, EIGHT, SEVEN, SIX, FIVE, FOUR, THREE };
    bool situation;
public:
    bool Flip()
    {
        if (situation)
            situation = false;
        else
            situation = true;
        return situation;
    }
    
    int GetValue(int val) const
    {
        switch (val) {
            case 1:
                return ACE;
                break;
            case 2:
                return KING;
                break;
            case 3:
                return QUEEN;
                break;
            default:
                break;
        }
        return 0;
    }
};


int main(int argc, char** args) 
{
    // task 1
    Parallelogram par(10, 5);
    Circle circle(23.5);
    Rectangle rect(5, 4);
    Square sq(14.4);
    Rhombus romb(3, 2.4);
    cout << "Parallelogram area = " << par.area() << endl;
    cout << "Circle area = " << circle.area() << endl;
    cout << "Rectangle area = " << rect.area() << endl;
    cout << "Square area = " << sq.area() << endl;
    cout << "Rhombus area = " << romb.area() << endl;
    
    
    // task 2
    
    Car car("BMW", "520i");
    PassengerCar pc;
    Bus bus;
    Minivan minivan;
    
    
    // task 3
    
    Fraction f1(6, 21);
    Fraction f2(5, 12);
    
    Fraction fractionResult = f1 + f2;
    cout << "\nSum: \n" << fractionResult.getNumerator() << "/" << fractionResult.getDenominator() << endl;
    
    fractionResult = f2 - f1;
    cout << "\nSubtraction: \n" << fractionResult.getNumerator() << "/" << fractionResult.getDenominator() << endl;
    
    fractionResult = f1 * f2;
    cout << "\nMultiplication: \n" <<fractionResult.getNumerator() << "/" << fractionResult.getDenominator() << endl;
    
    fractionResult = f2 / f1;
    cout << "\nDivision: \n" << fractionResult.getNumerator() << "/" << fractionResult.getDenominator() << endl;
    
    fractionResult = -f1;
    cout << "\nFraction unary operator `-`: \n" << fractionResult.getNumerator() << "/" << fractionResult.getDenominator() << endl;
    
    
    if (f1 == f2)
    {
        cout << "The fractions is equals" << endl;
    }
    else if (f1 != f2)
    {
        cout << "The fractions is not equals" << endl;
    }
    if (f1 < f2){
        cout << "f2 more than f1" << endl;
    }
    
    if (f1 > f2){
        cout << "f2 less than f1" << endl;
    }
    
    if (f1 <= f2){
        cout << "f2 more than f1 or equals" << endl;
    }
    
    if (f1 >= f2){
        cout << "f2 less than f1 or equals" << endl;
    }
    
    cout << endl;
    
    return 0;
}



