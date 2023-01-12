// .cpp files contain code definitions for methods that have been declared
// in the according .hpp file. The skeleton has been set up here for you.
// That is, the methods have been initiated, and your mission, should you
// choose to accept it (which you should for marks), is to fill in each method
// with the appropriate code.
//
// A note about the "::" syntax: generally, this means "the thing on the right
// belongs to the thing on the left." So, SequentialList::empty() means the method
// empty() belongs to the class SequentialList. This allows empty() to access (and
// potentially change) the member variables in class SequentialList.
#include "SequentialList.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// This is the constructor.
SequentialList::SequentialList(unsigned int cap)
{
    // initialize the sequential list
    data_ = new DataType[cap];
    // set the capacity to the passed in capacity
    capacity_ = cap;
    // set the initial size of the list to zero
    size_ = 0;
}

SequentialList::~SequentialList()
{
    // dynamically freeing memory occupied by the sequential list
    delete[] data_;
    data_ = NULL;
}

bool SequentialList::empty() const
{
    // returns true if the size is zero, false otherwise
    if(size_==0){
        return true;
    }
    return false;
}

unsigned int SequentialList::size() const
{
    // return the size of the list
    return size_;
}

unsigned int SequentialList::capacity() const
{
    // return the maximum allocated capacity of the list
    return capacity_;
}

bool SequentialList::full() const
{
    // if the size of the list is equal to the maximum capacity it will return true, and false otherwise
    if(size_==capacity_){
        return 1;
    }
    return 0;
}

void SequentialList::print() const
{
    // print the first bracket of the list
    cout << "(" ;
    // iterate through each element of the sequential list
    for(int index=0; index < size_; index++){
        // output the value
        cout << data_[index];
        // if there is another value print a comma
        if(size_-index>1){
            cout << ", ";
        }
    }
    // print the closing bracket
    cout << ")" << endl;
    
}

// NOTE on inserts: do NOT grow the array if we reach capacity. Simply return false.
bool SequentialList::insert_front(DataType val)
{
    // only insert if the list is not at capacity
    if(!full()){
        // call the insert method to handle the insertion at the 0th index
        return insert(val, 0);
    }
    // otherwise return false
    return 0;
    
}

bool SequentialList::remove_front()
{
    // call the remove method to handle removing the first
    return remove(0);
}

bool SequentialList::insert_back(DataType val)
{
    // only insert if the list is not at capacity
    if(!full()){
        // the list is not full so the value can be added to the back
        data_[size_] = val;
        // increase the size of the list
        size_++;
        return 1;
    }
    // the list is full so return false
    return 0;
    
    
}

bool SequentialList::remove_back()
{
    // if the list is empty return false as there is nothing to remove
    if(empty()){
        return 0;
    }
    // the list is not empty so 'remove' the last value by decreasing the size
    size_--;
    // the value was successfully removed
    return 1;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    
    // if the specified index is within the size of the list and the list is not at max capacity
    if (index <= size_&&!full()) {
        // start at the end of the list and shift each value to the right one until there is a space at the index
        for (int ind = size_; ind > index; ind--){
            // shifting values to the right
            data_[ind] = data_[ind-1];
        }
        // inserting the value at the specified index
        data_[index] = val;
        // increase the size of the list
        size_++;
        // return that the value was successfully inserted
        return 1;
    }
    // the value cannot be inserted at the specified index
    return 0;
}

bool SequentialList::remove(unsigned int index)
{
    // if the index is in the bounds of the list with actual values
    if(index<size_){
        // iterate through every element after the value being removed at the given index
        for (int count=index; count<size_; count++){
            // shift each value to the left one to fill the gap of the removed value at the specified index
            data_[index] = data_[index+1];
        }
        // decrease the size of the list
        size_--;
        // the value was successfully removed
        return 1;
    }
    return 0;
}

unsigned int SequentialList::search(DataType val) const
{
    // iterate through the entire list until the value is found
    for (int index=0; index < size_; index++) {
        // if the value at the current index is the desired value
        if (data_[index] == val) {
            // return the index of the target value
            return index;
        }
    }
    // return the size of the list if the desired value is not present
    return size_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    // if the specified index contains 'real' values return the value at the specified index
    if (index < size_){
        return data_[index];
    }
    // returns the last element of the list
    return data_[size_-1];
    
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    // if the index is in the size of the list and it is a valid index (non negative)
    if(index < size_){
        // replace the value
        data_[index] = val;
        // successfully replaced the value
        return 1;
    }
    // the value was not successfully replaced
    return 0;
}
