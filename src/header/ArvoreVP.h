#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "ProductReview.h"

using namespace std;

struct NoArvoreVP {
    std::string id; //user ID + product ID
    ProductReview *productReview;
    NoArvoreVP* esq;
    NoArvoreVP* dir;
    NoArvoreVP* pai;
    int cor; //1 vermelho e 0 preto

};
               
class ArvoreVP {                       
    public:                
                       
        ArvoreVP();                
        ~ArvoreVP();               
                        
        ProductReview* busca(string userId, string productId);
        void insere(ProductReview* review);
        void print(); 
        int getComparacoesInsercao();
        int getComparacoesBusca();               
                         
    private:

    NoArvoreVP* raiz;
    int comparacoesInsercao;
    int comparacoesBusca;                                 
    void rotacaoEsquerda(NoArvoreVP* no);
    void rotacaoDireita(NoArvoreVP* no);
    void verificaCoresArvore(NoArvoreVP* no);
    NoArvoreVP* criaNoArvoreVP(ProductReview* review);
    void imprime(NoArvoreVP* no);
    void deletaArvore(NoArvoreVP* no);
};  
#endif