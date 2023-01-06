#include <bits/stdc++.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "./header/AlgoritmosOrdenacao.h"
#include "./header/HashTable.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/ProductReview.h"
#include "./header/ArvoreB20.h"
#include "./header/ArvoreB200.h"
#include "./header/CompressaoLZ77.h"

using namespace std;
using namespace std;
using namespace std::chrono;
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
    uniform_int_distribution<> distr(0, 7000000);

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
    string metodosOrdenacao[3] = {"Quick Sort", "Merge Sort", "TimSort"};

    cout << "ANALISE ALGORITMO ORDENACAO: " << metodosOrdenacao[methodId] << endl;

    for (int j = 0; j < sizeN; j++) {
        for (int i = 0; i < M; i++) {
            ProductReview* vet = import(N[j]);
            sort(vet, N[j], methodId);
            delete[] vet;
        }

        // Gerando resultados parciais ..., true)
        arq.gerarResultado(N[j], methodId, j * M, true);
    }

    // Gerando resultado final ..., false)
    arq.gerarResultado(N[0], methodId, 0, false);
    arq.resetTempFile();

    remove("./src/files/temp.bin");
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

void randomVetIndex(vector<int>& numbers) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 7000000);

    generate(numbers.begin(), numbers.end(), [&]{ return dis(gen);});
    sort(numbers.begin(), numbers.end());

    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
}

ProductReview* importSemRepeticao(int n, int& size) {
    ProductReview* produtos = new ProductReview[n];
    vector<int> numbers(n + 90000);
    randomVetIndex(numbers);

    while (numbers.size() > n)
        numbers.pop_back();

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(numbers[i]);


    return produtos;
}

void arvoreB20() {
    // IMPORTANDO UM CONJUNTO DE 1M ELEMENTOS
    int size;
    int M = 3;
    int N = 1000000;
    int B = 100;

    double* timeResultsInsersion = new double[M];
    double* timeResultsSearch = new double[M];
    int* comparacoesResultsInsersion = new int[M];
    int* comparacoesResultsSearch = new int[M];

    for (int j = 0; j < M; j++) {
        ProductReview* prodsToImport = importSemRepeticao(N, size);
        ArvoreB20 arvoreB20;


        // REALIZANDO INSERCAO
        high_resolution_clock::time_point inicioInsere = high_resolution_clock::now();

        for (int i = 0; i < size; i++)
            arvoreB20.insere(&prodsToImport[i]);

        high_resolution_clock::time_point fimInsere = high_resolution_clock::now();
        double insersionTime = duration_cast<duration<double>>(fimInsere - inicioInsere).count();

        // REALIZANDO BUSCA
        high_resolution_clock::time_point inicioBusca = high_resolution_clock::now();

        ProductReview* prodsToSearch = import(B);
        for (int i = 0; i < B; i++) {
            ProductReview* res = arvoreB20.busca(prodsToImport[i].getUserId(), prodsToImport[i].getProductId());
            delete res;
        }

        high_resolution_clock::time_point fimBUsdca = high_resolution_clock::now();
        double searchTime = duration_cast<duration<double>>(fimBUsdca - inicioBusca).count();

        timeResultsInsersion[j] = insersionTime;
        timeResultsSearch[j] = searchTime;
        comparacoesResultsInsersion[j] = arvoreB20.getComparacoesInsercao();
        comparacoesResultsSearch[j] = arvoreB20.getComparacoesBusca();

        delete [] prodsToImport;
        delete [] prodsToSearch;
    }

    arq.gerarResultadoEB(timeResultsInsersion, timeResultsSearch, comparacoesResultsInsersion, comparacoesResultsSearch, "Arvore B m = 20");

    delete [] timeResultsInsersion;
    delete [] timeResultsSearch;
    delete [] comparacoesResultsInsersion;
    delete [] comparacoesResultsSearch;
}

