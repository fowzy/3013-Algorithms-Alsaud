#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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
    int size;

public:
    // Default Constructor
    wordNodes()
    {
        head = NULL;
        current = NULL;
        size = 0;
    }
    // Function that will insert a new word to the linked list
    void Insert(string s)
    {
        wordNode *newWord = new wordNode(s);
        if (head == NULL)
        {                      // if the head is empty node
            head = newWord;    // then head is equal to the new node (value = newWord, and Pointer is NULL)
            current = newWord; // current is
        }
        else
        {                            // if the head is not empty
            current->next = newWord; // it will make the current node next points to the new word
            current = newWord;       // then updated the value of the new current
        }
        size++;
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
    int Size()
    {
        return size;
    }
};

int main()
{
    wordNodes treeWords;

    // treeWords.Insert("Banana");
    // treeWords.Insert("Pineapple");
    // treeWords.Insert("Apple");
    // treeWords.Insert("Test");
    // cout << treeWords.Size() << endl;
    // treeWords.Print();
    // NORMAL METHOD
    // vector<string> array1;
    // ifstream f("food.txt");
    // string food;
    // // first method to push an item to a vector
    // while(f >> food){
    //     array1.push_back(food);
    // }
    // // print a vector
    // for(int i=0;i<=array1.size();i++){
    //     cout << array1[i] << endl;
    // }
    // f.close();
    // GRIFFIN'S METHOD
    vector<string> array2(4);
    ifstream f2("food.txt");
    string fruits;
    // Griffin's method to push an item to the vector
    // for (int i = 0; i < 4; i++)
    // {
    //     f2 >> treeWords.Insert(array2[i]);
    //     for (auto &c : array2[i])
    //     {                   // c++ 11 style loop
    //         c = tolower(c); // lowercase the animal name
    //     }
    // }
    while(f2 >> fruits){
        treeWords.Insert(fruits);
        for (auto &c : fruits) { // c++ 11 style loop
            c = tolower(c);        // lowercase the animal name
        }
    }
    // print a vector
    // cout << array2.size() << endl;
    // for (int i = 0; i < array2.size(); i++)
    // {
    //     cout << array2[i] << endl;
    // }
    treeWords.Print();
    f2.close();
    return 0;
}
