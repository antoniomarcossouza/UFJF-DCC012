#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ProductReview.h"
#include "Bucket.h"
#include <vector>

using namespace std;

class HashTable
{   
    private:
        vector<Bucket*> bucketList;
        int listSize;
        int bucketSize;
        float maxLoadFactor;
        int g;
        int n; // numero original de baldes no nível g (antes de qualquer divisão)

        int itemCount;
        int splitPointer;

        int hash(string productId);
        void split();

    public:
        HashTable();
        HashTable(int listSize, int bucketSize, float maxLoadFactor);
        ~HashTable();

        float loadFactor();
        void insere(ProductReview productReview);
        int getProductCount(string productId);

    // PARA TESTES

        void print();
};

#endif