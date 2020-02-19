#include "lesson6.hpp"

using namespace std;

// task 1
int get_int()
{
    int ret_integer;
    string str_number;

    while(true) {
        cout << "Enter an integer: ";
        getline(cin, str_number);
        stringstream convert(str_number);

        if(convert >> ret_integer && !(convert >> str_number)) return ret_integer;

        cin.clear();
        cerr << "Please try again.\n";
    }
}


// task 2
ostream& endll(ostream& stream)
{
    stream.setf(ios::left);
    stream << "\n\n";
    stream << flush;
    return stream;
}

// task 3, 4, 5
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
    
    friend ostream& operator<<(ostream& os, const Card& aCard);
    
private:
    CardSuit m_currentSuit;
    CardValue m_currentValue;
    bool m_situation;
};

//task 5
ostream& operator<<(ostream& os, const Card& aCard)
{
    if (!aCard.m_situation) {
        os << "XX" << endl;
    }
    else
    {
        os << "Suit: " << aCard.m_currentSuit << ", " << "Value: " << aCard.m_currentValue << endl;
    }
    return os;
}

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

// task 3
class Player : public GenericPlayer
{
public:
    Player(const string& name = "");
    
    virtual ~Player();
    
    virtual bool IsHitting() const
    {
        cout << m_Name << ", do you want a hit? (Y/N): ";
        char response;
        cin >> response;
        return (response == 'y' || response == 'Y');
    }
    
    void Win() const
    {
        cout << m_Name << " wins !!!\n";
    }
    
    void Lose() const
    {
        cout << m_Name << " loses ):\n";
    }
    
    void Push() const
    {
        cout << m_Name << " pushes.\n";
    }
};

// task 4
class House : public GenericPlayer
{
public:
    House(const string& name = "House");
    
    virtual ~House();
    
    virtual bool IsHitting() const
    {
        return (GetTotal() <= 16);
    }
    
    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
        {
            m_Cards[0]->Flip();
        }
        else
        {
            cout << "No card to flip!\n";
        }
    }
};


int main(int argc, char** args)
{
    // task 1
    int num = get_int();
    cout << "The integer entered is " << num << endl;
    
    // task 2
    cout << "endll" << endll;
    cout << "end" << endl;
    return 0;
} 
