#include <bits/stdc++.h>
#include <stdlib.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "./header/AlgoritmosOrdenacao.h"
#include "./header/ArvoreB.h"
#include "./header/ArvoreB200.h"
#include "./header/CompressaoHuffman.h"
#include "./header/CompressaoLZ77.h"
#include "./header/CompressaoLZW.h"
#include "./header/HashTable.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/ProductReview.h"

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

/*
    Retorna um array contendo n ProductReviews
*/
ProductReview* import(int n) {
    ProductReview* produtos = new ProductReview[n];
    vector<int> numbers(n + 90000);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 7000000);

    generate(numbers.begin(), numbers.end(), [&] { return dis(gen); });
    sort(numbers.begin(), numbers.end());

    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

    while (numbers.size() > n)
        numbers.pop_back();

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(numbers[i]);

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

    delete[] pr;
}

RegistroHash* createTable(int n) {
    HashTable hTable((int)(n * 0.3));

    ProductReview* pr = import(n);

    for (int i = 0; i < n; i++) {
        hTable.insere(pr[i]);
    }
    delete[] pr;

    return hTable.getTable();
}

template <typename T>
void testeArvore(T* arv, string algoritmo) {
    int N = 1000000;
    int B = 100;

    double timeResultsInsersion[3];
    double timeResultsSearch[3];
    int comparacoesResultsInsersion[3];
    int comparacoesResultsSearch[3];

    for (int j = 0; j < 3; j++) {
        ProductReview* prodsToImport = import(N);
        arv = new T();

        // REALIZANDO INSERCAO
        high_resolution_clock::time_point inicioInsere = high_resolution_clock::now();

        for (int i = 0; i < N; i++)
            arv->insere(&prodsToImport[i]);

        high_resolution_clock::time_point fimInsere = high_resolution_clock::now();
        double insersionTime = duration_cast<duration<double>>(fimInsere - inicioInsere).count();

        // REALIZANDO BUSCA
        high_resolution_clock::time_point inicioBusca = high_resolution_clock::now();

        ProductReview* prodsToSearch = import(B);
        for (int i = 0; i < B; i++) {
            ProductReview* res = arv->busca(prodsToImport[i].getUserId(), prodsToImport[i].getProductId());
            delete res;
        }

        high_resolution_clock::time_point fimBUsdca = high_resolution_clock::now();
        double searchTime = duration_cast<duration<double>>(fimBUsdca - inicioBusca).count();

        timeResultsInsersion[j] = insersionTime;
        timeResultsSearch[j] = searchTime;
        comparacoesResultsInsersion[j] = arv->getComparacoesInsercao();
        comparacoesResultsSearch[j] = arv->getComparacoesBusca();

        delete arv;
        delete[] prodsToImport;
        delete[] prodsToSearch;
    }

    arq.gerarResultadoEB(timeResultsInsersion, timeResultsSearch, comparacoesResultsInsersion, comparacoesResultsSearch, algoritmo);
}

void testeArvoreB() {
    ArvoreB* arv_20;
    ArvoreB200* arv_200;

    testeArvore(arv_20, "ArvoreB m = 20");
    testeArvore(arv_200, "ArvoreB m = 200");
}

void etapaEstruturasBalanceadas() {
    arq.clearOutputFile();
    // ARVORE VERMELHO E PRETO
    // ESPAÇO PARA FAZER O PROCESSO DE ANALISE

    // ARVORE B
    testeArvoreB();
}

// VARIÁVEIS GLOBAIS - COLOCAR ONDE?
unordered_map<char, string> huffmanCode;
priority_queue<CompressaoHuffman::Node*, vector<CompressaoHuffman::Node*>, CompressaoHuffman::Compare> filaPrioridade;

string comprime(string str, int metodo) {
    if (metodo == 0) {
        //  Huffman
        CompressaoHuffman::buildHuffmanTree(str, huffmanCode, filaPrioridade);
        return CompressaoHuffman::comprimir(str, huffmanCode);
    } else if (metodo == 1) {
        // LZ77
        return CompressaoLZ77::comprime(str);
    } else if (metodo == 2) {
        // LZW
        vector<unsigned short> codes = CompressaoLZW::comprime(str);
        string comprimida;
        for (int i = 0; i < codes.size(); i++)
            comprimida.append(to_string(codes.at(i)) + " ");

        return comprimida;
    }
    return "";
}

string descomprime(string str, int metodo) {
    if (metodo == 0) {
        //  Huffman
        return CompressaoHuffman::descomprimir(str, filaPrioridade.top());
    } else if (metodo == 1) {
        // LZ77
        return CompressaoLZ77::descomprime(str);
    } else if (metodo == 2) {
        // LZW
        return CompressaoLZW::descomprime(str);
    }
    return "";
}

