//
//  LinearProbing.hpp
//  Ziv-Lempel
//
//  Created by Bahadır on 2.12.2017.
//  Copyright © 2017 Bahadir. All rights reserved.
//

#ifndef LinearProbing_hpp
#define LinearProbing_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cmath>
using namespace std;

// LinearProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 100
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings


template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable( int size = 4096 ) : arr( size )
    { makeEmpty( ); }
    
    
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }
    
    
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : arr )
            entry.info = EMPTY;
    }
    
    
    bool insert( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        if( arr[ currentPos ].info != DELETED )
            ++currentSize;
        
        arr[ currentPos ].element = x;
        arr[ currentPos ].info = ACTIVE;
        
        if( currentSize >= arr.size())
            rehash();
        
        return true;
    }
    
    
    bool insert( HashedObj && x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        if( arr[ currentPos ].info != DELETED )
            ++currentSize;
        
        arr[ currentPos ] = std::move( x );
        arr[ currentPos ].info = ACTIVE;
        
        if( currentSize >= arr.size())
            rehash( );
        
        return true;
    }
    
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        
        arr[ currentPos ].info = DELETED;
        return true;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
    
    int returnPos(const HashedObj & x)
    {
        return findPos(x);
    }
    
    
    int returnArraySize()
    {
        return arr.size();
    }
    
    void printArray()
    {
        for (int i = 0; i < arr.size(); i++)
        {
            cout << i << " : " << arr[i].element << endl;
        }
    }
    
    bool is_index_active(const int &x){
        return arr[x].info == ACTIVE;
    }
    
    HashedObj key(const int &x)
    {
        return arr[x].element;
    }
    
    
    bool operator== (HashTable const &obj) const
    {
        return this->arr == obj.arr;
    }
    
    bool operator!= (HashTable const &obj) const
    {
        return this->arr != obj.arr;
    }
    
private:
    // hash entry object
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        
        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
        : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
        : element{ std::move( e ) }, info{ i } { }
        
        bool operator== (HashEntry const &obj) const
        {
            return this->element == obj.element;
        }
        
        bool operator!= (HashEntry const &obj) const
        {
            return this->element != obj.element;
        }
        
    };
    
    vector<HashEntry> arr; // our precious array
    int currentSize;
    
    bool isActive( int currentPos ) const
    { return arr[ currentPos ].info == ACTIVE; }
    
    int findPos( const HashedObj & x ) const {
        //int offset = 1;
        int currentPos = myhash(x);
        while( arr[ currentPos ].info != EMPTY && arr[ currentPos ].element != x )
        {
            currentPos ++;  // Compute ith probe
            //offset += 2;
            if( currentPos >= arr.size( ) )
                currentPos -= arr.size( );
        }
        
        return currentPos;
    }
    
    
    void rehash()
    {
        vector<HashEntry> oldArray = arr;
        
        // Create new double-sized, empty table
        arr.resize(2 * oldArray.size());
        for( auto & entry : arr )
            entry.info = EMPTY;
        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }
    
    
    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % arr.size( );
    }
};

#endif /* LinearProbing_hpp */
