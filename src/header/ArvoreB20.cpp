#include "ArvoreB20.h"
#include "ProductReview.h"
#include "ManipulandoArquivo.h"

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

extern ManipulandoArquivo arq;

ArvoreB20::ArvoreB20() 
{
    comparacoesInsercao = 0;
    comparacoesBusca = 0;
    raiz = NULL;
}

ArvoreB20::~ArvoreB20()
{
    delete raiz;
}

ArvoreBNo* ArvoreB20::criaNo(bool folha) 
{
    ArvoreBNo* no = new ArvoreBNo;
    no->folha = folha;
    no->n = 0;

    memset(no->filhos, 0, sizeof(no->filhos));

    return no;
}

// Fazer a cisao do filho e sobe a chave central para o pai
void ArvoreB20::cisaoFilho(ArvoreBNo* no, int i) 
{
    ArvoreBNo* no1 = no->filhos[i];
    ArvoreBNo* no2 = criaNo(no1->folha);

    // Sobe a chave central para o pai
    no->chaves[i] = no1->chaves[M - 1];

    // Copiar as chaves e filhos para a segunda metade de no1 para no2
    no2->n = M - 1;
    for (int j = 0; j < M - 1; j++)
    {
        no2->chaves[j] = no1->chaves[M + j];
    }

    if (!no1->folha)
    {
        for (int j = 0; j < M; j++)
        no2->filhos[j] = no1->filhos[M + j];
    }

    // Reseta numero de chaves no no1
    no1->n = M - 1;

    // Transfere as cahves e filos restantes no No pra liberar espaço pros novos filhos
    for (int j = no->n; j > i; j--)
        no->filhos[j + 1] = no->filhos[j];
    no->filhos[i + 1] = no2;

    // Incrementa o numero de chaves no No
    no->n++;
}

// Insere uma chave em uma arvore b com espaço
void ArvoreB20::insersaoComEspaco(ArvoreBNo* no, Infos chave)
{
    int i = no->n - 1;

    // Se o No eh uma folha, adiciona a chave direto
    if (no->folha)
    {
        while(i >= 0 && chave.id < no->chaves[i].id)
        {
            comparacoesInsercao++;
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->n++;
    } 
    else 
    {
        // Se nao, ache o filho para adicionar a chave
        while(i >= 0 && chave.id < no->chaves[i].id) {
            comparacoesInsercao++;
            i--;
        }
        i++;

        // Se o filho esta cheio, faz a cisao
        if (no->filhos[i]->n == 2*M - 1)
        {
            cisaoFilho(no, i);
            if (chave.id > no->chaves[i].id) {
                i++;
                comparacoesInsercao++;
            }
        }

        insersaoComEspaco(no->filhos[i], chave);
    }
}

// Insere uma chave na arvore B
void ArvoreB20::insersaoEncaps(ArvoreBNo*& raiz, Infos chave) {
    // Se a arvore esta vazia, cria um novo no como raiz
    if (raiz == NULL)
    {
        raiz = criaNo(true);
        raiz->chaves[0] = chave;
        raiz->n = 1;
    } 
    else 
    {
        // Se a raiz ja esta cheia, faz o cisao e cria uma nova raiz
        if (raiz->n == 2*M - 1)
        {
            ArvoreBNo* novoNo = criaNo(false);
            novoNo->filhos[0] = raiz;
            cisaoFilho(novoNo, 0);
            raiz = novoNo;
        }
        insersaoComEspaco(raiz, chave);
    }
}

void ArvoreB20::insere(ProductReview *pr)
{
    Infos chave;
    chave.id = pr->getUserId() + pr->getProductId();
    chave.localizacaoBinFile = pr->getBinFileLocation();

    insersaoEncaps(raiz, chave);
}

ProductReview* ArvoreB20::busca(string userId, string productId) {
    string idChave = userId + productId;
    int location = buscaEncaps(raiz, idChave);
    ProductReview* prod = new ProductReview();

    if (location != -1) {
        prod->setUserId(arq.findRegistryPosition(location).getUserId());
        prod->setProductId(arq.findRegistryPosition(location).getProductId());
        prod->setRating(arq.findRegistryPosition(location).getRating());
        prod->setTimestamp(arq.findRegistryPosition(location).getTimestamp());
        prod->setBinFileLocation(arq.findRegistryPosition(location).getBinFileLocation());
        return prod;
    }

    return NULL;
}

// faz a a busca encapsulada e retorna a localizacao no arquivo binario
int ArvoreB20::buscaEncaps(ArvoreBNo* raiz, string chave) {
    if (raiz == NULL) {
        return -1;
    }

    int i = 0;
    while (i < raiz->n && chave > raiz->chaves[i].id) {
        comparacoesBusca++;
        i++;
    }
    if (i < raiz->n && chave == raiz->chaves[i].id) {
        comparacoesBusca++;
        return raiz->chaves[i].localizacaoBinFile;
    }
    if (raiz->folha) {
        return -1;
    }
    return buscaEncaps(raiz->filhos[i], chave);
}

// Imprime as chaves na arvore B
void ArvoreB20::printEncaps(ArvoreBNo* raiz) {
    if (raiz == NULL) {
        return;
    }

    for (int i = 0; i < raiz->n; i++) {
        printEncaps(raiz->filhos[i]);
        cout << raiz->chaves[i].id << " ";
    }

    printEncaps(raiz->filhos[raiz->n]);
}