
///////////////////////////////////////////////////////////////////////////////
//
// Author     :     Fowzy Alsaud
// Label      :     P01
// Title      :     Assignment 01
// Assignment :     Program 1 - Resizing the Stack
// Course     :     CMPS 3013
// Semester   :     Spring 2020
//
// Description:
//       Overview of a class implementing an array based stack
//
// Instructions:
//    - Create a folder in your Assignments folder called P01
//    - Place your re-written main.cpp file into this P01 folder.
//    - Add your folder with all input and/or output files to your github repo.
//    - Banner
// Files:
//    - main.cpp
//    - my_test.dat
//    - nums_test.dat
//    - nums.dat
//    - output
//    TODO: MAKE SURE YOU CHANGE DEFAULT SIZE FROM 3 TO 10
//    TODO: Have better understanding full threshold & shrink threshold
//    TODO: Do I have to update the grow and shrink ratio when we reach to that
//          limition (fullThreshold & shrinkThreshold) that are provided by the user?
//            what I mean by that is keeping the grow and shrink ration as default and updating them
//            whenever the user user reach to the full threshold or shrink threshold and who goes first?
//            let's say ./main.cpp 0.70 0.20 1.25 .75
//            so if we start the stack from size 10(default) and when we gets to 70% full which is 7 items
//            then we have to update my grow ratio to 1 instead of 2 (default) and leave the shrink alone
//            till I get to the shrink status(which is if the stack reach %20 of the stack size)?
//            so if I get to 7 items my stack it will switch the grow ratio to 1
//            and keep going! so if the stack reachs 10 items(%100) it will be setting 1 grow
//            and let's say we remove items till I get to 2 items (which is %20 of my 10 size stack)
//            then I have change the shrink ratio to 1 instead of 0.5
//            at the same times
/////////////////////////////////////////////////////////////////////////////////
#include <iostream> // cout, cin
#include <fstream>  // for file I/O
#include <stdlib.h> // atof
#include <vector>   // vector
using namespace std;

double percentage; // global var. to follow up the size of my stack

