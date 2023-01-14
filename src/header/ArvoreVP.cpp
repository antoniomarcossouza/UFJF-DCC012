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
    //verifica se não existe raiz
    if(this->raiz == nullptr){
        this->raiz = criaNoArvoreVP(review);
        this->raiz->cor = 0; //colore raiz de preto
    }
    else{  

        NoArvoreVP* novoNo = criaNoArvoreVP(review);
        NoArvoreVP* atual = this->raiz;
        NoArvoreVP* pai = nullptr;
        
        //procura o local de inserção do no na arvore
        while(atual != nullptr){

            pai = atual;
                                                                                                                                
            if( novoNo->id < atual->id ){
                atual = atual->esq;
            }                                                            
            else{
                atual = atual->dir;
            }
        }                                       
        //
        novoNo->pai = pai;   

        if(novoNo->id < pai->id){
            pai->esq = novoNo;
        }
        else{
            pai->dir = novoNo;
        }
        verificaCoresArvore(novoNo);
    }
}

//Função para auxiliar a criação de NO
NoArvoreVP* ArvoreVP::criaNoArvoreVP(ProductReview* review){

    NoArvoreVP* novo = new NoArvoreVP();
                                                                                                                                                   
    novo->id = review->getUserId() + review->getProductId();
    novo->productReview = review;
    novo->dir = nullptr;
    novo->esq = nullptr;
    novo->pai = nullptr;
    //todo nó inserido é vermelho
    novo->cor = 1;

    return novo;

}

ProductReview*  ArvoreVP::busca(string userId, string productId){
    //verifica se existe no na arvore

    string id = userId + productId;
    NoArvoreVP* no = this->raiz;

    while(no!=nullptr && no->id != id){
        if(id < no->id){
            no = no->esq;
        }
        else{
            no = no->dir;
        }
    }
    //não encontrou ou não existe no raiz
    if(no == nullptr){
        return nullptr;
    }
    //retorna uma copia
    else {
        ProductReview *review = new ProductReview();
        review->setUserId(no->productReview->getUserId());
        review->setProductId(no->productReview->getProductId());
        review->setRating(no->productReview->getRating());
        review->setTimestamp(no->productReview->getTimestamp());
        review->setBinFileLocation(no->productReview->getBinFileLocation()); 

        return review;
    }
}

void ArvoreVP::rotacaoEsquerda(){

}

void ArvoreVP::rotacaoDireita(){

}

void ArvoreVP::verificaCoresArvore(NoArvoreVP* no){

}

void ArvoreVP::print(){

}