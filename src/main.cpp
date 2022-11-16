#include <bits/stdc++.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <random>

#include "./header/AlgoritmosOrdenacao.h"
#include "./header/HashTable.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/ProductReview.h"

using namespace std;

// Funcoes de Teste

void printArrayProd(ProductReview* arr, int tam) {
    for (int i = 0; i < tam; i++)
        arr[i].print();
}

void printArray(int* arr, int tam) {
    for (int i = 0; i < tam; i++)
        cout << arr[i] << endl;
}

// Etapa 1: Processamento dos dados
// https://www.kaggle.com/datasets/saurav9786/amazon-product-reviews

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

    // CHAVE RANDOMICA
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, n);

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(distr(gen));

    return produtos;
}

// Etapa 2: Análise de algoritmos de ordenação

void sort(ProductReview* vet, int n, int methodId) {
    AlgoritmosOrdenacao algoritmo;

    switch (methodId) {
        case 0:
            algoritmo.quickSort(vet, n);
            break;
        case 1:
            algoritmo.mergeSort(vet, n);
            break;
        case 2:
            algoritmo.timSort(vet, n);
            break;
    }
}

void testarAlgoritmo(int methodId, int M, int* N, int sizeN) {
    ProductReview* vet;
    string metodosOrdenacao[3] = {"Quick Sort", "Merge Sort", "TimSort"};

    cout << "ANALISE ALGORITMO ORDENACAO: " << metodosOrdenacao[methodId] << endl;

    for (int j = 0; j < sizeN; j++) {
        for (int i = 0; i < M; i++) {
            vet = import(N[j]);
            sort(vet, N[j], methodId);
        }

        // Gerando resultados parciais ..., true)
        arq.gerarResultado(N[j], methodId, j * M, true);
    }

    // Gerando resultado final ..., false)
    arq.gerarResultado(N[0], methodId, 0, false);
    arq.resetTempFile();

    remove("./src/files/temp.bin");
    delete[] vet;
}

void etapaOrdenacao(int M) {
    cout << "EXECUTANDO ETAPA DE ORDENACAO" << endl;

    int size;
    int* N = arq.readInput(size);

    arq.clearOutputFile();

    // Testando Algoritmo 0 - Quick Sort
    testarAlgoritmo(0, M, N, size);

    // Testando Algoritmo 1 - Merge Sort
    testarAlgoritmo(1, M, N, size);

    // Testando Algoritmo 2 - TimSort
    testarAlgoritmo(2, M, N, size);

    delete[] N;
}

void etapaHash() {
    cout << "EXECUTANDO ETAPA DE HASH" << endl;
    cout << "quantos itens inserir na tabela:" << endl;
    int n;
    std::cin >> n;

    HashTable hTable((int)(n * 0.3));

    ProductReview* pr = import(n);

    for (int i = 0; i < n; i++) {
        hTable.insere(pr[i]);
    }
    hTable.print();

    delete [] pr;
}

RegistroHash* createTable(int n) {
    HashTable hTable((int)(n * 0.3));

    ProductReview* pr = import(n);

    for (int i = 0; i < n; i++) {
        hTable.insere(pr[i]);
    }
    delete [] pr;
    
    return hTable.getTable();
}

void interface() {
    int option;
    do {
        cout << "Escolha qual etapa sera executada: " << endl
             << "1. Ordenacao" << endl
             << "2. Hash" << endl
             << "0. Sair" << endl
             << "> " << flush;
        cin >> option;

        if (option == 1)
            etapaOrdenacao(3);
        else if (option == 2)
            etapaHash();

    } while (option != 0);
}

int main(int argc, char* arg[]) {
    string PATH;

    if (argc == 2)
        PATH = arg[1];

    arq.setPath(PATH);
    createBinary(PATH);
    interface();

    return 0;
}