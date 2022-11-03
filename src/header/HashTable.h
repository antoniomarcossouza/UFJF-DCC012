#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ProductReview.h"

using namespace std;

class HashTable
{   
    private:
        ProductReview *info;
        int *next;
        int tamanho;
        int hash(ProductReview productReview);
    public:
        HashTable(int tamanho);
        ~HashTable();
        // Insere um ProductReview na tabela
        void insere(ProductReview productReview);
        ProductReview busca(string productId);

    // PARA TESTES

        void print();
        //Retorna o numero de colisoes
        int insereCount(ProductReview productReview);
};

#endif