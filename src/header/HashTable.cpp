#include "HashTable.h"

#include "AlgoritmosOrdenacao.h"
#include <math.h>

HashTable::HashTable(int tamanho)
{
    while(!isPrime(tamanho)) // o tamanho da tablea precisa ser impar
    {
        tamanho++;
    }

    this->tamanho = tamanho;
    vet = new RegistroHash[tamanho];
    qtdItens = 0;

    for (int i = 0; i < tamanho; i++)
    {
        vet[i].productId = "";
        vet[i].qtdReviews = 0;
    }
}

HashTable::~HashTable()
{
    delete [] vet;
}

bool HashTable::isPrime(int n)
{
    for (int i = 2; i < n/2; i++)
        if (n % i == 0)
            return false;
 
    return true;
}

int HashTable::hash(string productId, int i)
{
    unsigned key = 0;
    for (int j = 0; j < productId.length(); j++)
    {
        key += productId.at(j);
    }

    return (h1(key) + i*h2(key)) % tamanho;
}

int HashTable::h1(unsigned key)
{
    return key % tamanho;
}

int HashTable::h2(unsigned key)
{
    return 1 + (key % (tamanho-2));
}

void HashTable::insere(ProductReview newReview)
{
    if(qtdItens >= tamanho)
    {
        cout << "Capacidade maxima da tabela atingida" << endl;
        return;
    }

    int index = hash(newReview.getProductId(), 0);
    int qtdColisoes = 0;

    while(vet[index].qtdReviews != 0)
    {
        if (vet[index].productId == newReview.getProductId())
        {
            vet[index].qtdReviews++;
            return;
        }

        qtdColisoes++;
        index = hash(newReview.getProductId(), qtdColisoes);
    }

    vet[index].productId = newReview.getProductId();
    vet[index].qtdReviews = 1;
    qtdItens++;

}

RegistroHash* HashTable::getTable()
{
    return vet;
}

void HashTable::print()
{
    RegistroHash* aux = new RegistroHash[tamanho];

    for(int i = 0; i < tamanho; i++)
    {
        aux[i] = vet[i];
    }

    AlgoritmosOrdenacao algoritmo;
    algoritmo.quickSortHash(aux, tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        cout << " | " << setw(10) << aux[i].productId << " | " << setw(3) << aux[i].qtdReviews << " | " << endl;
    }

    delete [] aux;
}
