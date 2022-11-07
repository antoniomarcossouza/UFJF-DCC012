#include "HashTable.h"
#include <math.h>

HashTable::HashTable(int listSize, int bucketSize, float maxLoadFactor)
{
    this->listSize = listSize;
    this->bucketSize = bucketSize;
    this->maxLoadFactor = maxLoadFactor;
    this->overflow = 2;
    n = listSize;
    g = 0;
    splitPointer = 0;
    itemCount = 0;

    for (int i = 0; i < listSize; i++)
    {
        bucketList.push_back(new Bucket(bucketSize));
    }
    
}

HashTable::~HashTable()
{
    for(int i = 0; i < bucketList.size(); ++i)
        delete bucketList[i];
}


int HashTable::hash(string productId)
{
    int key = 0;
    for (int i = 0; i < productId.length(); i++)
    {
        key += productId.at(i);
    }


    int hashValue = key % ((int)pow(2, g) * n);

    if (hashValue < splitPointer)
    {
        hashValue = key % ((int)pow(2, g+1) * n);
    }

    return hashValue;   
}

float HashTable::loadFactor()
{
    return (float)itemCount / (bucketList.size() * (bucketSize)); // nao levando em conta o overflow por enquanto
}

void HashTable::insere(ProductReview pr)
{
    int hashValue = hash(pr.getProductId());
    itemCount += bucketList[hashValue]->addItem(pr.getProductId());

    if(loadFactor() > maxLoadFactor)
        split();

}

void HashTable::split()
{
    Bucket* newBucket = new Bucket(bucketSize);
    bucketList.push_back(newBucket);
    listSize++;
    Bucket* splitBucket = bucketList[splitPointer];
    splitPointer++;

    while (splitBucket != NULL)
    {
        for (int i = 0; i < splitBucket->getItemCount(); i++)
        {
            string productId = splitBucket->getItem(i);
            int hashValue = hash(productId);

            if (hashValue != splitPointer-1)
            {
                splitBucket->removeItem(i);
                newBucket->addItem(productId);
                i--;
            }
        }
        splitBucket = splitBucket->getOverflowBucket();
    }

    if (splitPointer == n*g)
    {
        splitPointer = 0;
        g++;    
    }
}

void HashTable::print()
{
    cout << endl << "loadFactor: " << (float)loadFactor() << endl;
    for(int i = 0; i < bucketList.size(); i++)
    {
        Bucket *b = bucketList[i];
        cout << "balde " << i << endl;
        b->print();
        cout << endl;
    }
}