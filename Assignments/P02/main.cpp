#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include "LinkedList.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
/*
are pointers suppos to be in private
can we do overloaded operator to print the linked list as list[i]
coloring
*/
/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
int CountLines(string file_name)
{
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
wordNodes LoadAnimals(string file_name)
{
    ifstream fin;        // file to get animal names
    wordNodes wordLists; // Creating wordList
    string word;
    fin.open(file_name); // open file for reading
    while (fin >> word)
    {
        wordLists.Insert(word); // push the word to my wordLists dictonary
    }
    return wordLists;
}

int main()
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    wordNodes animals;      // array of animal names
    vector<string> matches; // any matches found in vector of animals
    int loc;                // location of substring to change its color
    int show10words = 0;    // flag to show 10 words at a time
    int matchesFound = 0;   // number of matches found
    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it

    animals = LoadAnimals("dictionary.txt");
    T.End(); // end the current timer
    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and print json" << endl;
    cout << T.MilliSeconds() << " milli to read in and print json" << endl;
    cout << T.NanoSeconds() << " nano to read in and print json" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z')
    {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127)
        {
            if (word.size() > 0)
                word = word.substr(0, word.size() - 1);
        }
        else
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k))
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97)
                k += 32;
            word += k; // append char to word
        }
        // cout << word << endl;
        // Find any animals in the array that partially match
        // our substr word
        matches = animals.FindAnimals(animals, word);
        // wordNode *t; // = new wordNode();
        // cout << t->data << endl;
        // cout << t->data << endl;

        if (((int)k != 32))
        { // if k is not a space print it
            T.End();
            cout << T.NanoSeconds() << " nano,\t" << T.MilliSeconds() << ",\t" << T.Seconds() << ",seconds." << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Animals Found: ";
            cout << termcolor::green;
            // This prints out all found matches

            for (int i = 0; i < matches.size(); i++)
            {

                    // find the substring in the word
                    loc = matches[i].find(word);
                    // if its found

                    // print one letter at a time turning on red or green
                    //  depending on if the matching subtring is being printed
                    for (int j = 0; j < matches[i].size(); j++)
                    {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1)
                        {
                            cout << termcolor::red;
                        }
                        else
                        {
                            cout << termcolor::green;
                        }
                        if (loc != string::npos &&matchesFound < 10)
                        {
                            cout << matches[i][j];
                        }
                        cout << termcolor::green;
                    }
                    cout << "\t";

            }
            cout << termcolor::reset << endl
                 << endl;
            cout << fixed;
            cout << setprecision(2);
            cout << matches.size() << " words found in " << (double)T.Seconds() << " seconds." << endl;
        }
    }
    return 0;
}