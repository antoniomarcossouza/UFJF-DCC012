#include <cstdlib>
#include <string>
#include <ctime>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "ProductReview.h"
#include "ArvoreB.h"
#include "ManipulandoArquivo.h"
#include "ArvoreVP.h"

using namespace std;

ManipulandoArquivo arq;
void createBinary(string path) {
    arq.preProcessamento(path);
}

void getReview(int i) {
    ProductReview prod;

    prod = arq.findRegistryPosition(i);
    prod.print();
}

ProductReview* import(int n) {
    ProductReview* produtos = new ProductReview[n];
    vector<int> numbers(n + 90000);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 7000000);

    generate(numbers.begin(), numbers.end(), [&]{ return dis(gen);});
    sort(numbers.begin(), numbers.end());

    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

    while (numbers.size() > n)
        numbers.pop_back();

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(numbers[i]);

    return produtos;
}

void printPrompt(ProductReview *vet, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if(vet == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if(imp == 's')
    {
        for(int i = 0; i < n; i++)
            vet[i].print();
    }
}

void printPrompt(ArvoreVP *arv, int n)
{
     char imp;
     cout << "Imprimir (s/n): ";
    cin >> imp;

     if(arv == NULL)
         cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
     else if(imp == 's')
         arv->print();
}

void printPrompt(ArvoreB *arv, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if(arv == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if(imp == 's')
        arv->print();
}

ProductReview* randomTest(int n)
{
    ProductReview *vet = new ProductReview[n];

    for(int i = 0; i < n; i++)
    {
        string u("STR");
        u += 'a'+rand()%('z'-'a');
        // vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
        vet[i].setUserId(u);
    }

    return vet;
}

template<typename T>
void treeTest(T arv, ProductReview *vet, int n)
{
    for(int i = 0; i < n; i++)
        arv->insere(&vet[i]);
    printPrompt(vet, n);

    string userId, productId;
    cout << "Digite um par (userId, productId) para busca: ";
    cin >> userId >> productId;
    while(userId != "quit")
    {
        ProductReview *p = arv->busca(userId, productId);
        if(p != NULL)
            p->print();
        else
            cout << "Produto nao encontrado!" << endl;
        
        cout << "Digite outro par (userId, productId) para busca: ";
        cin >> userId >> productId;
    }
}

// void compressTest(int method)
// {
//     switch(method)
//     {
//         case 0: cout << "=== Teste Huffman ===" << endl << endl; break;
//         case 1: cout << "=== Teste LZ77 ===" << endl << endl; break;
//         case 2: cout << "=== Teste LZW ===" << endl << endl; break;
//         default: cout << "Metodo de compressao nao suportado" << endl << endl; break;
//     }
    
//     cout << "Testando strings..." << endl;

//     string str = "string qualquer";
//     string comp = comprime(str, method);
//     string orig = descomprime(str, method);

//     cout << "String comprimida: " << comp << endl;
//     cout << "String descomprimida: " << orig << endl << endl;

//     cout << "Testando arquivos..." << endl;

//     comprime(method); // essa função deve comprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsOrig.txt'
//     descomprime(method); // essa função deve descomprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsComp.bin'
// }

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
        // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
        std::string path(argv[1]);
        createBinary(path);

        int registerIdx;
        cout << "Digite um indice de registro (-1 para sair): ";
        cin >> registerIdx;
        while (registerIdx != -1)
        {
            getReview(registerIdx);
            cout << "Digite outro indice de registro (-1 para sair): ";
            cin >> registerIdx;
        }

        ProductReview *vet = 0;
        ArvoreVP *arv_vp = 0;
        ArvoreB *arv_b = 0;
        int option, n;
        do
        {
            cout << "[1] Vetor de teste" << endl 
                << "[2] Importar registros" << endl
                << "[3] Arvore vermelho-preto" << endl
                << "[4] Arvore B" << endl
                << "[5] Huffman" << endl
                << "[6] LZ77" << endl
                << "[7] LZW" << endl
                << "[0] Sair" << endl;

            cout << "Digite uma opcao de menu: ";
            cin >> option;
            switch (option)
            {
                case 1:
                    n = 10;
                    delete [] vet;
                    vet = randomTest(n);
                    printPrompt(vet, n);
                    break;
                case 2:
                    cout << "Quantos registros deseja importar? ";
                    cin >> n;
                    delete [] vet;
                    vet = import(n);
                    printPrompt(vet, n);
                    break;
                case 3:
                    delete arv_vp;
                    arv_vp = new ArvoreVP();
                    treeTest(arv_vp, vet, n);
                    break;
                case 4:
                    delete arv_b;
                    arv_b = new ArvoreB();
                    treeTest(arv_b, vet, n);
                    break;
                case 5:
                    // compressTest(0);
                    break;
                case 6:
                    // compressTest(1);
                    break;
                case 7:
                    // compressTest(2);
                    break;
                default:
                    break;
            }
        } while(option != 0);

        delete [] vet;
        delete arv_vp;
        delete arv_b;
    }

    return 0;
}