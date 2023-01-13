#include "ArvoreVP.h"
#include "ProductReview.h"
#include "ManipulandoArquivo.h"


extern ManipulandoArquivo arq;

ArvoreVP::ArvoreVP() 
{
   this->raiz = nullptr;
}
                                                                                     
ArvoreVP::~ArvoreVP()
{
    delete this->raiz;
}


void ArvoreVP::insere(ProductReview* review){
                                                                                                                                                                                                                      
    NoArvoreVP* novoNo = criaNoArvoreVP(review);
    NoArvoreVP* atual = this->raiz;
    NoArvoreVP* pai = nullptr;

    while(atual != nullptr){

        pai = atual;
                                                                                                                             
        if( novoNo->id < atual->id ){
            atual = atual->esq;
        }                                                            
        else{
            atual = atual->dir;
        }
    }                                       

    novoNo->pai = pai;   

    if(pai == nullptr)
    {                            
        raiz = novoNo->pai;
    }
    else{

        if(novoNo->id < pai->id){
            pai->esq = novoNo;
        }
        else{
            pai->dir = novoNo;
        }
    }

    verificaCoresArvore(novoNo);

}

//Função para auxiliar a criação de NO
NoArvoreVP* ArvoreVP::criaNoArvoreVP(ProductReview* review){

    NoArvoreVP* novo = new NoArvoreVP();
                                                                                                                                                   
    novo->id = review->getUserId() + review->getProductId();
    novo->productReview = review;
    novo->dir = nullptr;
    novo->esq = nullptr;
    novo->pai = nullptr;
    novo->cor = 1;

    return novo;

}

ProductReview*  ArvoreVP::busca(string userId, string productId){
    return nullptr;
}

void ArvoreVP::rotacaoEsquerda(){

}

void ArvoreVP::rotacaoDireita(){

}

void ArvoreVP::verificaCoresArvore(NoArvoreVP* no){

}

void ArvoreVP::print(){

}