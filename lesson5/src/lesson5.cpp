#include "lesson5.hpp"


using namespace std;


//task 1
template <typename T>
class Pair1
{
private:
    T m_dig1;
    T m_dig2;
public:
    Pair1(T dig1, T dig2): m_dig1(dig1), m_dig2(dig2) {
        
    }
    
    T first() const {
        return m_dig1;
    }
    
    T second() const {
        return m_dig2;
    }
    
    ~Pair1() { }
};

//task 2
template <typename T, typename U>
class Pair
{
private:
    T m_dig1;
    U m_dig2;
public:
    Pair(T dig1, U dig2): m_dig1(dig1), m_dig2(dig2) {

    }

    Pair() {

    }
    T first() const {
        return m_dig1;
    }

    U second() const {
        return m_dig2;
    }

    ~Pair() { }
};

//task 3
template <typename U>
class StringValuePair: public Pair<string, U>
{
public:
    StringValuePair(string param1, U param2): Pair<string, U>(param1, param2) {}
};






class Card
{
public:
    enum CardSuit { HEARTS, DIAMONDS, SPADES, CLUBS };
    enum CardValue { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, KING = 10, QUEEN = 10, JACK = 10 };
    
    Card(CardValue v, CardSuit s, bool f) : m_currentValue(v), m_currentSuit(s), m_situation(f) {}
    
    void Flip()
    {
        m_situation = !(m_situation);
    }
    
    int GetValue() const
    {
        int value = 0;
        if (m_situation)
        {
            value = m_currentValue;
            if (value > 10)
            {
                value = 10;
            }
                    
        }
        return value;
    }
    
private:
    CardSuit m_currentSuit;
    CardValue m_currentValue;
    bool m_situation;
};


class Hand
{
protected:
    vector<Card*> m_Cards;
public:
    Hand()
    {
        m_Cards.reserve(7);
    }
    
    virtual ~Hand()
    {
        Clear();
    }
    
    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }
    
    void Clear()
    {
        vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete *iter;
            *iter = 0;
        }
        m_Cards.clear();
    }
    
    int GetTotal() const
    {
        if (m_Cards.empty())
        {
            return 0;
        }
        
        if (m_Cards[0]->GetValue() == 0)
        {
            return 0;
        }
        
        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            total += (*iter)->GetValue();
        }
        
        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            if ((*iter)->GetValue() == Card::ACE)
            {
                containsAce = true;
            }
        }
        
        if (containsAce && total <= 11)
        {
            total += 10;
        }
        
        return total;
    }
};


class GenericPlayer : public Hand
{
protected:
    string m_Name;
    
public:
    GenericPlayer(const string& name = ""): m_Name(name) { }
    
    virtual ~GenericPlayer() { }
    
    virtual bool IsHitting() const = 0;
    
    bool IsBusted() const
    {
        return (GetTotal() > 21);
    }
    
    void Bust() const
    {
        cout << m_Name << " busts.\n";
    }
    
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
};

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";
    
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
             pCard != aGenericPlayer.m_Cards.end();
             ++pCard)
        {
            os << (*pCard) << "\t";
        }
        
        
        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    
    return os;
}

int main()
{
//    task 1
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

//    task 2
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

//    task 3
    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    
    
    return 0;


}
