// Example program
#include <iostream>
#include <string>
#include <algorithm> // for sort()
//#include <array>
//#include <iterator> // for std::begin, std::end

using namespace std;

int algoNumber = 1;

void algo1(pair<int, int> *pairs, int sortedSize)
{
    // 2  5  9  12 16 40 42 43 46 50 --- pairs.first
    // 1  2  3  4  5  6  7  8  9  10 --- pairs.second
    // 1  1  2  2  3  3  4  4  5  5  --- frets (GRYBO)
    
    for (int i = 0; i < sortedSize; ++i) {
        double res = (double) pairs[i].second * 5 / sortedSize;
        pairs[i].second = (int) ceil(res);
        
        //std::cout << pairs[i].first << " " << pairs[i].second << endl;
    }    
}

void algo2(pair<int, int> *pairs, int sortedSize)
{
    // 2  5  9  12 16 40 42 43 46 50 --- pairs.first
    // 1  2  3  4  5  6  7  8  9  10 --- pairs.second
    // 1  2  3  4  5  1  2  3  4  5  --- frets (GRYBO)
    
    for (int i = 0; i < sortedSize; ++i) {
        pairs[i].second = pairs[i].second % 5;
        if (pairs[i].second == 0)
        {
            pairs[i].second = 5;
        }
        
        //std::cout << pairs[i].first << " " << pairs[i].second << endl;
    }    
}

void printResults(int* order, int* frets, int size)
{
    // Reverse array to print last note first and make it look like a fretboard (first note at the bottom)   
    for (int i = size - 1; i >= 0; --i) { 
        std::cout << order[i] << "\t";
        
        int note = frets[i];
        
        for (int j = 1; j < 6; ++j) {
            if (j == note) {
                std::cout << "O";
            } else {
                std::cout << "-";
            }
        }
        std::cout << endl;
    }
}

void calculate(int* ints, int size)
{
    // Save noteArray
    int order[size];
    for(int i = 0; i < size; ++i) {
        order[i] = ints[i]; // copy the allocated memory 
    }
    
    // Sort noteArray
    sort(ints, ints + size);
    
    // Remove duplicates in the sorted array
    int sortedSize = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == size-1 || ints[i] != ints[i+1])
        {
            ints[sortedSize] = ints[i];
            sortedSize++;
        }
    }            
    
    // Reduce (= make pairs)
    pair<int, int> pairs[sortedSize];
    
    for (int i = 0; i < sortedSize; ++i) {
        pairs[i] = make_pair(ints[i], i + 1);
        
        //std::cout << pairs[i].first << " " << pairs[i].second << endl;
    }
    
    // Compute algo
    switch (algoNumber) {
        case 1:
            algo1(pairs, sortedSize);
            break;
        case 2:
            algo2(pairs, sortedSize);
            break;
        default:
            std::cout << "Wrong algo number, by default 1" << endl;
            algo1(pairs, sortedSize);
            break;        
    }    
    
    // Apply algo result to noteArray
    int frets[sortedSize];
    
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < sortedSize; ++j) {
            
            if (order[i] == pairs[j].first) {
                //std::cout << order[i] << " " << pairs[j].second << endl;
                frets[i] = pairs[j].second;
                break;
            }
        }
    }
    
    printResults(order, frets, size);
}

void test1()
{
    int myarray[] = { 2, 16, 77, 34, 50, 34, 2 };
    
    std::cout << "test1" << endl;
    int arraySize = sizeof(myarray) / sizeof(myarray[0]);
    
    calculate(myarray, arraySize);
}

void test2()
{
    int myarray[] = { 15, 4, 30, 20 };
    
    std::cout << "test2" << endl;
    int arraySize = sizeof(myarray) / sizeof(myarray[0]);
    
    calculate(myarray, arraySize);
}

void test3()
{
    int myarray[] = { 2, 16, 77, 34, 50, 34, 2, 3, 22 };
    
    std::cout << "test3" << endl;
    int arraySize = sizeof(myarray) / sizeof(myarray[0]);
    
    calculate(myarray, arraySize);
}

int main()
{
    std::cout << "Hello! Let's test algo number " << algoNumber << endl;
    test1();
    test2();
    test3();
}
