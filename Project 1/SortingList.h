/* File: SortingList.h
 * Course: CS216-00x
 * Project: Lab12 (as the second part of Proejct 3)
 * Purpose: the declaration for the SortingList class.
 *          it stores a sequence of Building objects to perform sorting operation
 *          it will be modified into a template class
 *
 */

#ifndef SORTINGLIST_H
#define	SORTINGLIST_H

#include <vector>
#include <string>

using namespace std;

template <class T>
class SortingList
{
   public:
    // inserts the newbuilding to the end of the current vector   

    void insert(T newItem);

    // return how many items in the list
    int size();

    // operator overloading for "[]"
    // provide the direct access by index number
    T& operator[](int index);

    // sort all items in ascending order 
    // the items are compared using operator "<"
    // using sort() from standard library
    void sort();

    // provide different sorting algorithms 
    // based on comparison defined by the function passing in as parameter
    
    // apply selection sorting algorithm
    void selection_sort(int (*compare)(const T& b1, const T& b2));

    // apply bubble sorting algorithm
    void bubble_sort(int (*compare)(const T& b1, const T& b2));

    // apply merge sorting algorithm
    void merge_sort(int (*compare)(const T& b1, const T& b2));

    // apply shuffle algorithm
    void shuffle();

    // display all the items in the sequence
    void print();
    
   private:
    vector<T> items;

    // helper functions
    void merge(int first, int mid, int last, int (*compare)(const T& b1, const T& b2));
    void merge_sortHelper(int min, int max, int (*compare)(const T& b1, const T& b2));
};


#endif	/* SORTINGLIST_H */
#include "SortingList.cpp"
