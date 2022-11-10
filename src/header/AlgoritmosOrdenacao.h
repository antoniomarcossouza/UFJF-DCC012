#ifndef ALGORITMOSORDENACAO_H
#define ALGORITMOSORDENACAO_H

#include "ProductReview.h"
#include "Metricas.h"

using namespace std;

class AlgoritmosOrdenacao
{   
    private:
        Metricas resultado;

        int particionamento(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao);
        void troca(ProductReview& x, ProductReview& y);

        void quickSortEncaps(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao);
        void mergeSortEncaps(ProductReview* vet, int i, int f);
        void merge(ProductReview* vet, int i, int q, int f);
    public:
        void quickSort(ProductReview* vet, int size);
        void mergeSort(ProductReview* vet, int size);
        void algumAlgoritmo(ProductReview* vet, int size);
};

#endif