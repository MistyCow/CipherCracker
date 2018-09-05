// CipherCracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Quadgram.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main()
{
    int quadFinder(char letters[4]);
    // Quadgram Generation
    std::vector<Quadgram> quadList;
    char setUpLetters[4] = { 'a', 'a', 'a', 'a'};
    for (int i = 0; i < 456976; i++)
    {
        quadList.push_back(Quadgram(setUpLetters));
        setUpLetters[3] ++;
        if (setUpLetters[3] > 122)
        {
            setUpLetters[3] = 'a';
            setUpLetters[2]++;
            if (setUpLetters[2] > 122)
            {
                setUpLetters[2] = 'a';
                setUpLetters[1] ++;
                if (setUpLetters[1] > 122)
                {
                    setUpLetters[1] = 'a';
                    setUpLetters[0]++;
                }
            }
        }
        
    }
    std::string fileLocation = "Il_bacio_di_Lesbia.txt";
    std::ifstream inFile;

    inFile.open(fileLocation);    
    long quadCount = 0;
    

    if (!inFile.is_open())
    {
        std::cout << "Failed loading file: " << fileLocation << "\n";
        throw;
    }

    std::string inputText;

    inFile.seekg(0, inFile.end);
    inputText.resize(inFile.tellg());
    inFile.seekg(0, inFile.beg);

    inFile.read(&inputText[0], inputText.size());

    // First we have to strip all non letters from the line
    for (int i = 0; i < inputText.length(); i++)
    {
        char curChar = inputText[i];
        // If it's already lowercase (between 97 and 122) just ignore it
        if (curChar >= 97 && curChar <= 122)
        {
            continue;
        }
        // If it's a capitalized letter (between 65 and 90)
        else if (curChar >= 65 && curChar <= 90)
        {
            // Change it to lowercase
            inputText[i] = (curChar + 32);
        }
        // If it's a wierder character we just remove it
        else
        {
            inputText.erase(i,1);
            i--;
        }
    }
    std::cout << inputText.length() << "\n";

    // Now that we have a sanitized text we need to count all the quadgrams inside of it
    char curQuad[4];
    for (int j = 0; j < inputText.size() - 4; j++)
    {
        curQuad[0] = inputText[j];
        curQuad[1] = inputText[j + 1];
        curQuad[2] = inputText[j + 2];
        curQuad[3] = inputText[j + 3];
        quadList[quadFinder(curQuad)].countUp();
        quadCount++;
    }
    std::cout << quadCount;
    inFile.close();
    return 0;
}

int quadFinder(char letters[4])
{
    char offset = 97;
    return
    (
        ((letters[0] - offset) * 17576)
        + ((letters[1] - offset) * 676)
        + ((letters[2] - offset) * 26)
        + letters[3] - offset
    );
}