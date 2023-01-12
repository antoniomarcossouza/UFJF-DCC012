#include "ManipulandoArquivo.h"

#include <bits/stdc++.h>
#include <dirent.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "Metricas.h"
#include "ProductReview.h"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

void ManipulandoArquivo::setPath(string path) {
    this->path = path;
}

vector<string> ManipulandoArquivo::getFileName(string path) {
    string val;
    int i;
    char postfix = '/';
    stringstream streamData(path);
    vector<string> dir;

    for (i = 0; getline(streamData, val, postfix); i++)
        dir.push_back(val);

    return dir;
}

void ManipulandoArquivo::fileCSVtoBIN(string path) {
    // Converte o arquivo CSV para BINARIO
    cout << "PRE-PROCESSANDO OS DADOS" << endl;

    string csvPath = path + ".csv";

    ifstream inFile(csvPath, ios::in);
    if (!inFile) {
        cout << "ERRO ao abrir o aquivo: " << csvPath << endl;
        exit(1);
    }
    ofstream outFile(this->binPath, ios::out | ios_base::binary);
    if (!outFile) {
        cout << "ERRO ao abrir o arquivo: " << binPath << ".bin" << endl;
        exit(1);
    }

    string cache[4];
    string linha;
    string val;
    char separador = ',';
    int i = 0;
    unsigned int size;

    while (!inFile.eof()) {
        // LENDO ARQUIVO CSV
        getline(inFile, linha);
        stringstream streamData(linha);

        for (int j = 0; getline(streamData, val, separador); j++)
            cache[j] = val;

        // SETANDO VARIAVEIS
        string userId = cache[0];
        string productId = cache[1];
        float rating = stof(cache[2]);
        int timestamp = stoi(cache[3]);

        // ESCREVENDO NO ARQUIVO
        outFile.write(reinterpret_cast<const char*>(userId.c_str()), 15);
        outFile.write(reinterpret_cast<const char*>(productId.c_str()), productId.length());
        outFile.write(reinterpret_cast<const char*>(&rating), sizeof(float));
        outFile.write(reinterpret_cast<const char*>(&timestamp), sizeof(int));
    }

    outFile.close();
    inFile.close();
}

ProductReview ManipulandoArquivo::findRegistryPosition(int i) {
    // Procura o registro na posicao i passada
    // string path = "./files/ratings_Electronics.bin";
    ifstream inFile(this->binPath, ios::in | ios_base::binary);
    if (!inFile) {
        cout << "ERRO ao abrir o arquivo " << this->binPath << endl;
        exit(1);
    }

    ProductReview prod;
    char userId[15], productId[11];
    float rating;
    int timestamp;
    unsigned int size;
    int registro = i * (sizeof(userId) + sizeof(productId) + sizeof(rating) + sizeof(timestamp));

    // ENCONTRANDO REGISTRO
    inFile.seekg(i * 33);

    inFile.read(userId, 15);
    userId[15] = '\0';
    inFile.read(productId, 10);
    productId[10] = '\0';

    inFile.read((char*)&rating, sizeof(float));
    inFile.read((char*)&timestamp, sizeof(int));

    // RETORNANDO A CLASSE
    prod.setUserId(userId);
    prod.setProductId(productId);
    prod.setRating(rating);
    prod.setTimestamp(timestamp);
    prod.setBinFileLocation(i);

    inFile.close();
    return prod;
}

void ManipulandoArquivo::resetTempFile() {
    // Reseta o arquivo temporario
    ofstream outFile("./src/files/temp.bin", ios::binary);
    if (!outFile) {
        cout << "ERRO ao abrir ./src/files/temp.bin" << endl;
        exit(1);
    }
}

void ManipulandoArquivo::temp(Metricas res) {
    // Gera um arquivo temporario para armazenar as metricas
    // dos metodos de ordenacao (tempo, comparacao e movimentacao)
    ofstream outFile("./src/files/temp.bin", ios::out | ios::binary | ios::app);
    outFile.seekp(0, ios::end);

    if (!outFile) {
        cout << "ERRO ao abrir o arquivo: ./file/temp.bin" << endl;
        exit(1);
    }

    int comparacao = res.getComparacao();
    int movimentacao = res.getMovimentacao();
    double tempo = res.getTempoExecucao();

    outFile.write(reinterpret_cast<char*>(&comparacao), sizeof(int));
    outFile.write(reinterpret_cast<char*>(&movimentacao), sizeof(int));
    outFile.write(reinterpret_cast<char*>(&tempo), sizeof(double));

    outFile.close();
}

int* ManipulandoArquivo::readInput(int& size) {
    // Le os dados de input do arquivo .dat e retorna um vetor com os dados.
    int* N;
    ifstream inFile(this->datPath, ios::binary);
    if (!inFile) {
        cout << "ERRO ao abrir " << this->datPath << endl;
        exit(1);
    }

    inFile.seekg(0, ios::end);
    size = inFile.tellg() / sizeof(int);
    inFile.seekg(0);

    N = new int[size];

    inFile.read((char*)N, size * sizeof(int));

    return N;
}

