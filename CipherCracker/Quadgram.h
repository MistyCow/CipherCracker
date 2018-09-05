#pragma once
#include <string>
class Quadgram
{
private:
    char letters[4];
    int count = 0;
    double likelihood;
public:
    Quadgram();
    Quadgram(char lettersIn[4]);

    void setLetters(char lettersIn[4]);
    char *getLetters();

    void countUp();
    int getCount();

    void setLikelihood(double likelihoodIn);
    double getLikelihood();

    operator std::string();
};