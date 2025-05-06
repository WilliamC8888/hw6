#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
//final push
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
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        int len = k.length();
        int numGroups = (len + 5) / 6; //+5 so last group wont get rounded down
        for (int i = 0; i < numGroups; i++) {
            int groupLen = 6;
            int start = len - (i + 1) * 6;
            if (start < 0) {
                groupLen += start; // trim extra chars on the left
                start = 0;
            }
            unsigned long long value = 0;
            for (int j = 0; j < groupLen; j++) {
                char c = k[start + j];
                HASH_INDEX_T digit = letterDigitToNumber(c);
                value = value * 36 + digit;
            }
            w[i] = value;
        }

        HASH_INDEX_T hash = 0;
        for (int k = 0; k < 5; k++){
            hash += (HASH_INDEX_T)(rValues[4 - k] * w[k]);
        }
        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'A' && letter<='Z'){
            letter = letter + ('a'-'A'); //may need to reverse As double check
        }
        if (letter >= 'a' && letter<='z'){
            return letter - 'a'; //maps 0-25
        }
        if (letter >= '0'&& letter<='9'){
           // char temp = letter - '0';
            return (letter- '0') + 26;
        }
        return 0;
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
