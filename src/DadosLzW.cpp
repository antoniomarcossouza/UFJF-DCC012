/*
g++ ./src/DadosLzW.cpp ./src/header/*.cpp -I ./src/header -o ./src/DadosLzW && ./src/DadosLzW ./src/files/
*/
#include <bits/stdc++.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "header/ProductReview.h"
#include "header/CompressaoLZW.h"
#include "header/ManipulandoArquivo.h"

using namespace std;

ManipulandoArquivo arq;
ProductReview* import(int n) {
    ProductReview* produtos = new ProductReview[n];
    vector<int> numbers(n + 90000);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 7000000);

    generate(numbers.begin(), numbers.end(), [&] { return dis(gen); });
    sort(numbers.begin(), numbers.end());

    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

    while (numbers.size() > n)
        numbers.pop_back();

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(numbers[i]);

    return produtos;
}

void gerarResultados() {
    ofstream outfile("./src/DadosCompressao/lzw_data.txt");
    ofstream taxaMedia("./src/DadosCompressao/taxa_media_de_compressao_lzw.txt");
    if (!outfile) {
        cout << "ERRO ao abrir ./src/DadosCompressao/lzw_data.txt" << endl;
        exit(1);
    }
    if (!taxaMedia) {
        cout << "ERRO ao abrir ./src/DadosCompressao/taxa_media_de_compressao_lzw.txt" << endl;
        exit(1);
    }

    for (int k = 10; k <= 1000; k += 10)
    {
        int qtdImports = k;
        double mediaCompressão = 0;
        int mediaChars = 0;
        outfile << " " << k << " imports = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl << endl;
        for (int i = 0; i < 3; i++) {
            string str;
            ProductReview* pr = import(qtdImports);
            for (int i = 0; i < qtdImports; i++) {
                str.append(pr[i].toString());
            }

            int tamOrig = str.length() * sizeof(char);
            vector<unsigned short> compress = CompressaoLZW::comprime(str);
            int tamCompress = compress.size() * sizeof(unsigned short);
            double taxa = ((double)tamOrig - (double)tamCompress) / (double)tamOrig;
            mediaCompressão += taxa;
            mediaChars += tamOrig;

            outfile << "\t"<< i+1 << "ª execucao" << endl;
            outfile << "\t\tstring original: " << tamOrig << " bytes" << endl;
            outfile << "\t\tstring comprimida: " << tamCompress << " bytes" << endl;
            outfile << "\t\ttaxa de compressao: " << (double)taxa * 100 << "%" << endl << endl;
        }
        mediaCompressão = mediaCompressão / 3;
        mediaChars = mediaChars / 3;
        outfile << "\tMedia final de compressão: " << mediaCompressão * 100 << "%" << endl; 
        taxaMedia << mediaCompressão << endl;
        outfile << "\tMedia de caracteres: " << mediaChars << endl << endl;
    }
}

int main(int argc, char* arg[]) {
    string PATH; if (argc == 2) PATH = arg[1]; arq.setPath(PATH); arq.preProcessamento(PATH);

/*
    string txt = "string qualquer"; //arq.getReviews();
    
    cout << "Original:" << endl;
    cout << txt << endl << endl;

    string comprimida = CompressaoLZ77::comprime(txt);
    cout << "Comprimida:" << endl;
    cout << comprimida;
    cout << endl << endl;

    string legivel = "";
    for (int i = 0; i+2 < comprimida.size(); i += 3)
        {
            legivel += "(";
            legivel += to_string(comprimida.at(i));
            legivel += ",";
            legivel += to_string(comprimida.at(i+1));
            legivel += ",";
            
            if (comprimida.at(i+2) == '\0')
                legivel += "NULL";
            else if (comprimida.at(i+2) == '\n')
                legivel += "/n";
            else
                legivel += comprimida.at(i+2);
            legivel += ")";
            
        }
    cout << "Legivel:" << endl;
    cout << legivel;
    cout << endl << endl;

    string descomprimida = CompressaoLZ77::descomprime(comprimida);
    cout << "Descomprimida:" << endl;
    cout << descomprimida << endl << endl; */

    gerarResultados();
}
