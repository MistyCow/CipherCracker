#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Quadgram.h"
#include "Cipher.h"

int main();
int quadFinder(char letters[4]);
std::string cleanString(std::string stringIn);
double fitness(std::vector<Quadgram> quadListIn, std::string text);