/**
 * ArrayStack
 *
 * Description:
 *      Array based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class ArrayStack
{
private:
  int *A;                        // pointer to array of int's
  int size;                      // current max stack size
  int top;                       // top of stack
  double fullThreshold = .85;    // ratio you go over to grow the stack (e.g. .85)
  double shrinkThreshold = 0.15; // ratio to go under to shrink the stack (e.g. .15) but not below size 10!
  double growRatio = 2.0;        // how much to grow the stack (e.g. 2.0 = double the size)
  double shrinkRatio = 0.5;      // how much to shrink the stack (e.g. .5 = half its size)
  int maxSize = 0;               // max size of the stack ever reached
  int timesResized = 0;          // number of times the stack has been resized (grown or reduced)
  double g;
  double s;
  vector<int> v; // vector to get the max
  // top = number of items in the stack + 1
  // size = array size
  // size = 100
  // (top + 1) / size

public:
  /**
   * ArrayStack
   *
   * Description:
   *      Default Constructor no params
   *
   * Params:
   *     - None
   *
   * Returns:
   *     - NULL
   */
  ArrayStack()
  {
    size = 3;
    A = new int[size];
    top = -1;
  }

  /**
   * ArrayStack
   *
   * Description:
   *      Overloaded Constructor size param
   *
   * Params:
   *     - int size
   *
   * Returns:
   *     - NULL
   */
  ArrayStack(int s)
  {
    size = s;
    A = new int[s];
    top = -1;
  }

  /**
   * Public bool: Empty
   *
   * Description:
   *      Stack empty?
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [bool] true = empty
   */
  bool Empty() { return (top <= -1); }

  /**
   * Public bool: Full
   *
   * Description:
   *      Stack full?
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [bool] true = full
   */
  bool Full() { return (top >= size - 1); }

  /**
   * Public int: Peek
   *
   * Description:
   *      Returns top value without altering the stack
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [int] top value if any
   */
  int Peek()
  {
    if (!Empty())
    {
      return A[top];
    }

    return -99; // some sentinel value
                // not a good solution
  }

  /**
   * Public int: Pop
   *
   * Description:
   *      Returns top value and removes it from stack
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [int] top value if any
   */
  int Pop()
  {
    ifAmFull();
    // Here if the stack is not empty and is bigger than or equal to 10 then it will pop the item else it will break
    if (!Empty())
    {
      ContainerShrink();
      return A[top--];
    }else{
      cout<<"empty"<<endl;
    }

    return -99; // some sentinel value
                // not a good solution
  }

  /**
   * Public void: Print
   *
   * Description:
   *      Prints stack to standard out
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void Print()
  {
    for (int i = 0; i <= top; i++)
    {
      cout << A[i] << " ";
    }
    cout << endl;
  }

  /**
   * Public bool: Push
   *
   * Description:
   *      Adds an item to top of stack
   *
   * Params:
   *      [int] : item to be added
   *
   * Returns:
   *      [bool] ; success = true
   */
  bool Push(int x)
  {
    ifAmFull();
    if (Full())
    {
      ContainerGrow();
    }
    if (!Full())
    {
      A[++top] = x;
      v.push_back(size);
      return true;
    }
    return false;
  }

  /**
   * Public bool: CheckResize
   *
   * Description: Basically its a boolean function that will give you a true if the stack is equal or larger than 10
   * Else it will return false
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      True or False
   */
  bool CheckResize()
  {
    // if the size is smaller or equal to 10 then tell the user is true
    if ((double)top/(double)size )
    {
      return 1;
    }
    else // return false if the size is bigger than 10
    {
      return 0;
    }
  }

  /**
   * Public void: ContainerShrink
   *
   * Description:
   *      Resizes the container for the stack by shrink the stack by 1 everytime I pop an item from the stack
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void ContainerShrink()
  {
    if (!CheckResize())
    {
      int newSize = size / shrinkRatio; // new size
      int *temp = new int[newSize];     // allocate new memory
      for (int i = 0; i < top; i++)
      {
        temp[i] = A[i]; // copy old data
      }
      delete[] A;     // delete old memory
      size = newSize; // update size
      cout<<"size: "<<size<<endl;
      A = temp;       // update pointer
      timesResized++; // calculate the number of times the stack has been resized}}
    }
  }

  /**
   * Public void: ContainerGrow
   *
   * Description:
   *      Resizes the container for the stack by doubling
   *      its capacity
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void ContainerGrow()
  {
    int newSize = size * growRatio; // double size of original
    int *B = new int[newSize];      // allocate new memory
    for (int i = 0; i < top; i++)
    { // copy values to new array
      B[i] = A[i];
    }
    delete[] A;     // delete old array
    size = newSize; // save new size
    cout<<"size: "<<size<<endl;
    A = B;          // reset array pointer
    timesResized++; // calculate the number of times the stack has been resized
  }

  /**
   * Public int: getSize
   *
   * Description:
   *      Function to get the size of the current stack
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      int
   */
  int getSize()
  {
    return size;
  }
  /**
   * Public void: setParams
   *
   * Description:
   *      set the paramaeters for the stack if the user  wants to change them
   *      Notice: Only when the user pass them from argc and argv
   *
   * Params:
   *      Get the argument from the main function if it provided any
   *
   * Returns:
   *      NULL
   */
  void setConfiguration(char **params)
  {
    if (params[1] != 0 && params[2] != 0 && params[3] != 0 && params[3] != 0)
    {
      fullThreshold = atof(params[1]);
      shrinkThreshold = atof(params[2]);
      g = atof(params[3]);
      s = atof(params[4]);
    }
  }
  /**
   * Public double: getFullThreshold
   *
   * Description: Get ratio you go over to grow the stack
   *
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      double
   */
  double getFullThreshold()
  {
    return fullThreshold;
  }
  /**
   * Public double: getShrinkThreshold
   *
   * Description: ratio to go under to shrink the stack (e.g. .15) but not below size 10!
   *
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      double
   */
  double getShrinkThreshold()
  {
    return shrinkThreshold;
  }
  /**
   * Public double: growRatio
   *
   * Description: how much to grow the stack
   *
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      double
   */
  double getGrowRatio()
  {
    return growRatio;
  }
  /**
   * Public double: getShrinkRatio
   *
   * Description: how much to shrink the stack
   *
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      double
   */
  double getShrinkRatio()
  {
    return shrinkRatio;
  }
  /**
   * Public int: getMax
   *
   * Description: Get the max size the stack ever reached
   *
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      int
   */
  int getMax()
  {
    int max = v[0]; // initialize max by the first element in the vector
    for (int i = 0; i < v.size(); i++)
    {
      if (A[i] > max)
      {
        max = A[i];
      }
    }
    return max;
    v.clear(); // delete or clear the vector to save memory
  }
  /**
   * Public int: getTimesResized
   *
   * Description:
   *      Get the number of times the stack has been resized
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      int
   */
  int getTimesResized()
  {
    return timesResized;
  }
  /**
   * Public double: getPercent
   *
   * Description:
   *      Get the percentage of the size of the stack
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      double
   */
  double getPercent()
  {
    return ((double)top + 1) / (double)size;
  }
  /**
   * Public void: ifAmFull
   *
   * Description:
   *      Check if the stack apply the status that user provided us
   *
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void ifAmFull()
  {
    // the program with this if statement it will apply if full th
    if (fullThreshold == getPercent())
      growRatio = g;
    if (shrinkRatio == getPercent())
      shrinkRatio = s;
  }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv)
{
  // if(argc > 1){
  ArrayStack stack;               // create stack object
  ifstream inFile("nums_test.dat"); // reading from our input file
  ofstream outFile("output");     // writing to our output file
  int num;                        // variable to hold the number
  int counter = 0;                // number of commands processed (how many values read from the input file)
  stack.setConfiguration(argv);   // set the configuration for the stack
  while (inFile >> num)           // while loop to read the input file number by number
  {
    int even = num % 2 == 0; // define even number
    if (even)                // if the number is even then push it to the stack
    {
      stack.Push(num);
    }
    else // if the number is odd then pop it from the stack
    {
      stack.Pop();
    }
    cout << stack.getPercent() << endl;
    counter++; // increment the counter to count the number of commands we processed
  }
  stack.Print(); // print the stack to confirm the stack has the right items

  // Print out the Output file into the output file "output.txt"
  outFile << "######################################################################" << endl;
  outFile << "\t\tAssignment 4 - Resizing the Stack" << endl;
  outFile << "\t\tCMPS 3013" << endl;
  outFile << "\t\tFowzy Alsaud" << endl
          << endl;
  outFile << "\t\tConfig Params:" << endl;
  outFile << "\t\t\tFull Threshold: " << stack.getFullThreshold() << endl;
  outFile << "\t\t\tShrink Threshold: " << stack.getShrinkThreshold() << endl;
  outFile << "\t\t\tGrow Ratio : " << stack.getGrowRatio() << endl;
  outFile << "\t\t\tShrink Ratio : " << stack.getShrinkRatio() << endl
          << endl;
  outFile << "\t\tProcessed " << counter << endl
          << endl;
  outFile << "\t\tMax Stack Size: " << stack.getMax() << endl;
  outFile << "\t\tEnd Stack Size: " << stack.getSize() << endl;
  outFile << "\t\tStack Resized: " << stack.getTimesResized() << " times" << endl;
  outFile << "######################################################################" << endl;
  // cout << stack.getPercent() << endl;

  return 0;
}