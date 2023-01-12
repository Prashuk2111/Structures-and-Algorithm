#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "Lab1Tests.hpp"

string get_status_str(bool status)
{
    return status ? "Pass" : "Fail";
}

int main()
{
    SequentialList seq_test(5);
    DoublyLinkedList doubly;
    
    doubly.insert_back(1);
    doubly.insert_back(2);
    doubly.insert_back(3);
    doubly.insert(69,2);
    doubly.remove(2);
    doubly.print();
    
    cout << doubly.empty();
    
    return EXIT_SUCCESS;
}
