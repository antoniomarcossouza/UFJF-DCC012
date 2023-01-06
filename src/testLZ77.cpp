// g++ testLZ77.cpp ./header/*.cpp -I ./src/header -o ./src/main

#include <iostream>
#include <string>
#include "header/CompressaoLZ77.h"

using namespace std;


int main() {
    cout << "iniciando" << endl;
    cout << CompressaoLZ77::comprime("bananabanabofana");
}