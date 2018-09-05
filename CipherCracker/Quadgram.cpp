#include "stdafx.h"
#include "Quadgram.h"


Quadgram::Quadgram()
{}

Quadgram::Quadgram(char lettersIn[4])
{
    for (int i = 0; i < 4; i++)
    {
        letters[i] = lettersIn[i];
    }
}

void Quadgram::setLetters(char lettersIn[4])
{
    for (int i = 0; i < 4; i++)
    {
        letters[i] = lettersIn[i];
    }
}

char *Quadgram::getLetters()
{
    return letters;
}

void Quadgram::countUp()
{
    count++;
}

int Quadgram::getCount()
{
    return count;
}

void Quadgram::setLikelihood(double likelihoodIn)
{
    likelihood = likelihoodIn;
}

double Quadgram::getLikelihood()
{
    return likelihood;
}

Quadgram::operator std::string()
{
    std::string returnString = letters;
    returnString.push_back(':');
    returnString += std::to_string(count);

    return returnString;
}
