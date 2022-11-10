#include "AlgoritmosOrdenacao.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include "Metricas.h"
#include "ManipulandoArquivo.h"

using namespace std;
using namespace std::chrono;

void AlgoritmosOrdenacao::troca(ProductReview& x, ProductReview& y)
{
    ProductReview aux = x;
    x = y;
    y = aux;
}

int AlgoritmosOrdenacao::particionamento(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao)
{
    int posPivo = (hi + lo) / 2;
    ProductReview pivo = vet[posPivo];
    int i = lo - 1, j = hi + 1;
    do
    {
        do {i++; comparacoes++; } while (vet[i].getUserId().compare(pivo.getUserId()) < 0);
        do {j--; comparacoes++; } while (vet[j].getUserId().compare(pivo.getUserId()) > 0);

        if (i >= j) return j;

        troca(vet[i], vet[j]);
        movimentacao++;

    } while (true);
}

void AlgoritmosOrdenacao::quickSortEncaps(ProductReview* vet, int lo, int hi, int& comparacoes, int& movimentacao)
{
    if (lo < hi)
    {
        int p = particionamento(vet, lo, hi, comparacoes, movimentacao);
        quickSortEncaps(vet, lo, p, comparacoes, movimentacao);
        quickSortEncaps(vet, p + 1, hi, comparacoes, movimentacao);
    }
}


void AlgoritmosOrdenacao::quickSort(ProductReview* vet, int size)
{
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
void AlgoritmosOrdenacao::merge(ProductReview* vet, int i, int q, int f)
{
    int inicio = i;
    int meio = q;
    int k = 0;
    ProductReview* aux;
    while(inicio < q && meio < f)
    {
        if(vet[inicio] < vet[meio])
        { 
            aux[k] = vet[i];  meio++;
        }
        else
        {
            aux[k] = vet[meio];  meio++; 
        }

        k++;
    }
    while( inicio < meio) { aux[k] = vet[inicio]; inicio++; k++; }
    while( meio < f) { aux[k] = vet[meio]; meio++; k++; }
    for(inicio = i; inicio < f; inicio++) { vet[i] = aux[inicio - i]; }
}
void AlgoritmosOrdenacao::mergeSortEncaps(ProductReview* vet, int i, int f)
{
    if(i < f)
    {
        int q = (i + f) / 2;
        mergeSortEncaps(vet, i, q);
        mergeSortEncaps(vet, q + 1, f);
        merge(vet, i, q, f);
    }
}

void AlgoritmosOrdenacao::mergeSort(ProductReview* vet, int size)
{
    ManipulandoArquivo arq;

    this->resultado.setComparacao(1000);
    this->resultado.setMovimentacao(10000);
    this->resultado.setTempoExecucao(30.33);

    arq.temp(resultado);
}

void AlgoritmosOrdenacao::algumAlgoritmo(ProductReview* vet, int size)
{
    ManipulandoArquivo arq;

    this->resultado.setComparacao(1000);
    this->resultado.setMovimentacao(10000);
    this->resultado.setTempoExecucao(30.33);

    arq.temp(resultado);
}