void comprime(int metodo) {
    /*
        comprime o conteúdo de um arquivo texto nomeado reviewsOrig.txt, utilizando o método especificado
        no segundo parâmetro (0 = Huffman, 1 = LZ77, 2 = LZW). A função deve salvar o resultado da compressão
        em um arquivo binário reviewsComp.bin. Ambos os arquivos deverão estar localizados no caminho fornecido
        pelo usuário via linha de comando (vide Seção 5).
    */

    string original = arq.getReviews();

    if (metodo == 0) {
        //  Huffman
        // string comprimida = CompressaoHUF::comprime(original);
    } else if (metodo == 1) {
        // LZ77
        string comprimida = CompressaoLZ77::comprime(original);
        arq.writeBin("reviewsComp.bin", comprimida);
    } else if (metodo == 2) {
        // LZW
        vector<unsigned short> comprimida = CompressaoLZW::comprime(original);
        arq.writeBin("reviewsComp.bin", comprimida);
        // string comprimida = CompressaoLZW::comprime(original);
    }
}

void descomprime(int metodo) {
    /*
        descomprime o conteúdo do arquivo binário reviewsComp.bin, utilizando o método especificado no segundo
        parâmetro (0 = Huffman, 1 = LZ77, 2 = LZW). A função deve salvar o resultado da descompressão em um arquivo texto
        reviewsDesc.txt. Ambos os arquivos deverão estar localizados no caminho fornecido pelo usuário via linha de comando (vide Seção 5).
    */

    if (metodo == 0) {
        //  Huffman
        // string comprimida = CompressaoHUF::comprime(original);
    } else if (metodo == 1) {
        // LZ77
        string comprimida = arq.readBin("reviewsComp.bin", 1);
        string descomprimida = CompressaoLZ77::descomprime(comprimida);
        arq.writeTxt("reviewsDesc.txt", descomprimida);
    } else if (metodo == 2) {
        // LZW
        string comprimida = arq.readBin("reviewsComp.bin", 2);
        string descomprimida = CompressaoLZW::descomprime(comprimida);
        arq.writeTxt("reviewsDesc.txt", descomprimida);
    }
}

void compressTest(int method) {
    switch (method) {
        case 0:
            cout << "=== Teste Huffman ===" << endl
                 << endl;
            break;
        case 1:
            cout << "=== Teste LZ77 ===" << endl
                 << endl;
            break;
        case 2:
            cout << "=== Teste LZW ===" << endl
                 << endl;
            break;
        default:
            cout << "Metodo de compressao nao suportado" << endl
                 << endl;
            break;
    }

    cout << "Testando strings..." << endl;

    string str = "string qualquer";
    string comp = comprime(str, method);
    cout << "String comprimida: " << comp << endl;

    string orig = descomprime(comp, method);
    cout << "String descomprimida: " << orig << endl << endl;

    cout << "Testando arquivos..." << endl;

    comprime(method);     // essa função deve comprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsOrig.txt'
    descomprime(method);  // essa função deve descomprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsComp.bin'
    
}

void etapaCompressao() {
    int option;
    cout << "Escolha qual compressão: " << endl
         << "0. Huffman" << endl
         << "1. LZ77" << endl
         << "2. LZW" << endl
         << "> " << flush;
    cin >> option;

    string strOption;
    switch (option) {
        case 0: strOption = "Huffman"; break;
        case 1: strOption = "LZ77"; break;
        case 2: strOption = "LZW"; break;
        default: break;
    }

    int qtdImports = 1000;
    int tamOrig[3];
    int tamCompress[3];

    for (int i = 0; i < 3; i++) {
        string str;
        ProductReview* pr = import(qtdImports);
        for (int i = 0; i < qtdImports; i++) {
            str.append(pr[i].toString());
        }

        if (option == 0) {
            
        }
        else if (option == 1) {
            string compress = comprime(str, option);
            tamOrig[i] = str.length();
            compress.erase(remove_if(compress.begin(), compress.end(), ::isspace), compress.end());
            tamCompress[i] = compress.length();
        }
        else if (option == 2) {
            vector<unsigned short> compress = CompressaoLZW::comprime(str);
            tamOrig[i] = str.length();
            tamCompress[i] = compress.size() * sizeof(short);
        }

    }

    arq.gerarResultadoCmprs(option, tamOrig, tamCompress);
}

void interface() {
    int option;
    do {
        cout << endl
             << "Escolha qual etapa sera executada: " << endl
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
        else if (option == 4) {
            etapaCompressao();
        }

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