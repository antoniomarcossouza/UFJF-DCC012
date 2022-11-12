#ifndef HASHNODE_H
#define HASHNODE_H

#include "RegistroHash.h"
#include "ProductReview.h"

class HashNode
{
    private:
        RegistroHash val;
        HashNode *next;

    public:
        HashNode(ProductReview review);
        void setNext(HashNode *next);
        HashNode* getNext();
        string getProductId();
        int getQtdReviews();
        void incrementaQtdReviews();
};


#endif
