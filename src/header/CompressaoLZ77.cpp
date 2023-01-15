#include "CompressaoLZ77.h"

#include <iostream>

#define TDIC 255
#define TBUF 255

string CompressaoLZ77::comprime(string str) {
    string strCompactada = "";
    int point = 0;
    int cursor = 0;
    int dicPtr = 0;
    string buffer = "";
    string dicionario = "";
    buffer = str.substr(0, TBUF);

    while (cursor < str.length())
    {   
        dicPtr = cursor - TDIC;
        if (dicPtr < 0) dicPtr = 0;
        string maiorPadrao = "";
        int inicioMaiorPadrao = 0;
        for (int p = dicPtr; p < cursor; p++)
        {
            if (str.at(cursor) == str.at(p)) {
                string padrao = "";
                padrao += str.at(cursor);
                for (int j = 1; j < TBUF; j++)
                {
                    if (cursor+j >= str.length())
                        break;

                    if (str.at(cursor+j) == str.at(p+j)) {
                        padrao += str.at(cursor+j);
                    } else {
                        break;
                    }
                }
                if (padrao.length() > maiorPadrao.length()) {
                    maiorPadrao = padrao;
                    inicioMaiorPadrao = p;
                }
            }
        }

        unsigned char volta = 0;
        unsigned char qtd = 0;
        char next;
        if (!maiorPadrao.empty()) {
            volta =  cursor - inicioMaiorPadrao;
            qtd = maiorPadrao.length();
        }

        if (cursor + qtd < str.length())
            next = str.at(cursor + qtd);
        else
            next = '\0';

        strCompactada += volta;
        strCompactada += qtd;
        strCompactada += next;
        
        cursor += qtd+1;
    }
    return strCompactada;   

}

string CompressaoLZ77::descomprime(string str) {
    string descomprimida = "";

    descomprimida += str.at(2);
    int ptr = 1;
    for (int i = 3; i < str.length()-1; i+=3)
    {
        unsigned char volta = str.at(i);
        unsigned char qtd = str.at(i+1);
        char next = str.at(i+2);

        for (int j = 0; j < qtd; j++)
        {
            descomprimida += descomprimida.at(ptr-volta+j);
        }
        if (next != '\0')
            descomprimida += next;
        
        ptr += qtd+1;
    }
    
    return descomprimida;
}