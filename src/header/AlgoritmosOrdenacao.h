#ifndef ALGORITMOSORDENACAO_H
#define ALGORITMOSORDENACAO_H

#include "Metricas.h"
#include "ProductReview.h"

#include "RegistroHash.h"

using namespace std;

class AlgoritmosOrdenacao {
   private:
    Metricas resultado;

    void trocaHash(RegistroHash& x, RegistroHash& y);
    int particionamentoHash(RegistroHash* vet, int lo, int hi);
    void quickSortEncapsHash(RegistroHash* vet, int lo, int hi);

    int particionamento(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao);
    void troca(ProductReview& x, ProductReview& y);

    void quickSortEncaps(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao);
    void mergeSortEncaps(ProductReview* vet, ProductReview* aux, int inicio, int fim, int& comparacoes, int& movimentacoes);
    void merge(ProductReview* vet, ProductReview* aux, int inicio, int meio, int fim, int& comparacoes, int& movimentacoes);
    void timSortEncaps(ProductReview* vet, ProductReview* aux, int size, int& comparacoes, int& movimentacoes);

   public:
    void quickSort(ProductReview* vet, int size);
    void mergeSort(ProductReview* vet, int size);
    void insertionSort(ProductReview* vetor, int esquerda, int direita, int& comparacoes, int& movimentacoes);
    void timSort(ProductReview* vet, int size);
    void quickSortHash(RegistroHash* vet, int size);
};

#endif