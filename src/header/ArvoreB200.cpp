#include "ArvoreB200.h"
#include "ProductReview.h"
#include "ManipulandoArquivo.h"

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

extern ManipulandoArquivo arq;

ArvoreB200::ArvoreB200() 
{
    comparacoesInsercao = 0;
    comparacoesBusca = 0;
    raiz = NULL;
}

ArvoreB200::~ArvoreB200()
{
    delete raiz;
}

ArvoreB200No* ArvoreB200::criaNo(bool folha) 
{
    ArvoreB200No* no = new ArvoreB200No;
    no->folha = folha;
    no->n = 0;

    memset(no->filhos, 0, sizeof(no->filhos));

    return no;
}

// Fazer a cisao do filho e sobe a chave central para o pai
void ArvoreB200::cisaoFilho(ArvoreB200No* no, int i) 
{
    ArvoreB200No* no1 = no->filhos[i];
    ArvoreB200No* no2 = criaNo(no1->folha);

    // Sobe a chave central para o pai
    no->chaves[i] = no1->chaves[M200 - 1];

    // Copiar as chaves e filhos para a segunda metade de no1 para no2
    no2->n = M200 - 1;
    for (int j = 0; j < M200 - 1; j++)
    {
        no2->chaves[j] = no1->chaves[M200 + j];
    }

    if (!no1->folha)
    {
        for (int j = 0; j < M200; j++)
        no2->filhos[j] = no1->filhos[M200 + j];
    }

    // Reseta numero de chaves no no1
    no1->n = M200 - 1;

    // Transfere as cahves e filos restantes no No pra liberar espaço pros novos filhos
    for (int j = no->n; j > i; j--)
        no->filhos[j + 1] = no->filhos[j];
    no->filhos[i + 1] = no2;

    // Incrementa o numero de chaves no No
    no->n++;
}

// Insere uma chave em uma arvore b com espaço
void ArvoreB200::insersaoComEspaco(ArvoreB200No* no, Infos200 chave)
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
        if (no->filhos[i]->n == 2*M200 - 1)
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
void ArvoreB200::insersaoEncaps(ArvoreB200No*& raiz, Infos200 chave) {
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
        if (raiz->n == 2*M200 - 1)
        {
            ArvoreB200No* novoNo = criaNo(false);
            novoNo->filhos[0] = raiz;
            cisaoFilho(novoNo, 0);
            raiz = novoNo;
        }
        insersaoComEspaco(raiz, chave);
    }
}

void ArvoreB200::insere(ProductReview *pr)
{
    Infos200 chave;
    chave.id = pr->getUserId() + pr->getProductId();
    chave.localizacaoBinFile = pr->getBinFileLocation();

    insersaoEncaps(raiz, chave);
}

ProductReview* ArvoreB200::busca(string userId, string productId) {
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
int ArvoreB200::buscaEncaps(ArvoreB200No* raiz, string chave) {
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
void ArvoreB200::printEncaps(ArvoreB200No* raiz) {
    if (raiz == NULL) {
        return;
    }

    for (int i = 0; i < raiz->n; i++) {
        printEncaps(raiz->filhos[i]);
        cout << raiz->chaves[i].id << " ";
    }

    printEncaps(raiz->filhos[raiz->n]);
}