/*
    Compile esse arquivo com os mesmos argumetos do main para testar a tabela hash
    g++ testeHash.cpp header/*.cpp -I header -o testeHash && ./testeHash ./files/

    altere TAM para escplher o tamanho da tabela
*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <random>
#include <stdlib.h>

#include "./header/ProductReview.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/AlgoritmosOrdenacao.h"
#include "./header/HashTable.h"

#define TAM 1000

using namespace std;

ManipulandoArquivo arq;
void createBinary(string path)
{
    arq.preProcessamento(path);
}

ProductReview getRandomPR()
{
    // CHAVE RANDOMICA
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 100);

    return arq.findRegistryPosition(distr(gen));
}

int main(int argc, char* arg[])
{
    string PATH;
    HashTable hash(TAM);
    int colisoes = 0;

    if (argc == 2) 
        PATH = arg[1];

    arq.setPath(PATH); 
    createBinary(PATH);

    for (int i = 0; i < TAM; i++)
    {
        ProductReview pr = getRandomPR();
        colisoes += hash.insereCount(pr);
    }
    
    hash.print();
    cout << "============================" << endl;
    cout << "Total de colisoes: " << colisoes << endl;

    
    return 0;
}