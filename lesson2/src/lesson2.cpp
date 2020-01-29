#include "lesson2.hpp"


using namespace std;

// task 1
class Book
{
protected:
    string title;
    string author;
    int price;
    
public:
    Book (string title, string author, int price): title(title), author(author), price(price) { }
    
    Book() { }
    
    void setTitle(string title)
    {
        this->title = title;
    }
    
    string getTitle() const
    {
        return this->title;
    }
    
    void setAuthor(string author)
    {
        this->author = author;
    }
    
    string getAuthor() const
    {
        return this->author;
    }
    
    void setPrice(int price)
    {
        this->price = price;
    }
    
    int getPrice() const
    {
        return price;
    }
};

class GoldenEditionBook : public Book
{
private:
    int percent;
public:
    GoldenEditionBook (string title, string author, int price) : Book(title, author, price) {
        this->percent = price * 0.3;
        price -= this->percent;
        setPrice(price);

    }
    
    GoldenEditionBook() { }
    
    int getPrice() const
    {
        return price + percent;
    }
};


bool validatePrice(int price)
{
    return price > 0;
}


int countWords(string strString)
{
    int nSpaces = 0;
    unsigned int i = 0;

    while(isspace(strString.at(i)))
      i++;

    for(; i < strString.length(); i++)
    {
      if(isspace(strString.at(i)))
      {
        nSpaces++;
        while(isspace(strString.at(i++)))
          if(strString.at(i) == '\0')
            nSpaces--;
      }
    }

    return nSpaces + 1;
}

bool validateAuthorName(string authorName)
{
    int count = countWords(authorName);
    return count == 1 || count == 2;
}

bool validateTitle(string title)
{
    int found = title.find_first_not_of("1234567890");
    return found == 0;
}


//task 2


class Human
{
protected:
    string m_firstName;
    string m_lastName;
public:
    Human(string firstName, string lastName): m_firstName(firstName), m_lastName(lastName) {
        
    }
    
    Human() {}
    
    string getFirstName() const {
        return m_firstName;
    }
    
    string getLastName() const {
        return m_lastName;
    }
};


class Student: public Human
{
private:
    string m_facultyNumber;
    static int count;
    const int id;
public:
    Student(string firstName, string lastName, string facultyNumber): Human(firstName, lastName), m_facultyNumber(facultyNumber), id(++count)  {
    }
    
    Student(): id(++count) {

    }
    
    
    static int getCount() {
        return count;
    }
    
    int getId()
    {
        return id;
    }
    
    string getFacultyNumber() {
        return m_facultyNumber;
    }
    
    
    
};

class Worker: public Human
{
private:
    double m_weekSalary;
    double m_hoursePerDay;
    static int count;
    const int id;
public:
    Worker(string firstName, string lastName, double weekSalary, double hoursePerDay): Human(firstName, lastName), m_weekSalary(weekSalary), m_hoursePerDay(hoursePerDay), id(++count) { }
    
    Worker(): id(++count) {

    }
    static int getCount() {
        return count;
    }
    
    double getWeekSalary() const
    {
        return m_weekSalary;
    }
    
    double getHoursePerDay() const
    {
        return m_hoursePerDay;
    }
    
    int getId()
    {
        return id;
    }
};

int Student::count = 0;
int Worker::count = 0;


Student& getStudentById(int Id, Student arr[])
{
    for (int i = 0; i < Student::getCount(); ++i)
    {
        if (arr[i].getId() == Id) {
            return arr[i];
        }
    }
    return *new Student();
}

Worker& getWorkerById(int Id, Worker arr[])
{
    for (int i = 0; i < Worker::getCount(); ++i)
    {
        if (arr[i].getId() == Id) {
            return arr[i];
        }
    }
    return *new Worker();
}


int main(int argc, char** args)
{
    
    //task 1
    GoldenEditionBook book("Мертвые души", "Николай Гоголь", 100);
    if (validateTitle(book.getTitle()) && validateAuthorName(book.getAuthor()) && validatePrice(book.getPrice())) {
        cout << "Книга валидна" << endl;
    } else {
        cout << "Книга не валидна! Попробуйте еще раз." << endl;
    }
    
    //task 2
    Worker w1("Ivan", "Vasilev", 7000.00, 8);
    Worker w2("Genadii", "From", 5200.00, 6);
    Student s1 ("Stepan", "Gavr", "21D");
    Worker w3("Vasilii", "Gradusov", 8200.00, 10);
    Student s2 ("Inna", "Gavreva", "24D");
    Student s3 ("Diana", "Davidova", "345AS");
    Student s4 ("Masha", "Petrova", "345AS");
    const int size = 4;
    Student students[size] = {s1, s2, s3, s4};
    Worker workers[size] = {w1, w2, w3};
    Student s = getStudentById(3, students);
    cout << "Студент: " << s.getFirstName() << " " << s.getLastName() << "\nФакультет номер: " << s.getFacultyNumber() << endl;
    cout << endl;
    Worker w = getWorkerById(2, workers);
    cout << "Работник: " << w.getFirstName() << " " << w.getLastName() << "\nЗарплата за неделю: " << w.getWeekSalary() << "\nРабочих часов в день: " << w.getHoursePerDay() << endl;
    return 0;
}


// task 3
// получилось 7 классов

class Card
{
    
};

class Hand
{
    
}

class Player: Hand
{
    
};

class AI : public Player
{
    
};

class Person: public Player
{
    
};

class Deck: public Hand
{
    
}

class Game
{
    
};


