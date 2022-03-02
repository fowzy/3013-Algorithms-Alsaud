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
int CountLines(string file_name) {
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
Trie LoadAnimals(string file_name)
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
// vector<string> FindAnimals(wordNodes array, string substring)
//     {
//         vector<string> matches; // to hold any matches
//         size_t found; // size_t is an integer position of
//                       // found item. -1 if its not found.
//         wordNode *temp =->;
//         while (temp != NULL)
//         {
//             found = temp->data.find(substring);
//             if (found != string::npos && found == 0) // if found >= 0 (its found then)
//             {
//                 matches.push_back(temp->data);
//             }
//             temp = temp->next;
//         }
//         return matches;
//     }

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    wordNodes animals; // array of animal names
    vector<string> matches; // any matches found in vector of animals
    ofstream fout("temp.txt");
    Timer T;   // create a timer
    T.Start(); // start it

    animals = LoadAnimals("dictionary.txt");

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        matches = animals.FindAnimals(animals, word);

        if ((int)k != 32) { // if k is not a space print it
            cout << termcolor::red << word << termcolor::reset << endl;
            cout << matches.size() << " words found in " << (double)T.Seconds()/60<< endl;
            cout << termcolor::green;
            int counterMatches=0;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++) {
                if(counterMatches <10)
                    cout << matches[i] << " ";
                else
                    break;
                counterMatches++;
            }
            cout << termcolor::reset << endl
                 << endl;
        }
        T.End(); // end the current timer
    }
    return 0;
}