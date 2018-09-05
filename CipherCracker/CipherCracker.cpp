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
    std::ifstream file;

    file.open(fileLocation);

    long quadCount = 0;
    
    std::string inputLine;
    std::string cleanLine;
    if (file.is_open())
    {
        while (std::getline(file, inputLine))
        {
            // First we have to strip all non letters from the line
            for (int i = 0; i < inputLine.length(); i++)
            {
                char curChar = inputLine[i];
                // If it's a capitalized letter (between 65 and 90)
                if (curChar >= 65 && curChar <= 90)
                {
                    // Put it in lowercase
                    cleanLine.push_back(curChar + 32);
                }
                // If it's already lowercase (between 97 and 122) just put it in
                else if (curChar >= 97 && curChar <= 122)
                {
                    cleanLine.push_back(curChar);
                }
                // If it's a wierder character we just ignore it
            }
            // Now that we have a sanitized line we need to count all the quadgrams inside of it
            char curQuad[4];
            for (int j = 0; j < cleanLine.size() - 4; j++)
            {
                curQuad[0] = cleanLine[j];
                curQuad[1] = cleanLine[j + 1];
                curQuad[2] = cleanLine[j + 2];
                curQuad[3] = cleanLine[j + 3];
                quadList[quadFinder(curQuad)].countUp();
                quadCount++;
            }
            cleanLine.erase();
        }
        std::cout << quadCount;
    } else
    {
        std::cout << "Failed loading file: " << fileLocation << "\n";
    }
    file.close();
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