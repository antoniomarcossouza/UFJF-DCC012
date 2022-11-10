#include "Bucket.h"
#include <iomanip>

Bucket::Bucket(int size)
{
    this->size = size;
    items = new RegistroHash[size];

    for (int i = 0; i < size; i++)
    {
        items[i].qtdReviews = 0;
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
    return items[index].productId; 
}

/*
    Adiciona um item. Retorna 1 se o item foi adicionado e 0 se o item era repitido
*/
int Bucket::addItem(string productId)
{
    // retorna 0 se o item já está no balde ou no overflow
    Bucket* bucket = this;
    while (bucket)
    {
        for (int i = 0; i < bucket->getItemCount(); i++)
        {
            if (bucket->getItem(i) == productId)
            {
                items[i].qtdReviews++;
                return 0;
            }
        }
        bucket = bucket->getOverflowBucket();
    }
    

    if (itemCount < size)
    {
        items[itemCount].productId = productId;
        items[itemCount].qtdReviews++;
        itemCount++;
        return 1;
    }
    else
    {
        // insercao no overflow
        if (!overflowBucket)
        {
            overflowBucket = new Bucket(size);
        }
        overflowBucket->addItem(productId);
        return 0;
    }
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
        items[i].qtdReviews = items[i+1].qtdReviews;
    }

    items[itemCount-1].productId = "";
    items[itemCount-1].qtdReviews = 0;
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
        if(items[i].productId == productId)
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
        cout <<"|" << std::setw(15) << items[i].productId << "|" << std::setw(4) << items[i].qtdReviews << "|" << endl;
    }

    if (overflowBucket)
    {
        cout << " v v v v v v v v v v" << endl;
        overflowBucket->print();
    }
}