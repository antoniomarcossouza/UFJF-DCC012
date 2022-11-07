#include "Bucket.h"
#include <iomanip>

Bucket::Bucket(int size)
{
    this->size = size;
    items = new string[size];
    repeatedItemCount = new int[size];

    for (int i = 0; i < size; i++)
    {
        repeatedItemCount[i] = 0;
    }
    
    
    itemCount = 0;
    g = 0;
    overflowBucket = NULL;
}

// Insere o productId de um ProductReview no balde
Bucket::~Bucket()
{
    delete [] items;
    delete overflowBucket;
}

// Retorna a string no index
string Bucket::getItem(int index) 
{ 
    return items[index]; 
}

/*
    Adiciona um item. Retorna 1 se o item foi adicionado e 0 se o item era repitido
*/
int Bucket::addItem(string productId)
{
    // sem itens repitidos
    Bucket* bucket = this;
    while (bucket)
    {
        for (int i = 0; i < bucket->getItemCount(); i++)
        {
            if (bucket->getItem(i) == productId)
            {
                repeatedItemCount[i]++;
                return 0;
            }
        }
        bucket = bucket->getOverflowBucket();
    }
    

    if (itemCount < size)
    {
        items[itemCount] = productId;
        repeatedItemCount[itemCount]++;
        itemCount++;
    }
    else
    {
        // insercao com overflow
        if (!overflowBucket)
        {
            overflowBucket = new Bucket(size);
        }
        overflowBucket->addItem(productId);
    }
    return 1;
}

/* 
    Remove o item no index _index_ nesse balde.
    Reposiocionando os itens no começo do array.
*/
void Bucket::removeItem(int index)
{
    for (int i = index; i < itemCount-1; i++)
    {
        items[i] = items[i+1];
        repeatedItemCount[i] = repeatedItemCount[i+1];
    }

    items[itemCount-1] = "";
    repeatedItemCount[itemCount] = 0;
    itemCount--;
}

/* 
    Procura o item (nesse balde e nos baldes de overflow), remove e reposiociona os itens no começo do array.
*/
void Bucket::removeItem(string productId)
{
    bool itemFound = false;
    for (int i = 0; i < itemCount; i++)
    {
        if(items[i] == productId)
        {
            itemFound = true;
            removeItem(i);
            itemCount--;
            return;
        }
    }

    if (!itemFound && overflowBucket)
        overflowBucket->removeItem(productId);
}

// Retorna a quantidade de itens no balde
int Bucket::getItemCount() 
{ 
    return itemCount; 
}

// Retorna o level do balde
int Bucket::getG() 
{ 
    return g; 
}

void Bucket::setG(int g)
{
    this->g = g;
}

// Retorna o balde de overflow
Bucket* Bucket::getOverflowBucket()
{
    return overflowBucket;
}

void Bucket::print()
{
    for (int i = 0; i < size; i++)
    {
        cout <<"|" << std::setw(15) << items[i] << "|" << std::setw(4) << repeatedItemCount[i] << "|" << endl;
    }

    if (overflowBucket)
    {
        cout << " v v v v v v v v v v" << endl;
        overflowBucket->print();
    }
}
