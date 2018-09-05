#pragma once
#include <random>
#include <time.h>
#include <string>

class Cipher
{
    char alphabet[26];
    char cipherAlphabet[26];

    int tmpRand[2];
public:
    Cipher();
    std::string passthrough(std::string textIn);
    void randomSwitch();
    void undoSwitch();
};

