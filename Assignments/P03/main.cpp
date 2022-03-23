/**
 * Source: https://www.techiedelight.com/cpp-implementation-trie-data-structure/
 *
 * The time complexity of a Trie data structure for insertion,
 * deletion, and search operation is O(n) where n is the key
 * length.
 *
 * The space complexity of a Trie data structure is O(N × M × C)
 * N = total number of strings
 * M = longest string length
 * C = alphabet size
 */

#include <algorithm>
#include <iostream>
#include <fstream>       // fstream and ofstream to read and write files
#include <vector>        // Vector
#include "json.hpp"      // nlohmann library to read and write json files
#include "mygetch.hpp"   // To get the input from the user keyboard
#include "termcolor.hpp" // For coloring the output on the terminal
#include "timer.hpp"     // Timer to calclate time: Seconds, NanoSeconds, MilliSeconds
#include <iomanip>       // for formatting

using namespace std;
using json = nlohmann::json; // for convenience

// Define the character size
//#define CHAR_SIZE 128
#define CHAR_SIZE 26

bool isUpper(char letter)
{
    int l = letter;
    return (l >= 65 && l <= 90);
}

bool isLower(char letter)
{
    int l = letter;
    return (l >= 97 && l <= 122);
}

bool isLetter(char letter)
{
    int l = letter;
    return isUpper(l) || isLower(l);
}

bool isAlphaOnly(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!isLetter(word[i]))
        {
            return false;
        }
    }
    return true;
}

void makeUpper(string &word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (isLower(word[i]))
        {
            word[i] -= 32;
        }
    }
}

struct TrieNode
{
    bool isLeaf;
    TrieNode *character[CHAR_SIZE];
    TrieNode()
    {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++)
        {
            this->character[i] = nullptr;
        }
    }
};

vector<char> countLetters(string filename)
{
    ifstream fin;
    vector<char> alph;

    fin.open(filename);

    string word;
    while (!fin.eof())
    {
        fin >> word;
        for (int j = 0; j < word.size(); j++)
        {
            if (std::find(alph.begin(), alph.end(), word[j]) == alph.end())
            {
                alph.push_back(word[j]);
            }
        }
    }
    return alph;
}

// A class to store a Trie node
class Trie
{
    TrieNode *root;
    bool deletion(TrieNode *&, string);
    void find_all(TrieNode *&, string);
    vector<string> results;

public:
    Trie()
    {
        root = new TrieNode;
    }
    void insert(string);
    bool deletion(string);
    bool search(string);
    bool haveChildren(TrieNode const *);
    vector<string> find_all(string);
};

void Trie::find_all(TrieNode *&curr, string key)
{

    if (curr->isLeaf)
    {
        results.push_back(key);
    }

    for (int i = 0; i < 26; i++)
    {
        if (curr->character[i])
        {
            find_all(curr->character[i], key + char(i + 65));
        }
    }
}

vector<string> Trie::find_all(string key)
{
    TrieNode *curr = root;

    results.clear();

    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i] - 65];
    }

    find_all(curr, key);
    return results;
}

// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    makeUpper(key);

    // cout<<key<<endl;

    // start from the root node
    TrieNode *curr = root;
    for (int i = 0; i < key.length(); i++)
    {

        // create a new node if the path doesn't exist
        if (curr->character[key[i] - 65] == nullptr)
        {
            curr->character[key[i] - 65] = new TrieNode();
        }

        // go to the next node
        curr = curr->character[key[i] - 65];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    makeUpper(key);
    TrieNode *curr = root;
    // return false if Trie is empty
    if (curr == nullptr)
    {
        return false;
    }

    for (int i = 0; i < key.length(); i++)
    {

        // go to the next node
        curr = curr->character[key[i] - 65];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr)
        {
            return false;
        }
    }

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(TrieNode const *curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i])
        {
            return true; // child found
        }
    }

    return false;
}

bool Trie::deletion(string key)
{
    makeUpper(key);
    return deletion(root, key);
}

// Recursive function to delete a key in the Trie
bool Trie::deletion(TrieNode *&curr, string key)
{

    // return if Trie is empty
    if (curr == nullptr)
    {
        return false;
    }

    // if the end of the key is not reached
    if (key.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)

        if (curr != nullptr &&
            curr->character[key[0] - 65] != nullptr &&
            deletion(curr->character[key[0] - 65], key.substr(1)) && curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else
        {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
        }
    }

    return false;
}

void loadDictionary(Trie *&T, string filename = "")
{
    string word;
    size_t found;
    ifstream fin;

    if (filename == "")
        fin.open("dictionary.txt");
    else
        fin.open(filename);

    while (!fin.eof())
    {
        fin >> word;

        // found = word.find('\'');
        // if (found == string::npos) {
        //     T->insert(word);
        // }
        if (isAlphaOnly(word))
        {
            T->insert(word);
        }
    }
    // Finally return Trie of the wordLists
}

void loadJsonDict(Trie *&T, string filename = "")
{
    ifstream jsonFile(filename); // open the json file using ifstream
    json data;                   // var. to store the data of json
    jsonFile >> data;            // access the json file and read the data
    for (auto &[key, value] : data.items())
    {
        if (isAlphaOnly((string)key))
        {
            T->insert((string)key);
        }
    }
    jsonFile.close(); // close the file
}
// C++ implementation of Trie data structure
int main()
{
    // Creating variables
    char k;           // holder for character being typed
    string word = ""; // var to concatenate letters to
    Trie *T = new Trie();
    vector<string> results;
    ofstream fout("temp.txt");
    Timer Time;   // create a timer
    Time.Start(); // start it

    loadJsonDict(T, "dict_w_defs.json");

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
        makeUpper(word);
        vector<string> res = T->find_all(word);
        // cout << res.size() << endl;
        if ((int)k != 32)
        { // if k is not a space print it
            cout << termcolor::red << word << termcolor::reset << endl;
            cout << fixed << setprecision(3);
            cout << res.size() << " words found in " << (double)Time.MilliSeconds() / 10000 << endl;
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < res.size(); i++)
            {
                    cout << res[i] << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }
        Time.End(); // end the current timer
    }
    return 0;
}