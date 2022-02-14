#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include "LinkedList.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

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
wordNodes FindAnimals(wordNodes array, string substring)
{
    wordNodes matches; // to hold any matches
    size_t found;      // size_t is an integer position of
                       // found item. -1 if its not found.
    array.temp = array.head;
    while (array.temp != NULL)
    {
        found = array.temp->data.find(substring);
        if (found != string::npos)
        { // if found >= 0 (its found then)
            matches.Insert(array.temp->data);
        }
        array.temp = array.temp->next;
    }
    return matches;
}

int main()
{
    char k;            // holder for character being typed
    string word = "";  // var to concatenate letters to
    wordNodes animals; // array of animal names
    wordNodes matches; // any matches found in vector of animals

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
            {
                word = word.substr(0, word.size() - 1);
            }
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
            {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        matches = FindAnimals(animals, word);

        if ((int)k != 32)
        { // if k is not a space print it
            T.End();
            cout << T.NanoSeconds() << " nano, "<< T.MilliSeconds() << " milli seconds, " << T.Seconds() << " seconds." << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Animals Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            // matches.Print();
            int matchCounter =0;
            matches.temp = matches.head;
            while (matches.temp != NULL)
            {
                if(matchCounter <= 10){
                cout << matches.temp->data <<"\t";
                // cout << matches.temp->next << endl;
                matches.temp = matches.temp->next;
                }
								else{
									break;
								}
                matchCounter++;
            }
            cout << termcolor::reset << endl
                 << endl;
        }
    }
    return 0;
}