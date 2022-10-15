#ifndef MANIPULANDOAQRQUIVO_H
#define MANIPULANDOAQRQUIVO_H

#include <fstream>
#include <vector>
#include "ProductReview.h"
#include "Metricas.h"

using namespace std;

class ManipulandoArquivo
{
    public:
        void fileCSVtoBIN(string path);
        ProductReview findRegistryPosition(int i);
        void resetTempFile();
        void temp(Metricas resultado);
        int* readInput(int& size);
        void gerarResultado(int N, int methodId, int M, bool parcial);
        void clearOutputFile();
        void preProcessamento(string path);
    
    private:
        vector<string> getFileName(string path);
};

#endif