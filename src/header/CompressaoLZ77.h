#ifndef COMPRESSAO_H
#define COMPRESSAO_H

#include <string>
using namespace std;

class CompressaoLZ77
{   
    public:
        static string comprime(string str); 
        static string descomprime(string str); 
};

#endif