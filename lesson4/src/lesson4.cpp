#include "lesson4.hpp"


using namespace std;

class ArrayInt {
private:
    int* m_data;
    int m_length;
    
    void swap(int* a, int* b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }
    
    int partition (int low, int high)
    {
        int pivot = m_data[high];
        int i = (low - 1);
      
        for (int j = low; j <= high - 1; j++)
        {
            if (m_data[j] < pivot)
            {
                i++;
                swap(&m_data[i], &m_data[j]);
            }
        }
        swap(&m_data[i + 1], &m_data[high]);
        return (i + 1);
    }
public:
    ArrayInt() : m_length(0), m_data(nullptr) { }
    ArrayInt(int length): m_length(length)
    {
        assert(length >= 0);
        if (length > 0) {
            m_data = new int[length];
        }
        else {
            m_data = nullptr;
        }
    }
    
    ~ArrayInt()
    {
        delete [] m_data;
    }
    
    void erase()
    {
        delete [] m_data;
        m_length = 0;
    }
    
    int getLength() const
    {
        return m_length;
    }
    
    int& operator[] (int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    
    void resize(int newLength)
    {
        if (newLength == m_length)
            return;
        
        if (newLength <= 0)
        {
            erase();
            return;
        }
        
        int *data = new int[newLength];
        
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
            
            delete [] m_data;
            
            m_data = data;
            m_length = newLength;
        }
    }
    
    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        
        int *data = new int[m_length + 1];
        
        for (int before = 0; before < index; ++before)
        {
            data[before] = m_data[before];
        }
            
        data[index] = value;
        
        for (int after = index; after < m_length; ++after)
        {
            data[after+1] = m_data[after];
        }
        
        delete [] m_data;
        
        m_data = data;
        ++m_length;
    }
    
    void push_back(int value) {
        insertBefore(value, m_length); }
    
    void push_rand(int value)
    {
        int randIndex = 0;
        if (m_length > 0)
            randIndex = rand() % m_length;
        else
            randIndex = 0;
        insertBefore(value, randIndex);
    }
    
    
    
    void pop_back()
    {
        int* data = new int[m_length-1];
        
        for (int index = 0; index < m_length - 1; ++index)
            data[index] = m_data[index];
        
        delete [] m_data;
        
        m_data = data;
        --m_length;
    }
    
    
    void sort()
    {
        int high = m_length - 1;
        int low = 0;
        
        int stack[high - low + 1];
        
        int top = -1;
        
        stack[++top] = low;
        stack[++top] = high;
        
        while (top >= 0) {
            high = stack[top--];
            low = stack[top--];
            
            int p = partition(low, high);
        
            if (p - 1 > low) {
                stack[++top] = low;
                stack[++top] = p - 1;
            }
        
            if (p + 1 < high) {
                stack[++top] = p + 1;
                stack[++top] = high;
            }
            
          }
    }
};

void mergeSort(vector<int>&left, vector<int>& right, vector<int>& bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

void sort(vector<int> & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, bar);
}


enum CardSuit { HEARTS, DIAMONDS, SPADES, CLUBS };
enum CardValue { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, KING = 10, QUEEN = 10, JACK = 10 };
class Card
{
private:
    CardSuit currentSuit;
    CardValue currentValue;
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
    
    int GetValue() const
    {
        return currentValue;
    }
};


//task 3
class Hand
{
private:
    vector<Card*> m_cards;
public:
    Hand(vector<Card*> cards): m_cards(cards) { }
    
    void Add(Card* n)
    {
        m_cards.push_back(n);
    }
    
    void Clear()
    {
        m_cards.clear();
    }
    
    int GetTotal()
    {
        
        int summ = 0;
        for (int i = 0; i < m_cards.size(); ++i)
        {
            if (m_cards[i]->GetValue() == 1 && summ <= 10) {
                summ += 11;
            } else {
                summ += m_cards[i]->GetValue();
            }
        }
        return summ;
    }
    
};

//task 4

class Converter {
private:
    vector<int> m_arr;
    int iriginal;
public:

    Converter(vector<int> arr, int original): m_arr(arr), iriginal(original) { }
    
    int nextNumber(int final){
        int temp = 0;
        for ( int i = 0; i<this->m_arr.size(); i++){
            temp = temp*this->iriginal + this->m_arr[i];
            m_arr[i] = temp / final;
            temp = temp % final;
        }
        return temp;
    }
    bool zero(){
        for ( int i=0; i<this->m_arr.size(); i++ ){
            if (this->m_arr[i] != 0 ){
                return false;
            }
        }
        return true;
    }
    vector<int> convertTo(int final){
        vector<int> b;
        int size = 0;
        do {
            b.push_back(this->nextNumber(final));
            size++;
        } while( !this->zero() );
        return b;
    }
};

vector<int> der(const vector<int> &A, int baseA, const vector<int> &B, int baseB, int baseResult)
{
    vector<int> C = A;
    vector<int> D = B;
    vector<int> E;
    Converter conv(C, baseA);
        
    C = conv.convertTo(10);
    
    Converter conv1(D, baseB);
    
    D = conv1.convertTo(10);
    
    if (C.size() < D.size())
    {
        C.resize(D.size());
        E.resize(D.size());
    } else {
        D.resize(A.size());
        E.resize(A.size());
    }
    
    for (int i = D.size() - 1; i >= 0; --i)
    {
        E[i] = C[i] + D[i];
        if ((C[i] + D[i]) >= 10) {
            string ch = to_string(C[i] + D[i]);
            E[i] = ch[1] - '0';
            E[i+1] += ch[0] - '0';
        }
    }
    
    string result = "";
    for (int i = E.size() - 1; i >= 0; --i)
    {
        result += to_string(E[i]);
    }
    
    int resultInt = stoi(result);
    E.clear();
    E.push_back(resultInt);
    Converter conv3(E, 10);

    E = conv3.convertTo(baseResult);

    return E;
}

int main(int argc, char** args) 
{
    //task 1
    ArrayInt a;
    a.push_back(12);
    a.push_back(15);
    a.push_back(14);
    a.push_back(18);
    a.push_back(1);
    a.push_rand(2);
    
    for (int i = 0; i < a.getLength(); ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Removal of the last element: ";
    a.pop_back();
    for (int i = 0; i < a.getLength(); ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << endl;
    a.sort();
    cout << "Sorted array: ";
    for (int i = 0; i < a.getLength(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    
    //task2
    vector<int> arr;
    
    int n;
    cout << "Enter the numbers(): ";
    do {
        cin >> n;
        if (arr.size() >= 5) {
            arr.resize(arr.size() + 1);
        }
        arr.push_back(n);
    } while (n != 0);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    sort(arr);
    int numberOfDifferent = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] != arr[i + 1]) {
            numberOfDifferent++;
        }
    }
    cout << numberOfDifferent << endl;
    cout << endl;
    
    
    
    // task 4
    vector<int> ar1;
    vector<int> ar2;
    vector<int> e;
    
    
    ar1.push_back(15);
    ar1.push_back(15);
    
    ar2.push_back(17);
    ar2.push_back(14);
    ar2.push_back(21);
    ar2.push_back(21);
    ar2.push_back(24);
    
    e = der(ar1, 16, ar2, 36, 2);
    
    for (int i = e.size() - 1; i >= 0; --i)
        cout << e[i];
    
    cout << endl;
    return 0;
}



