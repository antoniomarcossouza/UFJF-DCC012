#ifndef BUCKET_H
#define BUCKET_H

#include "ProductReview.h"
#include "RegistroHash.h"

using namespace std;

class Bucket
{   
    private:
        RegistroHash *items;
        int size;
        int itemCount;
        Bucket *overflowBucket;
        int g;
    public:
        Bucket(int size);
        ~Bucket();
        int addItem(string productId);
        string getItem(int index);
        void removeItem(int index);
        void removeItem(string productId);
        int getItemCount();
        int getG();
        void setG(int g);
        Bucket* getOverflowBucket();

        void print();
};

#endif