// Example program
#include <iostream>
#include <string>
#include <algorithm> // for sort()
//#include <array>
//#include <iterator> // for std::begin, std::end

using namespace std;

void algo1(pair<int, int> *pairs, int size)
{
    // 2  5  9  12 16 40 42 43 46 50 --- pairs.first
    // 1  2  3  4  5  6  7  8  9  10 --- pairs.second
    // 1  1  2  2  3  3  4  4  5  5  --- frets (GRYBO)
    
    for (int i = 0; i < size; ++i) {
        pairs[i].second = pairs[i].second * 5 / size;
        //std::cout << pairs[i].first << " " << pairs[i].second << endl;
    }    
}

void algo2(pair<int, int> *pairs, int size)
{
    // 2  5  9  12 16 40 42 43 46 50 --- pairs.first
    // 1  2  3  4  5  6  7  8  9  10 --- pairs.second
    // 1  2  3  4  5  1  2  3  4  5  --- frets (GRYBO)
    
    for (int i = 0; i < size; ++i) {
        pairs[i].second = pairs[i].second % 5;
        if (pairs[i].second == 0)
        {
            pairs[i].second = 5;
        }
    }    
}

void printResults(int* ints, int size)
{
    std::cout << "FRETS" << endl;
    
    for (int i = 0; i < size; ++i) {
        std::cout << ints[i] << " ";
    }    
    
    std::cout << endl;
    std::cout << "RESULTS" << endl;
    
    // reverse array to print last note first and make it look like a fretboard    
    for (int i = size - 1; i >= 0; --i) { 
        int note = ints[i];
        
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
    // Trace
    for(int i = 0; i < size; ++i) {
        std::cout << ints[i] << ' ';
    }
    std::cout << endl;
    
    // Save noteArray
    int order[size];
    for(int i = 0; i < size; ++i) {
        order[i] = ints[i]; // copy the allocated memory 
    }
    
    // Sort noteArray
    // TODO remove duplicates
    sort(ints, ints + size);
    
    // Reduce (= make pairs)
    pair<int, int> pairs[size];
    
    for (int i = 0; i < size; ++i) {
        pairs[i] = make_pair(ints[i], i + 1);
        
        //std::cout << pairs[i].first << " " << pairs[i].second << endl;
    }
    
    // Compute algo
    algo2(pairs, size);
    
    // Apply algo result to noteArray
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            
            if (order[i] == pairs[j].first) {
                //std::cout << ints[i] << endl;
                order[i] = pairs[j].second;
                //std::cout << ints[i] << endl;
                break;
            }
        }
    }
    
    printResults(order, size);    
}

void test1()
{
    std::cout << "test1\n";
    int myarray[] = { 2, 16, 77, 34, 50 };
    calculate(myarray, 5);
}

void test2()
{
    std::cout << "test2\n";
    int myarray[] = { 15, 4, 30, 20 };
    calculate(myarray, 4);
}

int main()
{
    std::cout << "Hello!\n";
    test1();
}
