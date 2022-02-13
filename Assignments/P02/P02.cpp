#include <iostream>
// #include <timer.hpp>
using namespace std;

// Define a node as word Node
struct wordNode
{
    string data;
    wordNode *next;
    wordNode()
    {
        next = NULL;
    }
    wordNode(string s)
    {
        data = s;
        next = NULL;
    }
};

// Make a linked list and call it wordNodes
class wordNodes
{
private:
    wordNode *head;
    wordNode *current;

public:
    // Default Constructor
    wordNodes()
    {
        head = NULL;
        current = NULL;
    }
    // Function that will insert a new word to the linked list
    void Insert(string s)
    {
        wordNode *newWord = new wordNode(s);
        if (head == NULL)
        { // if the head is empty node
            head = newWord;     // then head is equal to the new node (value = newWord, and Pointer is NULL)
            current = newWord;  // current is 
        }
        else // if the head is not empty
        {
            current->next = newWord; // it will make the current node next points to the new word
            current = newWord; // then updated the value of the new current
        }
    }
    // Function that will print the linked list
    void Print()
    {
        wordNode *temp = head;
        if (head == NULL)
            cout << "It's Empty." << endl;
        else
            while (temp != NULL)
            {
                cout << temp->data << endl;
                cout << temp->next << endl;
                temp = temp->next;
            }
    }
};

int main()
{
    wordNodes treeWords;
    treeWords.Insert("Banana");
    treeWords.Insert("Pineapple");
    treeWords.Insert("Apple");
    treeWords.Insert("Test");
    treeWords.Print();
    return 0;
}
