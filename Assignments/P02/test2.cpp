#include <iostream>
#include "LinkedList.hpp"
using namespace std;

int main()
{
    wordNodes list1;
    list1.Insert("Apple");
    list1.Insert("Banana");
    list1.Insert("Pineapple");
    list1.temp = list1.head;
    while (list1.temp != NULL)
    {
        cout << list1.temp->data << endl;
        cout << list1.temp->next << endl;
        list1.temp = list1.temp->next;
    }
    return 0;
}