#include "DoublyLinkedList.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
DoublyLinkedList::Node::Node(DataType data)
{
    // set the data passed in to the value stored in the node
    value = data;
    // removes all links from the node
    next = NULL;
    prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
    // create an empty linked list that does not have a head or tail
    head_ = NULL;
    tail_ = NULL;
    // setting the list to be empty
    size_= 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    // if there are no nodes in the list return
    if(size_==0){
        return;
    }
    // begin at the end of the list
    Node* lastNode = tail_;
    // create a copy of the second last node
    Node* secondLastNode = tail_->prev;
    // while the node being examined exists
    while(lastNode!=NULL){
        // move the second last node to the node before the first node (note this will do nothing on the first iteration of the loop)
        secondLastNode = lastNode->prev;
        // delete the node
        delete lastNode;
        // move the node that is going to be deleted over to the left one
        lastNode = secondLastNode;
    }
}

bool DoublyLinkedList::empty() const
{
    // if there are no nodes in the list return the list is empty, and false otherwise
    if(size_==0)
        return true;
    return false;
}

unsigned int DoublyLinkedList::size() const
{
    // returning the size of the list
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    // return the max capacity of the list
    return CAPACITY;
}

void DoublyLinkedList::print() const
{
    // begin at the beginning of the list
    Node* print_last = head_;
    // print the first bracket
    cout << "(";
    // keep printing while the end of the list has not been reached
    while(print_last!=NULL){
        // print the value
        cout << "[" << print_last->value << "]";
        if(print_last->next!=NULL){
            // only print the comma if there is another value
            cout << "->";
        }
        // move to the next node
        print_last = print_last->next;
    }
    // print the closing bracket of the list
    cout << ")" << endl;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    // return the insert method at the 0th index
    return insert(value, 0);
}

bool DoublyLinkedList::remove_front()
{
    // return the remove method at the 0th index
    return remove(0);
}

bool DoublyLinkedList::insert_back(DataType value)
{
    // return the insert method at the back of the list
    return insert(value, size_);
}

bool DoublyLinkedList::remove_back()
{
    // return the remove method at the last index
    return remove(size_-1);
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    // if the list is not at capacity and a valid index is entered
    if (index <= size() && !full()) {
        Node* newNode = new Node(value);
        // if its an empty list assign head and tail to the new node
        if (empty()) {
            head_ = newNode;
            tail_ = newNode;
        }
        // if inserting at the beginning and the list isn't empty
        else if(index == 0){
            // link the new node to the first node in the list
            newNode->next = head_;
            // link the original first node to the new node being inserted at the front
            getNode(0)->prev = newNode;
            // set the first node to be the new node inserted at the front
            head_ = newNode;
        }
        // if inserting at the end
        else if(index == size_){
            // the list has one or more nodes
            // set the tail to be at this node
            tail_= newNode;
            // linking the last two elements together in a doubly manner
            getNode(size_-1)->next = newNode;
            newNode->prev = getNode(size_-1);
        }
        // we are inserting in the middle of a list with more than one element
        else{
            // set the previous node of the newNode to be whatever is in the list behind it at the specified index
            newNode->prev = getNode(index-1);
            // set the next node of the newNode to be the node at the specified index
            newNode->next = getNode(index);
            // set the next node of the node behind the newNode to be the newNode
            getNode(index-1)->next = newNode;
            // set the previous node of the node in front of the newNode to be the newNode
            getNode(index)->prev = newNode;
        }
        // increase the size of the list
        size_++;
        // the node was successfully added
        return 1;
    }
    // unable to add the node so return false
    return 0;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    // if a valid index is entered
    if (index < size_) {
        // if the list is empty do nothing
        if(size_==0){
            return 0;
        }
        // if there is one node in the list
        else if(size_ == 1){
            // delete the head
            delete head_;
            // remove the link with the one node
            head_ = NULL;
            tail_ = NULL;
        }
        // if the first node is to be removed
        else if (index == 0) {
            // there is more than one node in the list
            // delete the first node
            delete getNode(0);
            // remove the link from the second node to the first
            getNode(1)->prev = NULL;
            // make head point to the second node (making the second node the first)
            head_ = getNode(1);
        }
        // a node is to be removed to the back of the list
        else if (index == size_-1){
            // delete the last node and remove its links
            delete getNode(size_-2)->next;
            getNode(size_-2)->next = NULL;
            // there is more than one item in the list
            tail_ = getNode(size_-2);
        }
        // the list has more than 2 nodes and the node is being removed from the middle
        else{
            // delete the node to be removed
            delete getNode(index);
            // doubly link the node before and after the one deleted together
            getNode(index-1)->next = getNode(index)->next;
            getNode(index)->prev = getNode(index-1);
        }
        // decrease the size of the list
        size_--;
        // the node was successfully removed
        return 1;
    }
    // return false as an invalid index was entered
    return 0;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    // iterate through the linked list
    for(int count = 0; count < size_; count++){
        // if the value of the node at the current index is the desired value, return the index of the node
        if(getNode(count)->value == value){
            return count;
        }
    }
    // return the size of the list as the target value was not found
    return size_;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    // if the index is not in the range of the list
    if(index>size_){
        // return the value of the last node
        return getNode(size_)->value;
    }
    // return the value at the given index
    return getNode(index)->value;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    // if the index is in the range of the list
    if(index<size_){
        // set the value of the node at the index to be the value passed in
        getNode(index)->value = value;
        // the value of the node was replaced
        return 1;
    }
    // return false as a valid index was not entered
    return 0;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    // begin at the first node of the list
    Node* findNode = head_;
    // if the entered index is within the size of the list and it is non-negative
    if(index<size_){
        // iterate up to the index
        for(int count = 0; count < index; count++){
            // move the along to the next node
            findNode = findNode->next;
        }
        // return the node at the specified index
        return findNode;
    }
    // return null as there is no node at the specified index as the index is invalid
    return NULL;
}
bool DoublyLinkedList::full() const
{
    // if the number of nodes is equal to the max capacity return that the list is full, and false otherwise
    return (size_==capacity());
}
