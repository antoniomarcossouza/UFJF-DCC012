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
void AlgoritmosOrdenacao::merge(ProductReview* vet, ProductReview* aux,  int inicio, int meio, int fim)
{

    int i = inicio;                                        
    int j = meio + 1;                                
    int k = 0;
    
    while(i <= meio && j <= fim)
    {
        if(vet[i].getUserId().compare(vet[j].getUserId()) <= 0)
        { 
            aux[k] = vet[i];  i++;
        }
        else
        {
            aux[k] = vet[j];  j++; 
        }

        k++;
    }
    while( i <= meio ) {
         aux[k] = vet[i]; i++; k++; 
    }
    while( j <= fim) {
         aux[k] = vet[j]; j++; k++; 
    }
    for(k = 0; k < fim - inicio + 1; k++ ) {
         vet[ inicio + k] = aux[k];     
    }
    
}
void AlgoritmosOrdenacao::mergeSortEncaps(ProductReview* vet, ProductReview* aux , int inicio, int fim)
{
    if(inicio < fim )
    {

        int meio = (inicio + fim) / 2;
        mergeSortEncaps(vet, aux, inicio, meio);

        mergeSortEncaps(vet, aux, meio + 1, fim);

        merge(vet, aux, inicio, meio, fim);
    }
}

void AlgoritmosOrdenacao::mergeSort(ProductReview* vet, int size)
{
    
    ManipulandoArquivo arq;
    int comparacoes = 0, movimentacoes = 0;
    
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    ProductReview* aux = new ProductReview[size];
    mergeSortEncaps(vet, aux, 0, size-1);

    delete [] aux;
    
    high_resolution_clock::time_point fim = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(fim - inicio).count();
    
    this->resultado.setTempoExecucao(time);
    this->resultado.setComparacao(comparacoes);
    this->resultado.setMovimentacao(movimentacoes);
    
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