#include "CompressaoLZ77.h"

#include <iostream>

#define TDIC 6
#define TBUF 4

string CompressaoLZ77::comprime(string str) {
    string strCompactada = "";
    int point = 0;
    int midPoint = 0;
    int dicPtr = 0;
    string buffer = "";
    string dicionario = "";
    buffer = str.substr(0, TBUF);

    while (midPoint < str.length())
    {   
        dicPtr = midPoint - TDIC;
        bool encontrou = false;
        int volta = 0;
        int qtd = 0;
        if (dicPtr < 0) dicPtr = 0;
        for (int p = dicPtr; p < midPoint; p++)
        {
            if (str.at(midPoint) == str.at(p)) {
                encontrou = true;
                volta = midPoint - p;
                qtd++;
                for (int j = 1; j < TBUF; j++)
                {
                    if (midPoint+j < str.length()) {
                        if (str.at(midPoint+j) != str.at(p+j)) {
                            qtd = j;
                            break;
                        }
                    } else {
                        break;
                    }

                }
                break;
                
            } else {
            }

        }

        try
        {
        }
        catch(const std::out_of_range& e)
        {
        }
        strCompactada += to_string(volta);
        strCompactada += to_string(qtd);
        try
        {
            strCompactada += str.at(midPoint+qtd);
        }
        catch(const std::out_of_range& e)
        {
            strCompactada += '\0';
        }
        
        midPoint += qtd+1;
    }

    return strCompactada;   

}

string CompressaoLZ77::descomprime(string str) {
    string descomprimida = "";

    descomprimida += str.at(2);
    int ptr = 1;
    for (int i = 3; i < str.length(); i+=3)
    {
        int volta = int(str.at(i) - '0');
        int qtd = int(str.at(i+1) - '0');
        char next = str.at(i+2);

        for (int j = 0; j < qtd; j++)
        {
            descomprimida += descomprimida.at(ptr-volta+j);
        }
        
        descomprimida += next;
        
        ptr += qtd+1;
    }
    
    return descomprimida;
}