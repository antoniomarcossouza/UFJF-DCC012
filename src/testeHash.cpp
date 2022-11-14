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
#include <math.h>

#include "./header/ProductReview.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/AlgoritmosOrdenacao.h"
#include "./header/HashTable.h"



#define TAM 50000
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
    uniform_int_distribution<> distr(0, 1000000);
    
    return arq.findRegistryPosition(distr(gen));
}


int main(int argc, char* arg[])
{
    string PATH;
    HashTable hTable(0.2 * TAM);

    if (argc == 2) 
        PATH = arg[1];

    arq.setPath(PATH); 
    createBinary(PATH);

    cout << "iniciando" << endl;
    ProductReview pr;
    for (int i = 0; i < TAM; i++)
    {
        pr = getRandomPR();
        hTable.insere(pr);
    }
    hTable.print();

    
    return 0;
}