#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;
// Define a node as word Node
struct wordNode
{
    string data; // save the new word in this variable
    wordNode *next;
    // Overloaded constructor that will pass a value and set the next pointer to NULL
    wordNode(string s)
    {
        data = s;
        next = NULL;
    }
    // Default Constructor
    wordNode()
    {
        next = NULL;
    }
};

// Make a linked list and call it wordNodes
class wordNodes
{
private:
    wordNode *head;     // pointer points to the head of the list
    wordNode *current;  // pointer to see where we at 
    wordNode *temp;     // temp pointer
    int size;           // variable to keep up with the size of my linked lists

public:
    int counterMatches=0;
    // Default Constructor
    wordNodes()
    {
        head = NULL;
        current = NULL;
        temp = NULL;
        size = 0;
    }
    // Function that will insert a new word to the linked list
    void Insert(string s)
    {
        wordNode *newWord = new wordNode(s);
        if (head == NULL)
        {                      // if the head is empty node
            head = newWord;    // then head is equal to the new node (value = newWord, and Pointer is NULL)
            current = newWord; // current is pointing at the new word
        }
        else // if the head is not empty
        {
            current->next = newWord; // it will make the current node next points to the new word
            current = newWord;       // then updated the value of the new current
        }
        size++; // count the size of the linked list
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
                // cout << temp->next << endl;
                temp = temp->next;
            }
    }
    // function to return the size of the linked list
    int Size()
    {
        return size;
    }
    /**
     * Description:
     *      Finds partial matches in an array of strings and returns them. It
     *      doesn't matter where in the string the match is.
     * Params:
     *      vector<string>  array       - array to search
     *      string          substring   - substring to search for in each word
     *
     * Returns:
     *      vector<string> - holding all the matches to substring
     */
    vector<string> FindAnimals(wordNodes array, string substring)
    {
        vector<string> matches; // to hold any matches
        size_t found; // size_t is an integer position of
                      // found item. -1 if its not found.
        wordNode *temp = head;
        while (temp != NULL)
        {
            found = temp->data.find(substring);
            if (found != string::npos && found == 0) // if found >= 0 (its found then)
            {
                matches.push_back(temp->data);
            }
            temp = temp->next;
        }
        return matches;
    }
};
