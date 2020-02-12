#include "lesson7.hpp"

using namespace std;

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int day, int month, int year) {
        if (day >= 1) m_day = day;
        if (month > 0 && month <= 12) m_month = month;
        m_year = year;
    }
    
    Date() {
        
    }
    
    virtual ~Date () {}
    
    int GetDay() const
    {
        return m_day;
    }
    
    int GetMonth() const
    {
        return m_month;
    }
    
    int GetYear() const
    {
        return m_year;
    }
    
    
    friend ostream& operator<<(ostream& os, Date& aDate);
};


ostream& operator<<(ostream& os, Date& aDate)
{
    os << "Date: " << aDate.GetDay() << "-" << aDate.GetMonth() << "-" << aDate.GetYear() << endl;
    return os;
}


//task 2
bool operator>(Date d1, Date d2)
{
    if (d1.GetYear() > d2.GetYear())
        return true;
    else if (d1.GetYear() < d2.GetYear()) {
        return false;
    }
    if (d1.GetMonth() > d2.GetMonth())
        return true;
    else if (d1.GetMonth() < d2.GetMonth()) {
        return false;
    }
    if (d1.GetDay() > d2.GetDay())
               return true;
    return false;
}

Date& isEqualDate(unique_ptr<Date>& d1, unique_ptr<Date>& d2)
{
    return (d1 > d2 ? *d1 : *d2);
}

void swap_ptr(unique_ptr<Date> d1, unique_ptr<Date> d2)
{
    unique_ptr<Date> temp;
    temp = move(d1);
    d1 = move(d2);
    d2 = move(temp);
    cout << "date1:\n\t" << *d1 << "date2:\n\t" << *d2;
}



// taask 3, 4 in blackjack folder in another project
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
    
//    task 1
    unique_ptr<Date> today(new Date(12, 2, 2020));
    
    cout << "Today is " << today->GetDay() << "." << today->GetMonth() << "." << today->GetYear() << endl;
    
    cout << *today;
    
    unique_ptr<Date> date;
    
    date = move(today);
    
    if (today) cout << "today is not null" << endl;
    else cout << "today is null" << endl;
    if (date) cout << "date is not null" << endl;
    else cout << "date is null" << endl;
    
//    task 2
    unique_ptr<Date> date1(new Date(12, 3, 2020));
    unique_ptr<Date> date2(new Date(11, 4, 2020));
    
    cout << isEqualDate(date1, date2);
    swap_ptr(move(date1), move(date2));
    
    
    
    return 0;
} 