void arvoreB200() {
    // IMPORTANDO UM CONJUNTO DE 1M ELEMENTOS
    int size;
    int M = 3;
    int N = 1000000;
    int B = 100;

    double* timeResultsInsersion = new double[M];
    double* timeResultsSearch = new double[M];
    int* comparacoesResultsInsersion = new int[M];
    int* comparacoesResultsSearch = new int[M];

    for (int j = 0; j < M; j++) {
        ProductReview* prodsToImport = importSemRepeticao(N, size);
        ArvoreB200 arvoreB200;


        // REALIZANDO INSERCAO
        high_resolution_clock::time_point inicioInsere = high_resolution_clock::now();

        for (int i = 0; i < size; i++)
            arvoreB200.insere(&prodsToImport[i]);

        high_resolution_clock::time_point fimInsere = high_resolution_clock::now();
        double insersionTime = duration_cast<duration<double>>(fimInsere - inicioInsere).count();

        // REALIZANDO BUSCA
        high_resolution_clock::time_point inicioBusca = high_resolution_clock::now();

        ProductReview* prodsToSearch = import(B);
        for (int i = 0; i < B; i++) {
            ProductReview* res = arvoreB200.busca(prodsToImport[i].getUserId(), prodsToImport[i].getProductId());
            delete res;
        }

        high_resolution_clock::time_point fimBUsdca = high_resolution_clock::now();
        double searchTime = duration_cast<duration<double>>(fimBUsdca - inicioBusca).count();

        timeResultsInsersion[j] = insersionTime;
        timeResultsSearch[j] = searchTime;
        comparacoesResultsInsersion[j] = arvoreB200.getComparacoesInsercao();
        comparacoesResultsSearch[j] = arvoreB200.getComparacoesBusca();

        delete [] prodsToImport;
        delete [] prodsToSearch;
    }

    arq.gerarResultadoEB(timeResultsInsersion, timeResultsSearch, comparacoesResultsInsersion, comparacoesResultsSearch, "Arvore B m = 200");

    delete [] timeResultsInsersion;
    delete [] timeResultsSearch;
    delete [] comparacoesResultsInsersion;
    delete [] comparacoesResultsSearch;
}

void etapaEstruturasBalanceadas() {
    arq.clearOutputFile();
    // ARVORE VERMELHO E PRETO
        // ESPAÇO PARA FAZER O PROCESSO DE ANALISE

    // ARVORE B
    arvoreB20();
    arvoreB200();
}

string comprime(string str, int metodo) {
    if (metodo == 0) {
        //  Huffman
        // retorna a string comprimida
    }
    else if (metodo == 1) {
        // LZ77
        return CompressaoLZ77::comprime(str);
    }
    else if (metodo == 2) {
        // LZW
        // retorna a string comprimida
    }
}

string descomprime(string str, int metodo) {
    if (metodo == 0) {
        //  Huffman
        // retorna a string descomprimida
    }
    else if (metodo == 1) {
        // LZ77
        // retorna a string descomprimida
    }
    else if (metodo == 2) {
        // LZW
        // retorna a string descomprimida
    }
}

void comprime(int metodo) {
    /*
        comprime o conteúdo de um arquivo texto nomeado reviewsOrig.txt, utilizando o método especificado 
        no segundo parâmetro (0 = Huffman, 1 = LZ77, 2 = LZW). A função deve salvar o resultado da compressão
        em um arquivo binário reviewsComp.bin. Ambos os arquivos deverão estar localizados no caminho fornecido 
        pelo usuário via linha de comando (vide Seção 5). 
    */
}

void descomprime(int metodo) {
    /*
        descomprime o conteúdo do arquivo binário reviewsComp.bin, utilizando o método especificado no segundo
        parâmetro (0 = Huffman, 1 = LZ77, 2 = LZW). A função deve salvar o resultado da descompressão em um arquivo texto
        reviewsDesc.txt. Ambos os arquivos deverão estar localizados no caminho fornecido pelo usuário via linha de comando (vide Seção 5).
    */
}


void etapaCompressao() {
    const int n = 3; // qtd de registros importados
    string str = "";
    ProductReview* lista = import(n);

    for (int i = 0; i < n; i++)
    {
        cout << "oi" << endl;
        str += lista[i].toString() + '\n';
    }

    // NAO ESTA PRONTO  

}


void interface() {
    int option;
    do {
        cout << "Escolha qual etapa sera executada: " << endl
             << "1. Ordenacao" << endl
             << "2. Hash" << endl
             << "3. Estruturas Balanceadas" << endl
             << "4. Compressao" << endl
             << "0. Sair" << endl
             << "> " << flush;
        cin >> option;

        if (option == 1)
            etapaOrdenacao(3);
        else if (option == 2)
            etapaHash();
        else if (option == 3)
            etapaEstruturasBalanceadas();
        else if (option == 4)
            etapaCompressao();

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