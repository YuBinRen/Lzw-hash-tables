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
// bool is_index_active( x ) --> returns true if index active.
// void makeEmpty( )      --> Remove all items
// HashedObj key(const int &x) --> Returns the value stored in index x
// int returnPos(const HashedObj & x) --> Returns the index of given value. 
//                                        If value is not contained, 
//                                        it will still return the index of it as if it is contained.
// void printArray()      --> prints the hashTable array
// void printArraySize()  --> Size of the array
// int hashCode( string str ) --> Global method to hash strings


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LinearProbing.hpp"
using namespace std;



string decompress(HashTable<string> & myHash, vector<int> compressed_vec) {
    string str = "";
    string newbe;
    str += myHash.key(compressed_vec[0]);
    
    for (int i = 1; i < compressed_vec.size(); i++){
        if (myHash.is_index_active(compressed_vec[i])) {
            str += myHash.key(compressed_vec[i]);
            newbe = myHash.key(compressed_vec[i-1]) + myHash.key(compressed_vec[i])[0];
            myHash.insert(newbe);
        }
        else {
            newbe = myHash.key(compressed_vec[i-1]) + myHash.key(compressed_vec[i-1])[0];
            str += newbe;
            myHash.insert(newbe);
        }
    }
    
    return str;
}


int main() {
    
    ifstream f("compout");
    //string str(istreambuf_iterator<char>(f), (std::istreambuf_iterator<char>()));
    
    vector<int> compressed_vec;
    string str;
    while (f >> str) {
        int i = atoi(str.c_str());
        compressed_vec.push_back(i);
    }
    
    HashTable<string> myHash;
    
    for (int i = 0; i < 256; i++)
    {
        char c = i;
        string s(1, c);
        myHash.insert(s);
    }
    
    
    // Decompression starts...
    
    string decomp = decompress(myHash, compressed_vec);
    fstream of("decompout");
    
    of << decomp;
    
    
    return 0;
}












