//
//  Proj2.cpp
//  
//
//  Created by Gabriel Miller on 5/6/18.
//  A set of functions to execute QuickSort, BinarySearch, MergeSort, a hashing function, and a Bloom Filter. All applicable functions are overloaded for strings and numbers.

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;


// QUICKSORT overloaded for strings and numbers
void QuickSort(vector<double>& vec, int bot, int top)
{
    if (!vec.empty())
    {
        if (top > bot)
        {
            double pivot = vec[((top-bot)/2)+bot];
            double temp;
            int left = bot;
            int right = top;
            while (left <= right)
            {
                while (vec[left] < pivot)
                {
                    left++;
                }
                while (vec[right] > pivot)
                {
                    right--;
                }
                if (left <= right)
                {
                    temp = vec[left];
                    vec[left] = vec[right];
                    vec[right] = temp;
                    left++;
                    right--;
                }
            }
            QuickSort(vec, bot, right);
            QuickSort(vec, left, top);
        }
    }
    return;
}

void QuickSort(double arr[], int bot, int top)
{
    if (top > bot)
    {
        double pivot = arr[((top-bot)/2)+bot];
        double temp;
        int left = bot;
        int right = top;
        while (left <= right)
        {
            while (arr[left] < pivot)
            {
                left++;
            }
            while (arr[right] > pivot)
            {
                right--;
            }
            if (left <= right)
            {
                temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
                left++;
                right--;
            }
        }
        QuickSort(arr, bot, right);
        QuickSort(arr, left, top);
    }
    return;
}


// BINARY SEARCH overloaded for strings and numbers
int BinarySearch(vector<double>& vec, int bot, int top, int x)
{
    if (top >= bot)
    {
        int mid = bot + (top - bot)/2;
        if (vec[mid] == x)
        {
            return mid;
        }
        if (vec[mid] > x)
        {
            return BinarySearch(vec, bot, mid-1, x);
        }
        else
        {
            return BinarySearch(vec, mid+1, top, x);
        }
    }
    return -1;
}

int BinarySearch(double arr[], int bot, int top, int x)
{
    if (top >= bot)
    {
        int mid = bot + (top - bot)/2;
        if (arr[mid] == x)
        {
            return mid;
        }
        if (arr[mid] > x)
        {
            return BinarySearch(arr, bot, mid-1, x);
        }
        else
        {
            return BinarySearch(arr, mid+1, top, x);
        }
    }
    return -1;
}


