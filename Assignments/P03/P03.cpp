#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include "Trie.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int CountLines(string file_name)
{
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}

vector<string> FindWord(Trie tr1, string word)
{
    vector<string> matches;
    if (tr1.search(word))
    {
        matches.push_back(word);
    }
    return matches;
}

Trie LoadAnimals(string file_name)
{
    ifstream fin;   // file to get animal names
    Trie wordLists; // Creating wordList
    string word;
    fin.open(file_name); // open file for reading
    while (fin >> word)
    {
        wordLists.insert(word); // push the word to my wordLists dictonary
    }
    return wordLists;
}

int main()
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    Trie animals;           // array of animal names
    vector<string> matches; // any matches found in vector of animals
    ofstream fout("temp.txt");
    Timer T;   // create a timer
    T.Start(); // start it
    animals = LoadAnimals("dictionary.txt");
    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z')
    {
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
        matches = FindWord(animals, word);
        if ((int)k != 32)
        { // if k is not a space print it
            cout << termcolor::red << word << termcolor::reset << endl;
            cout << fixed << setprecision(3);
            cout << matches.size() << " words found in " << (double)T.MilliSeconds() / 10000 << endl;
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++)
            {
                cout << matches[i] << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }``
        T.End(); // end the current timer
    }
    return 0;
}