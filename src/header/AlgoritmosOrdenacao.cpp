#include "AlgoritmosOrdenacao.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "ManipulandoArquivo.h"
#include "Metricas.h"

using namespace std;
using namespace std::chrono;

void AlgoritmosOrdenacao::troca(ProductReview& x, ProductReview& y) {
    ProductReview aux = x;
    x = y;
    y = aux;
}

int AlgoritmosOrdenacao::particionamento(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao) {
    int posPivo = (hi + lo) / 2;
    ProductReview pivo = vet[posPivo];
    int i = lo - 1, j = hi + 1;
    do {
        do {
            i++;
            comparacoes++;
        } while (vet[i].getUserId().compare(pivo.getUserId()) < 0);
        do {
            j--;
            comparacoes++;
        } while (vet[j].getUserId().compare(pivo.getUserId()) > 0);

        if (i >= j) return j;

        troca(vet[i], vet[j]);
        movimentacao++;

    } while (true);
}

void AlgoritmosOrdenacao::quickSortEncaps(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao) {
    if (lo < hi) {
        int p = particionamento(vet, lo, hi, comparacoes, movimentacao);
        quickSortEncaps(vet, lo, p, comparacoes, movimentacao);
        quickSortEncaps(vet, p + 1, hi, comparacoes, movimentacao);
    }
}

void AlgoritmosOrdenacao::quickSort(ProductReview* vet, int size) {
    ManipulandoArquivo arq;
    int comparacoes = 0, movimentacoes = 0;

    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    quickSortEncaps(vet, 0, size - 1, comparacoes, movimentacoes);

    high_resolution_clock::time_point fim = high_resolution_clock::now();
    double time = duration_cast<duration<double>>(fim - inicio).count();

    this->resultado.setTempoExecucao(time);
    this->resultado.setComparacao(comparacoes);
    this->resultado.setMovimentacao(movimentacoes);

    arq.temp(resultado);
}

void AlgoritmosOrdenacao::merge(ProductReview* vet, ProductReview* aux, int inicio, int meio, int fim, int& comparacoes, int& movimentacoes) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {
        if (vet[i].getUserId().compare(vet[j].getUserId()) <= 0) {
            aux[k] = vet[i];
            i++;
            comparacoes++;
            movimentacoes++;
        } else {
            aux[k] = vet[j];
            j++;
        }

        k++;
    }
    while (i <= meio) {
        aux[k] = vet[i];
        i++;
        k++;
    }
    while (j <= fim) {
        aux[k] = vet[j];
        j++;
        k++;
    }
    for (k = 0; k < fim - inicio + 1; k++) {
        vet[inicio + k] = aux[k];
    }
}

void AlgoritmosOrdenacao::mergeSortEncaps(ProductReview* vet, ProductReview* aux, int inicio, int fim, int& comparacoes, int& movimentacoes) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortEncaps(vet, aux, inicio, meio, comparacoes, movimentacoes);

        mergeSortEncaps(vet, aux, meio + 1, fim, comparacoes, movimentacoes);

        merge(vet, aux, inicio, meio, fim, comparacoes, movimentacoes);
    }
}

void AlgoritmosOrdenacao::mergeSort(ProductReview* vet, int size) {
    ManipulandoArquivo arq;
    int comparacoes = 0, movimentacoes = 0;

    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    ProductReview* aux = new ProductReview[size];
    mergeSortEncaps(vet, aux, 0, size - 1, comparacoes, movimentacoes);

    high_resolution_clock::time_point fim = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(fim - inicio).count();

    this->resultado.setTempoExecucao(time);
    this->resultado.setComparacao(comparacoes);
    this->resultado.setMovimentacao(movimentacoes);
    arq.temp(resultado);
}

void AlgoritmosOrdenacao::insertionSort(ProductReview* vetor, int esquerda, int direita, int& comparacoes, int& movimentacoes) {
    for (int i = esquerda + 1; i <= direita; i++) {
        string temp = vetor[i].getUserId();
        int j = i - 1;
        movimentacoes++;
        while (j >= esquerda && vetor[j].getUserId().compare(temp) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
            movimentacoes++;
            comparacoes++;
        }
        vetor[j + 1].setUserId(temp);
        movimentacoes++;
    }
}
const int RUN = 32;
void AlgoritmosOrdenacao::timSort(ProductReview* vet, int size) {
    ManipulandoArquivo arq;
    int comparacoes = 0, movimentacoes = 0;

    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    // Sort individual subarrays of size RUN
    for (int i = 0; i < size; i += RUN) {
        insertionSort(vet, i, min((i + RUN - 1), (size - 1)), comparacoes, movimentacoes);
    }
    // Start merging from size RUN.
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    ProductReview* aux = new ProductReview[size];
    for (int tamanho = RUN; tamanho < tamanho; tamanho = 2 * tamanho) {
        // pick starting point of left sub array. We are going to merge arr[left..left+size-1] and arr[left+size, left+2*size-1]
        // After every merge, we increase left by 2*size
        for (int esquerda = 0; esquerda < tamanho; esquerda += 2 * tamanho) {
            // find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            int meio = esquerda + tamanho - 1;
            movimentacoes++;
            int direita = min((esquerda + 2 * tamanho - 1), (tamanho - 1));
            movimentacoes++;
            comparacoes++;
            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if (meio < direita) {
                merge(vet, aux, esquerda, meio, direita, comparacoes, movimentacoes);
            }
        }
    }

    high_resolution_clock::time_point fim = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(fim - inicio).count();

    this->resultado.setTempoExecucao(time);
    this->resultado.setComparacao(comparacoes);
    this->resultado.setMovimentacao(movimentacoes);

    arq.temp(resultado);
}