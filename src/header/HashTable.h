#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iomanip>
#include "ProductReview.h"
#include "HashNode.h"

using namespace std;

class HashTable
{   
    private:
        HashNode **vet;
        int tamanho;

    public:
        HashTable(int tamanho);
        ~HashTable();

        int hash(string productId);
        void insere(ProductReview productReview);
        HashNode* procura(ProductReview productReview);
        void print();
};

#endif