#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long lop[5] = {0,0,0,0,0};
        std::string temp = k;

            for (int j = 4; j >= 0; j--) // go through lop
            {
                int sizeN = temp.size();
                for(int i = sizeN-1; i >= 0; i--)
                {
                    if(i < 6 && i < temp.size()){
                        lop[j] = lop[j] + letterDigitToNumber(temp[abs(i - temp.size()+1)])*pow(36,i);
                    }
                }
                size_t i = 0;
                while(i<6){
                    if (!(temp.size() == 0))
                    {
                        temp.pop_back(); // pop back the last 6 of these here
                    }
                    i++;
                }
            }
        HASH_INDEX_T fnumber = 0;
        for(size_t k = 0; k < 5; k++)
        {
            fnumber = fnumber + (rValues[k]*lop[k]);
        }
        return fnumber;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int n = 0;
        if ( letter > 64 && letter < 91 ) { //if uppercase, change to lowercase
            letter += 32;
        }
        if ( letter >= 47 && letter < 58 ) { //if number, change to corresponding digit
            n = letter - 22;
        }
        else if ( letter > 96 && letter < 123 ) {
            n = letter - 97;
        }
        return n;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
