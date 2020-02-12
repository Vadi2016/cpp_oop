#include "Blackjack.hpp"

using namespace std;

class Card
{
public:
    enum CardSuit { HEARTS, DIAMONDS, SPADES, CLUBS };
    enum CardValue { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, KING = 10, QUEEN = 10, JACK = 10};
    
    Card(CardValue v, CardSuit s, bool f) : m_currentValue(v), m_currentSuit(s), m_situation(f) {}
    
    void Flip()
    {
        m_situation = !(m_situation);
    }
    
    int GetValue() const
    {
        int value = 0;
        if (!m_situation)
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
    
    CardSuit getSuit() const
    {
        return m_currentSuit;
    }
    
protected:
    CardSuit m_currentSuit;
    CardValue m_currentValue;
    bool m_situation;
};

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
            if ((*iter)->GetValue() == 1)
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
            os << **pCard << "\t";
        }
        
        if (aGenericPlayer.GetTotal() != 0)
        {
            os << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    
    return os;
}


class Player : public GenericPlayer
{
public:
    Player(const string& name = ""): GenericPlayer(name) {}
    
    virtual ~Player() {}
    
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
    
    // объявляет ничью
    void Push() const
    {
        cout << m_Name << " pushes.\n";
    }
};



class House : public GenericPlayer
{
public:
    House(const string& name = "House"): GenericPlayer(name) {}
    
    virtual ~House() {}
    
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


int myrandom (int i) { return std::rand()%i;}

class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    }
    
    virtual ~Deck() {}
    
    // создает стандартную колоду из 52 карт
    void Populate()
    {
    
        Clear();
        // создает стандартную колоду
        for (int s = 1; s <= 4; ++s)
        {
            for (int r = 1; r <= 14; ++r)
            {
                int temp_r = 10;
                if (r >= 10) {
                    Add(new Card(static_cast<Card::CardValue>(temp_r),
                    static_cast<Card::CardSuit>(s), false));
                } else {
                    Add(new Card(static_cast<Card::CardValue>(r),
                    static_cast<Card::CardSuit>(s), false));
                }
            }
        }
    }
    

 
    // тасует карты
    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end(), myrandom);
    }
    
    
    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
        {
            cout << "Out of cards. Unable to deal.";
        }
    }
    
    // дает дополнительные карты игроку
    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;
        // продолжает раздавать карты до тех пор, пока у игрока не случается
        // перебор или пока он хочет взять еще одну карту
        while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
        {
            srand(time(0));
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;
            
            if (aGenericPlayer.IsBusted())
            {
                aGenericPlayer.Bust();
            }
        }
    }
};


class Game
{
public:
    
    Game(const vector<string>& names)
    {
        // создает вектор игроков из вектора с именами
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }
        
        // запускает генератор случайных чисел
        std::srand(std::time(0));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }
    
    ~Game()
    {}
    
    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                
                m_Deck.Deal(*pPlayer);
                m_Deck.Shuffle();
                
            }
            m_Deck.Deal(m_House);
            m_Deck.Shuffle();
        }
        
        m_House.FlipFirstCard();
        
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            cout << *pPlayer << endl;
        }
        cout << m_House << endl;
        
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.AdditionalCards(*pPlayer);
            
        }
        
        m_House.FlipFirstCard();
        cout << endl << m_House;
        
        m_Deck.AdditionalCards(m_House);
        
        if (m_House.IsBusted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                {
                    pPlayer->Win();
                }
                      }
                    }
                    else
                    {
                        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
                             ++pPlayer)
                        {
                            if (!(pPlayer->IsBusted()))
                            {
                                if (pPlayer->GetTotal() > m_House.GetTotal())
                                {
                                    pPlayer->Win();
                                }
                                else if (pPlayer->GetTotal() < m_House.GetTotal())
                                {
                                    pPlayer->Lose();
                                }
                                else
                                {
                                    pPlayer->Push();
                                }
                            }
                        }
                        
                    }
                    
                    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
                    {
                        pPlayer->Clear();
                    
                    }
                    
        m_House.Clear();
                
    }
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};


int main(int argc, char** args)
{
    vector<string> names;
    string name = "";
    string answer = "";
    int count = 1;
    do {
        cout << "Enter name of " << count << " player: ";
        cin >> name;
        if (name != "end")
            names.push_back(name);
        count++;
    } while(name != "end");
    Game game(names);
    while (true) {
        cout << "You want to play a game?" << endl;
        cin >> answer;
        if (answer == "yes")
            game.Play();
        else if (answer == "no")
            break;
        else
            cout << "Pleas enter yes or no!" << endl;
    }
    return 0;
}
