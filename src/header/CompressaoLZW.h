#ifndef COMPRESSAOLZW_H
#define COMPRESSAOLZW_H

#include <string>
#include <vector>

using namespace std;

class CompressaoLZW
{   
    public:
        static vector<int> comprime(string str); 
        static string descomprime(vector<int>); 
        static string descomprime(string str); 
};

#endif