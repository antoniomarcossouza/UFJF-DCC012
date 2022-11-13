#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iomanip>
#include "ProductReview.h"
#include "RegistroHash.h"

using namespace std;

class HashTable
{   
    private:
        RegistroHash *vet;
        int tamanho;
        int qtdItens;

        bool isPrime(int n);

    public:
        HashTable(int tamanho);
        ~HashTable();

        RegistroHash* getTable();
        int hash(string productId, int i);
        int h1(unsigned key);
        int h2(unsigned key);
        void insere(ProductReview productReview);
        //procura(ProductReview productReview);
        void print();
};

#endif