// MERGE SORT overloaded for strings and numbers
void MergeSort(vector<double>& vec, int bot, int top)
{
    if (bot < top)
    {
        int mid = bot + (top-bot)/2;
        MergeSort(vec,bot,mid);
        MergeSort(vec,mid+1,top);
        int i; int j; int k;
        int n1 = mid - bot + 1;
        int n2 = top - mid;

        vector<double> L;
        vector<double> R;
        for (i = 0; i < n1; i++)
            L.push_back(vec[bot + i]);
        for (j = 0; j < n2; j++)
            R.push_back(vec[mid + 1+ j]);

        i = 0;
        j = 0;
        k = bot;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                vec[k] = L[i];
                i++;
            }
            else
            {
                vec[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            vec[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2)
        {
            vec[k] = R[j];
            j++;
            k++;
        }
    }
    return;
}

void MergeSort(double arr[], int bot, int top)
{
    if (bot < top)
    {
        int mid = bot + (top-bot)/2;
        MergeSort(arr,bot,mid);
        MergeSort(arr,mid+1,top);
        
        int i; int j; int k;
        int n1 = mid - bot + 1;
        int n2 = top - mid;
        
        double L[n1];
        double R[n2];
        for (i = 0; i < n1; i++)
            L[i] = arr[bot + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1+ j];
        
        i = 0;
        j = 0;
        k = bot;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    return;
}


// GOOF HASH overloaded for strings and numbers
unsigned int GoofHash(const string& str)
{
    unsigned int b    = 1234;
    unsigned int a    = 6789;
    unsigned int hash = 0;
    
    for(size_t i = str.length()-3; i < str.length(); i++)
    {
        hash = hash * a + str[i];
        a = a * b;
    }
    return hash;
}

unsigned int GoofHash(const int& num)
{
    string str = to_string(num);
    unsigned int b    = 1234;
    unsigned int a    = 6789;
    unsigned int hash = 0;
    
    for(size_t i = str.length()-3; i < str.length(); i++)
    {
        hash = hash * a + str[i];
        a = a * b;
    }
    return hash;
}


// BLOOM FILTER
struct BloomFilter
{
    BloomFilter(unsigned int size, unsigned int numHashes);
    void BloomAdd(unsigned int data);
    void BloomAdd(string data);
    bool BloomContains(unsigned int data) const;
    bool BloomContains(string data) const;
private:
    unsigned int m_numHashes;
    vector<bool> m_bits;
    unsigned int elements;
};

//Constructor
BloomFilter::BloomFilter(unsigned int size, unsigned int numHashes) : m_numHashes(numHashes),m_bits(size),elements(0) {}

// Hashing function using GoofHash n times
unsigned int nthHash(int n, const int& data)
{
    unsigned int hashVal;
    if (n > 0)
    {
        hashVal = GoofHash(data);
        return nthHash(n-1,hashVal);
    }
    else
    {
        return GoofHash(data);
    }
}

// Same function but for strings instead of numbers
unsigned int nthHash(int n, const string& data)
{
    unsigned int hashVal;
    if (n > 0)
    {
        hashVal = GoofHash(data);
        return nthHash(n-1,hashVal);
    }
    else
    {
        return GoofHash(data);
    }
}

//Add function for numbers
void BloomFilter::BloomAdd(unsigned int data)
{
    for (int n = 0; n < m_numHashes; n++)
    {
        m_bits[(nthHash(n,data))%m_bits.size()] = true;
    }
    elements++;
}

//Add function for strings
void BloomFilter::BloomAdd(string data)
{
    for (int n = 0; n < m_numHashes; n++)
    {
        m_bits[(nthHash(n,data))%m_bits.size()] = true;
    }
    elements++;
}

//Contains function for strings
bool BloomFilter::BloomContains(string data) const
{
    for (int n = 0; n < m_numHashes; n++)
    {
        if (!m_bits[(nthHash(n,data))%m_bits.size()])
        {
            cout << "The filter does not contain " << data << "." << endl;
            return false;
        }
    }
    cout << "The filter might contain " << data << "!" << endl;
    return true;
}

//Contains function for numbers
bool BloomFilter::BloomContains(unsigned int data) const
{
    for (int n = 0; n < m_numHashes; n++)
    {
        if (!m_bits[(nthHash(n,data))%m_bits.size()])
        {
            cout << "The filter does not contain " << data << "." << endl;
            return false;
        }
    }
    cout << "The filter might contain " << data << "!" << endl;
    return true;
}

int main()
{
    //QuickSort vector
    vector<double> vec1;
    double entry;
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter a number: ";
        cin >> entry;
        vec1.push_back(entry);
    }
    QuickSort(vec1,0,9);
    for (int i = 0; i < 10; i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl << endl;
    
    //QuickSort Array
    double arr1[10];
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter a number: ";
        cin >> entry;
        arr1[i] = entry;
    }
    QuickSort(arr1,0,9);
    for (int i = 0; i < 10; i++)
    {
        cout << arr1[i] << " ";
    }
    cout << endl << endl;
    
    //BinarySearch vector
    int x = 2;
    int index = BinarySearch(vec1,0,9,x);
    if (index == -1)
    {
        cout << "Number not found!" << endl;
    }
    else
    {
        cout << "Number: " << x << endl << "Index: " << index << endl << endl;
    }
    
    //BinarySearch array
    x = 7;
    index = BinarySearch(arr1,0,9,x);
    if (index == -1)
    {
        cout << "Number not found!" << endl;
    }
    else
    {
        cout << "Number: " << x << endl << "Index: " << index << endl << endl;
    }
    
    //MergeSort vector
    vector<double> vec2;
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter a number: ";
        cin >> entry;
        vec2.push_back(entry);
    }
    MergeSort(vec2,0,9);
    for (int i = 0; i < 10; i++)
    {
        cout << vec2[i] << " ";
    }
    cout << endl << endl;
    
    //MergeSort Array
    double arr2[10];
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter a number: ";
        cin >> entry;
        arr2[i] = entry;
    }
    MergeSort(arr2,0,9);
    for (int i = 0; i < 10; i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl << endl;
    
    //Hashing Function
    string str = "This is a hashing test";
    cout << "Hash of 'This is a hashing test': " << GoofHash(str) << endl;
    int num = 123456789;
    cout << "Hash of '123456789': " << GoofHash(num) << endl;
    
    //Bloom Filter
    BloomFilter testFilter(12,13);
    testFilter.BloomAdd("Testing");
    testFilter.BloomContains("Testing");
    testFilter.BloomContains("What");
    testFilter.BloomAdd("What");
    testFilter.BloomContains("What");
    testFilter.BloomContains("Where");
    return 0;
}
