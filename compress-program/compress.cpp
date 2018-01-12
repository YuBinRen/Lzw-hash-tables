//
//  main.cpp
//  Ziv-Lempel
//
//  Created by Bahadır on 27.11.2017.
//  Copyright © 2017 Bahadir. All rights reserved.
//
// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// HashedObj key(const int &x) --> Returns the value stored in index x
// int returnPos(const HashedObj & x) --> Returns the index of given value. If value is not contained, it will still return the index of it as if it is contained.
// void printArray()      --> prints the hashTable array
// void printArraySize()  --> Size of the array
// int hashCode( string str ) --> Global method to hash strings


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LinearProbing.hpp"
using namespace std;

vector<int> ziv_lampel_compress(string &str, HashTable<string> &myHash) {
    
    vector<int> vec;
    string prefix = str.substr(0,1); // start with the first char
    
    // Longest prefix
    int pos = 0;
    while(!myHash.contains(str))
    {
        // Follow the algorithm given in the pdf.
        for ( ; pos < str.length() && myHash.contains(prefix); pos++)
        {
            if(pos > 0)
                prefix = str.substr(0,pos+1);
        }
       
        vec.push_back(myHash.returnPos(str.substr(0,pos-1)));
        string s = str.substr(0,pos);
        myHash.insert(s);
        str = str.substr(pos-1);
        pos = 0;
    }
    
    vec.push_back(myHash.returnPos(str));
    
    return vec;
}


int main()
{
    // Take input from compin.txt
    
    ifstream f("compin");
    string str(istreambuf_iterator<char>(f), (std::istreambuf_iterator<char>()));
    HashTable<string> myHash;
    
    for (int i = 0; i < 256; i++)
    {
        char c = i;
        string s(1, c);
        myHash.insert(s);
    }
    
    // COMPRESSION
    vector<int> compressed;
    compressed = ziv_lampel_compress(str, myHash); // compressed data
    
    fstream of("compout", ios::out | ios::trunc);
    string output = "";
    cout << "Compression completed"<< endl;
    for (int i = 0;  i < compressed.size(); i++) {
        output += to_string(compressed[i]) + " ";
        cout << compressed[i] << " ";
    }
    cout << endl;
    of << output;
    of.close();
    f.close();
    
    return 0;
}










