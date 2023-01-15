#ifndef COMPRESSAOLZW_H
#define COMPRESSAOLZW_H

#include <string>
#include <vector>

using namespace std;

class CompressaoLZW
{   
    public:
        static vector<unsigned short> comprime(string str); 
        static string descomprime(vector<unsigned short>); 
        static string descomprime(string str); 
};

#endif