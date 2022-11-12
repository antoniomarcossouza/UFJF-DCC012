#ifndef MANIPULANDOAQRQUIVO_H
#define MANIPULANDOAQRQUIVO_H

#include <fstream>
#include <vector>

#include "Metricas.h"
#include "ProductReview.h"

using namespace std;

class ManipulandoArquivo {
   public:
    void fileCSVtoBIN(string path);
    ProductReview findRegistryPosition(int i);
    void resetTempFile();
    void temp(Metricas resultado);
    int* readInput(int& size);
    void gerarResultado(int N, int methodId, int M, bool parcial);
    void clearOutputFile();
    void preProcessamento(string path);
    void setPath(string path);

   private:
    vector<string> getFileName(string path);
    string path;
    string datPath;
    string binPath;
};

#endif