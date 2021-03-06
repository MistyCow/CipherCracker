// CipherCracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CipherCracker.h"


int main()
{

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
    std::string inFileLocation = "bibbia.txt";
    std::ifstream inFile;

    inFile.open(inFileLocation);
    long quadCount = 0;
    

    if (!inFile.is_open())
    {
        std::cout << "Failed loading file: " << inFileLocation << "\n";
        throw;
    }
    std::string inputText;

    inFile.seekg(0, inFile.end);
    inputText.resize(inFile.tellg());
    inFile.seekg(0, inFile.beg);

    inFile.read(&inputText[0], inputText.size());

    inputText = cleanString(inputText);

    // Now that we have a sanitized text we need to count all the quadgrams inside of it
    char curQuad[4];
    for (int j = 0; j < inputText.size() - 3; j++)
    {
        curQuad[0] = inputText[j];
        curQuad[1] = inputText[j + 1];
        curQuad[2] = inputText[j + 2];
        curQuad[3] = inputText[j + 3];
        quadList[quadFinder(curQuad)].countUp();
        quadCount++;
    }
    inFile.close();

    for (int i = 0; i < quadList.size(); i++)
    {
        
        quadList[i].setLikelihood(log((quadList[i].getCount() + 1.f) / quadCount));
    }
    std::cout << "Succesfully created quadgrams from file : " << inFileLocation << "\n";
    // Now we have our quadList set up, let's use it in a hill climbing algorithm
    

    std::string encryptedFileLocation = "stuff.txt";
    std::ifstream encryptedFile;
    encryptedFile.open(encryptedFileLocation);

    if (!encryptedFile.is_open())
    {
        std::cout << "Failed loading file: " << encryptedFileLocation << "\n";
        throw;
    } else
    {
        std::cout << "Succesfully loaded file : " << encryptedFileLocation << "\n";
    }

    std::string encryptedText;

    encryptedFile.seekg(0, encryptedFile.end);
    encryptedText.resize(encryptedFile.tellg());
    encryptedFile.seekg(0, encryptedFile.beg);

    encryptedFile.read(&encryptedText[0], encryptedText.size());

    encryptedText = cleanString(encryptedText);

decrypt:
    int reiteration = 0;
    double maxFitness = fitness(quadList, encryptedText);

    while (reiteration < 100)
    {
        Cipher cipher;

        int iteration = 0;

        double lastFitness = fitness(quadList, cipher.passthrough(encryptedText));
        double curFitness;

        while (iteration < 1000)
        {
            cipher.randomSwitch();
            curFitness = fitness(quadList, cipher.passthrough(encryptedText));
            if (curFitness <= lastFitness)
            {
                cipher.undoSwitch();
            } else
            {
                lastFitness = curFitness;
                iteration = 0;
            }
            iteration++;
        }
        if (curFitness > maxFitness)
        {
            std::cout << cipher.passthrough(encryptedText) << "\n";
            std::cout << "Fitness: " << std::to_string(curFitness) << "\n";
            reiteration = 0;
            maxFitness = curFitness;
        }

        reiteration++;
    }
    char retry;
    std::cout << "\n Would you like to retry? (y/n) : ";
    std::cin >> retry;
    if (retry == 'y')
    {
        std::cout << "\n";
        goto decrypt;
    }

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
std::string cleanString(std::string stringIn)
{
    // First we have to strip all non letters from the line
    for (int i = 0; i < stringIn.length(); i++)
    {
        char curChar = stringIn[i];
        // If it's already lowercase (between 97 and 122) just ignore it
        if (curChar >= 97 && curChar <= 122)
        {
            continue;
        }
        // If it's a capitalized letter (between 65 and 90)
        else if (curChar >= 65 && curChar <= 90)
        {
            // Change it to lowercase
            stringIn[i] = (curChar + 32);
        }
        // If it's a wierder character we just remove it
        else
        {
            stringIn.erase(i, 1);
            i--;
        }
    }
    return stringIn;
}
double fitness(std::vector<Quadgram> quadListIn, std::string text)
{
    double fitness = 1.0;
    char curQuadgram[4];
    text = cleanString(text);
    for (int i = 0; i < text.length() - 3; i++)
    {
        curQuadgram[0] = text[i];
        curQuadgram[1] = text[i + 1];
        curQuadgram[2] = text[i + 2];
        curQuadgram[3] = text[i + 3];

        fitness += quadListIn[quadFinder(curQuadgram)].getLikelihood();
    }
    return fitness / (text.length() - 3);
}