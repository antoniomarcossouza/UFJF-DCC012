#include "HashTable.h"
#include <math.h>

#include <iostream> // TESTE
#include <iomanip>  // TESTE

HashTable::HashTable(int tamanho)
{
    this->tamanho = tamanho;
    info = new ProductReview[tamanho];
    next = new int[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        next[i] = -2;
    }
    
}

HashTable::~HashTable()
{
    delete [] info;
    delete [] next;
}

int HashTable::hash(ProductReview productReview)
{
    string key = productReview.getProductId();
    int sum = 0;

    for (int i = 0; i < key.length(); i++)
    {
        sum += key.at(i);
    }
    

    cout << endl << " >>> >>> " << (int)key.at(0) << " % " << tamanho << " = " << key.at(0) % tamanho << endl;

    return sum % tamanho;   
}

void HashTable::insere(ProductReview productReview)
{
    int key = hash(productReview);
    int previousKey;
    cout << "inserindo PR na posicao: " << key << endl; 
    int contColisoes = 0;               // TESTE

    if (next[key] != -2)
    {   
        previousKey = key;
        key = tamanho-1;
        contColisoes++;                 // TESTE
        while (next[key] != -2)
        {
            key--;
            contColisoes++;             // TESTE
        }
        std::cout << contColisoes << " colisoes" << endl;         // TESTE
        next[previousKey] = key;
    }
    else {std::cout << "Nenhuma colisao" << endl; }     // TESTE

    info[key] = productReview;
    next[key] = -1;
}

int HashTable::insereCount(ProductReview productReview)
{
    int key = hash(productReview);
    int previousKey;
    cout << "inserindo PR na posicao: " << key << endl; 
    int contColisoes = 0;               // TESTE

    if (next[key] != -2)
    {   
        previousKey = key;
        key = tamanho-1;
        contColisoes++;                 // TESTE
        while (next[key] != -2)
        {
            key--;
            contColisoes++;             // TESTE
        }
        std::cout << contColisoes << " colisoes" << endl;         // TESTE
        next[previousKey] = key;
    }
    else {std::cout << "Nenhuma colisao" << endl; }     // TESTE

    info[key] = productReview;
    next[key] = -1;

    return contColisoes;
}

void HashTable::print()
{
    for (int i = 0; i < tamanho; i++)
    {
        std::cout << std::setw(4) << i << "| " << std::setw(15) << info[i].getProductId() << " | " << std::setw(5) << next[i] << " |" << endl;
    }

    std::cout << endl;
}