#include "stdafx.h"
#include "Cipher.h"


Cipher::Cipher()
{
    srand(time(NULL));

    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = i + 97;
    }
    bool assigned[26] = { false };
    int curRand = rand() % 26;
    int counter = 0;
    for (int i = 0; i < 26; i++)
    {
        while (assigned[curRand])
        {
            curRand = rand() % 26;
        }
        cipherAlphabet[i] = alphabet[curRand];
        assigned[curRand] = true;
    }
}

std::string Cipher::passthrough(std::string textIn)
{
    std::string returnString;
    returnString.resize(textIn.size());
    for (int i = 0; i < textIn.size(); i++)
    {
        returnString[i] = cipherAlphabet[textIn[i] - 97];
    }
    return returnString;
}

void Cipher::randomSwitch()
{
    tmpRand[0] = rand() % 26;   
    tmpRand[1] = rand() % 26;

    char tmpChar = cipherAlphabet[tmpRand[0]];

    cipherAlphabet[tmpRand[0]] = cipherAlphabet[tmpRand[1]];

    cipherAlphabet[tmpRand[1]] = tmpChar;

}

void Cipher::undoSwitch()
{
    char tmpChar = cipherAlphabet[tmpRand[0]];

    cipherAlphabet[tmpRand[0]] = cipherAlphabet[tmpRand[1]];

    cipherAlphabet[tmpRand[1]] = tmpChar;
}
