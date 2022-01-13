#include <iostream>

using namespace std;

int A[100];

// Making new data type to define the Node which has a variable and pointer
struct Node
{
    int x;          // x is the value of the node
    Node *next;     // pointer next is pointer points at the next node
    Node()
    { // Default Constructor
        x = -1;         // the value by default is -1
        next = NULL;    // by default the pointer points at NULL
    }
    Node(int n)
    { // Overloaded Constructor
        x = n;  // whenever we creat a node and we overload it with a value this value is equal to x
        next = NULL;    // pointer by default point at NULL
    }
};

// Class for LinkList
class List
{
private: // Our linked list contain a head and tail and the size of the linked list
    Node *Head; // Node Head (which contains a value and pointer)
    Node *Tail; // Node Tail (which contains a value and pointer)
    int Size;   // Size of the Linked list

public:
    List()
    { // Default Constructor
        Head = Tail = NULL; // by default the head and tail is NULL if we ever creat an object
        Size = 0;           // size is set to zero whwnever we create an object for the linked list
    }

    // Push function is to add value to our linked list and we have to pass an integer value as we see below
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val); // we allocated memory for our temporary Node

        if (!Head && !Tail)
        { 
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    string Print()
    { // Function to print what's in the linked list
        Node *Temp = Head; 
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop()
    { 
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    // Making two objects or another word LinkedList one called L1 and one L2 
    List L1;
    List L2;

    // For loop to push 1 through 24 into list 1 (L1)
    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }
    // for loop to push 50 through 99 into list 2 (L2)
    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    // cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2; // Creating linked list 3 (L3)
    cout << L3 << endl; // L3

    cout << L3[5] << endl;
    return 0;
}
