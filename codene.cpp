#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <random>  
#include <windows.h>
using namespace std;

struct translate
{
    string word;
    string definition;
};

void tumoi(int m)
{
    ifstream inputFile("W3.txt");
    if (!inputFile)
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    vector<translate> words;
    string line;
    while (getline(inputFile, line))
    {
        size_t separatorPos = line.find(';');
        if (separatorPos == string::npos)
        {
            cerr << "Invalid line format: " << line << endl;
            continue;
        }

        translate wordDef;
        wordDef.word = line.substr(0, separatorPos);
        wordDef.definition = line.substr(separatorPos + 1);
        words.push_back(wordDef);
    }

    inputFile.close();

    int numWords = words.size();
    cout << "Number of new words: " << numWords << endl;

    random_device rd;
    mt19937 g(rd());
    shuffle(words.begin(), words.end(), g);

    int numRandomWords = min(m, numWords);

    ofstream outputFile("random.txt");
    if (!outputFile)
    {
        cerr << "Failed to create output file." << endl;
        return;
    }

    for (int i = 0; i < numRandomWords; i++)
    {
        const auto &word = words[i];
        outputFile << "Word: " << word.word << endl;
        outputFile << endl;
        cout << "Word: " << word.word << endl;
        cout << "DW: " << word.definition << endl
             << endl;
    }

    outputFile.close();

    words.clear();
}

int main()
{
    string a;
    int m;
    cin >> m;
    tumoi(m);
    cout << "Newword save in random_words.txt" << endl;
    cout << "Press Y/y to open ChatGPT and ask a question/press N/n to close";
    cin >> a;
    if (a == "Y" || a == "y")
    {
        ShellExecute(NULL, "open", "https://chat.openai.com/c/59698162-e413-4b39-a38e-3f34a1047b79", NULL, NULL, SW_SHOWNORMAL);

        Sleep(2000);
        string b;
        cout << "Please choose Enter for close";
        cin >> b;
        return 0;
    }
    else
    {
        return 0;
    }
}

// cover by chatgpt