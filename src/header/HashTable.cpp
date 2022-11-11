#include "HashTable.h"
#include <math.h>

HashTable::HashTable(int tamanho)
{
    this->tamanho = tamanho;
    vet = new HashNode*[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        vet[i] = NULL;
    }
    
}

HashTable::~HashTable()
{
    delete [] vet;
}

int HashTable::hash(string productId)
{
    unsigned key = 0;
    for (int i = 0; i < productId.length(); i++)
    {
        key += productId.at(i);
    }

    double kA = key * (sqrt(5) - 1) / 2;
    return floor(tamanho * (kA - (int)kA));

}

void HashTable::insere(ProductReview newReview)
{
    int id = hash(newReview.getProductId());

    HashNode* node = procura(newReview);
    if (node != NULL)
    {
        node->incrementaQtdReviews();
    }
    else
    {
        HashNode* newNode = new HashNode(newReview);
        if (vet[id] == NULL)
        {
            vet[id] = newNode;
        }
        else
        {
            newNode->setNext(vet[id]);
            vet[id] = newNode;
        }
    }    
}


HashNode* HashTable::procura(ProductReview review)
{
    int id = hash(review.getProductId());
    
    HashNode *p = vet[id];
    while (p != NULL)
    {
        if (p->getProductId() == review.getProductId())
        {
            return p;
        }
        p = p->getNext();
    }

    return NULL;
}

void HashTable::print()
{
    for (int i = 0; i < tamanho; i++)
    {
        cout << i << "| ";
        HashNode* p = vet[i];
        if (p != NULL)
        {
            cout << p->getProductId() << " {" << p->getQtdReviews() << "}";
            p = p->getNext();
            while (p != NULL)
            {
                cout << " -> ";
                cout << "| " << p->getProductId() << " {" << p->getQtdReviews() << "}";
                p = p->getNext();
            }
        }
        cout << endl;
    }
}
