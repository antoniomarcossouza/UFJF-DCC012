#include "CompressaoLZW.h"
#include <unordered_map>


#include <iostream>
using namespace std;


vector<int> CompressaoLZW::comprime(string str) {
    unordered_map<string, int> dicionario;

    // iniciar dicionario com a tabela hash
    for (int i = 0; i < 128; i++)
    {
        string aux = "";
        aux += char(i);
        dicionario[aux] = i;
    }

    string padrao = str.substr(0, 1); // primeiro simbolo da entrada
    int code = 128;
    vector<int> saida;
    for (int i = 0; i < str.length()-1; i++) 
    {
        char c = str.at(i+1);
        
        if (dicionario.find(padrao + c) != dicionario.end()) {
            padrao += c;
        } else { // insere a combinacao nova combinacao "string + c" no dicionario
            saida.push_back(dicionario[padrao]);
            dicionario[padrao + c] = code;
            code++;
            padrao = c;
        }
    }
    saida.push_back(dicionario[padrao]);

    return saida;
}

string CompressaoLZW::descomprime(vector<int> codes) {
    string saida;
    vector<string> dicionario;
    for (int i = 0; i < 128; i++)
    {
        string aux = "";
        aux += char(i);
        dicionario.push_back(aux);
    }

    int prevCode = codes[0];
    saida += dicionario[prevCode];
    for (int i = 1; i < codes.size(); i++)
    {
        if (codes[i] >= dicionario.size()) {
            string newCombination = dicionario[prevCode];
            newCombination += dicionario[prevCode].back();
            dicionario.push_back(newCombination);
            saida += dicionario[codes[i]];
        } else {
            saida += dicionario[codes[i]];
            dicionario.push_back(dicionario[prevCode] + dicionario[codes[i]].at(0));
        }

        prevCode = codes[i];
    }

    return saida;
}

string CompressaoLZW::descomprime(string str) {
    vector<int> code;

    string currentCode;
    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) == ' ') {
            code.push_back(stoi(currentCode));
            currentCode = "";
        } else {
            currentCode += str.at(i);
        }
    }

    return descomprime(code);
    
    
    

}