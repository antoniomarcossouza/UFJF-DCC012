#ifndef ARVOREB_H
#define ARVOREB_H

#include "ProductReview.h"
#include <string>

using namespace std;

const int M = 20; // Ordem da arvore B

struct Infos {
    std::string id;
    int localizacaoBinFile;
};

struct ArvoreBNo {
    Infos chaves[M-1]; // Vetor de chaves userId + productId
    int n; // Numero de chaves no vetor
    ArvoreBNo* filhos[M]; // filhos
    bool folha; // no folha
};

class ArvoreB {
    public:
        ArvoreB();
        ~ArvoreB();

        ProductReview* busca(string userId, string productId);
        void print() {printEncaps(raiz);}
        void insere(ProductReview* chave);
        int getComparacoesInsercao() {return this->comparacoesInsercao;};
        int getComparacoesBusca() {return this->comparacoesBusca;};

    private:
        ArvoreBNo* raiz;
        int comparacoesInsercao;
        int comparacoesBusca;

        int buscaEncaps(ArvoreBNo* raiz, string chave);
        void cisaoFilho(ArvoreBNo* no, int i);
        void insersaoComEspaco(ArvoreBNo* no, Infos chave);
        void insersaoEncaps(ArvoreBNo*& raiz, Infos chave);
        void printEncaps(ArvoreBNo* no);

        ArvoreBNo* criaNo(bool folha);
};  

#endif