void ManipulandoArquivo::gerarResultado(int N, int methodId, int M, bool parcial) {
    // Gera os resultados para o metodo de ordenacao passado
    string algoritmo;
    int comp, mov, mediaComp, mediaMov, total, size;
    double tempo, mediaTempo;

    mediaTempo = 0.0;
    mediaComp = mediaMov = total = 0;

    ifstream inFile("./src/files/temp.bin", ios::in | ios::binary);
    if (!inFile) {
        cout << "ERRO ao abrir ./src/files/temp.bin" << endl;
        exit(1);
    }

    inFile.seekg(0, ios::end);
    int sizeofRegistry = sizeof(int) + sizeof(int) + sizeof(double);
    size = inFile.tellg() / sizeofRegistry;

    // Se parcial == true, gerara o resultado medio individual.
    if (parcial)
        inFile.seekg(M * sizeofRegistry);
    else
        // Se parcial == false, gerara o resultado medio total.
        inFile.seekg(0);

    for (int i = 0; i < size; i++) {
        inFile.read((char*)&comp, sizeof(int));
        inFile.read((char*)&mov, sizeof(int));
        inFile.read((char*)&tempo, sizeof(double));

        mediaComp += comp;
        mediaMov += mov;
        mediaTempo += tempo;
        total++;
    }

    inFile.close();

    // Calculando a media
    mediaComp /= total;
    mediaMov /= total;
    mediaTempo /= total;

    ofstream outFileResults(this->path + "/saida.txt", ios::app);
    if (!outFileResults) {
        cout << "ERRO ao abrir " << this->path << "/saida.txt" << endl;
        exit(1);
    }

    outFileResults.seekp(0, ios::end);

    switch (methodId) {
        case 0:
            algoritmo = "Quick Sort";
            break;
        case 1:
            algoritmo = "Merge Sort";
            break;
        case 2:
            algoritmo = "TimSort";
            break;
    }

    // Gerando o resultado para o arquivo saida.txt
    outFileResults << "Algoritmo: " << algoritmo << endl;

    if (parcial)
        outFileResults << "Simulaçao de N: " << N << " Valores" << endl;
    else
        outFileResults << "Media Total dos Testes" << endl;

    outFileResults << "Media Comparaçoes: " << mediaComp << endl;
    outFileResults << "Media Movimentaçoes: " << mediaMov << endl;
    outFileResults << "Media Tempo: " << mediaTempo << endl
                   << endl;

    if (!parcial)
        outFileResults << "---------------------------------------" << endl;

    outFileResults.close();
}

void ManipulandoArquivo::clearOutputFile() {
    // Limpa o arquivo de saida.txt
    ofstream outFile(this->path + "/saida.txt");
    if (!outFile) {
        cout << "ERRO ao abrir " << this->path << "/saida.txt" << endl;
        exit(1);
    }
    outFile.close();
}

void ManipulandoArquivo::preProcessamento(string path) {
    // Avalia o diretorio passado para fazer o preprocessamento se necessario
    int position = 0, index;
    string csvName = "";
    string binName = "";
    string datName = "";

    for (const auto& entry : fs::directory_iterator(path))
        // Analisa se existe arquivo .CSV no diretorio
        while ((index = getFileName(entry.path()).back().find(".csv", position)) != string::npos) {
            if (index > 0) {
                csvName = entry.path();
                csvName.erase(csvName.size() - 4);
                break;
            }
            position = index + 1;
        }

    position = 0;
    for (const auto& entry : fs::directory_iterator(path))
        // Analisa se existe arquivo .DAT no diretorio
        while ((index = getFileName(entry.path()).back().find(".dat", position)) != string::npos) {
            if (index > 0) {
                datName = entry.path();
                datName.erase(datName.size() - 4);
                break;
            }
            position = index + 1;
        }

    if (datName == "") {
        cout << "ERRO Faltando arquivo input.dat" << endl;
        exit(1);
    } else
        this->datPath = datName + ".dat";

    if (csvName != "")
        // Analisa se existe arquivo .BIN no diretorio
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path() == (csvName + ".bin")) {
                binName = entry.path();
                break;
            }
        }
    else {
        cout << "ERRO arquivo .csv nao localizado" << endl;
        exit(1);
    }

    if (binName == "") {
        this->binPath = csvName + ".bin";
        fileCSVtoBIN(csvName);
    } else
        this->binPath = binName;
}

void ManipulandoArquivo::gerarResultadoEB(double* timeInsert, double* timeSearch, int* compInsert, int* compSearch, string algoritmo)
{
    double mediaTotalTime = 0;
    int mediaTotalComp = 0;

    for (int i = 0; i < 3; i++) {
        mediaTotalTime += timeInsert[i] + timeSearch[i];
        mediaTotalComp += compInsert[i] + compSearch[i];
    }

    ofstream outFileResults(this->path + "/saida.txt", ios::app);
    if (!outFileResults) {
        cout << "ERRO ao abrir " << this->path << "/saida.txt" << endl;
        exit(1);
    }

    outFileResults.seekp(0, ios::end);

    outFileResults << "Algoritmo: " << algoritmo << endl;
    outFileResults << "1 execucao" << endl;
    outFileResults << "\tComparaçoes: " << compInsert[0] + compSearch[0] << endl;
    outFileResults << "\tTempo: " << timeSearch[0] + timeInsert[0] << endl << endl;

    outFileResults << "2 execucao" << endl;
    outFileResults << "\tComparaçoes: " << compInsert[1] + compSearch[1] << endl;
    outFileResults << "\tTempo: " << timeSearch[1] + timeInsert[1] << endl << endl;

    outFileResults << "3 execucao" << endl;
    outFileResults << "\tComparaçoes: " << compInsert[2] + compSearch[2] << endl;
    outFileResults << "\tTempo: " << timeSearch[2] + timeInsert[2] << endl << endl;
    
    outFileResults << "Media final das execucoes" << endl;
    outFileResults << "\tComparaçoes: " << mediaTotalComp/3 << endl;
    outFileResults << "\tTempo: " << mediaTotalTime/3 << endl << endl;
    outFileResults.close();
}
