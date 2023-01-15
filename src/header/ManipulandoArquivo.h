#ifndef MANIPULANDOAQRQUIVO_H
#define MANIPULANDOAQRQUIVO_H

#include <fstream>
#include <vector>
#include <string>

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
    void gerarResultadoEB(double* timeInsert, double* timeSearch, int* compInsert, int* compSearch, std::string algo);

    // etapa de compressao
    string getReviews();
    void writeBin(string nomeArq, string str);
    void writeBin(string nomeArq, vector<unsigned short> code);
    string readBin(string nomeArq, int option);
    void writeTxt(string nomeAqr, string str);
    void gerarResultadoCmprs(string metodo, int charOrig[], int charCompress[]);

    string path;

   private:
    vector<string> getFileName(string path);
    string datPath;
    string binPath;
};

#endif