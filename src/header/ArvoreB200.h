#ifndef ARVOREB200_H
#define ARVOREB200_H

#include "ProductReview.h"
#include <string>

using namespace std;

const int M200 = 200; // Ordem da arvore B

struct Infos200 {
    std::string id;
    int localizacaoBinFile;
};

struct ArvoreB200No {
    Infos200 chaves[M200-1]; // Vetor de chaves userId + productId
    int n; // Numero de chaves no vetor
    ArvoreB200No* filhos[M200]; // filhos
    bool folha; // no folha
};

class ArvoreB200 {
    public:
        ArvoreB200();
        ~ArvoreB200();

        ProductReview* busca(string userId, string productId);
        void print() {printEncaps(raiz);}
        void insere(ProductReview* chave);
        int getComparacoesInsercao() {return this->comparacoesInsercao;};
        int getComparacoesBusca() {return this->comparacoesBusca;};

    private:
        ArvoreB200No* raiz;
        int comparacoesInsercao;
        int comparacoesBusca;

        int buscaEncaps(ArvoreB200No* raiz, string chave);
        void cisaoFilho(ArvoreB200No* no, int i);
        void insersaoComEspaco(ArvoreB200No* no, Infos200 chave);
        void insersaoEncaps(ArvoreB200No*& raiz, Infos200 chave);
        void printEncaps(ArvoreB200No* no);

        ArvoreB200No* criaNo(bool folha);
};  

#endif