#include "ArvoreVP.h"
#include "ProductReview.h"

ArvoreVP::ArvoreVP() 
{
    this->raiz = NULL;
    comparacoesInsercao = 0;
    comparacoesBusca = 0;
}
                                                                                     
ArvoreVP::~ArvoreVP()
{
   deletaArvore(raiz);
}
void ArvoreVP::deletaArvore(NoArvoreVP* no)
{
    if (no == NULL)
    return;
    deletaArvore(no->esq);
    deletaArvore(no->dir);

    delete no;
}


void ArvoreVP::insere(ProductReview* review){
    //verifica se não existe raiz
    if(this->raiz == NULL){
        this->raiz = criaNoArvoreVP(review);                                           
    }
    else{  

        NoArvoreVP* novoNo = criaNoArvoreVP(review);
        NoArvoreVP* atual = this->raiz;
        NoArvoreVP* pai = NULL;
        
        //procura o local de inserção do no na arvore
        while(atual != NULL){

            pai = atual;
                                                                                                                                                                 
            if( novoNo->id < atual->id ){
                atual = atual->esq;
            }                                                                                     
            else{                  
                atual = atual->dir;
            }  
            comparacoesInsercao++;                      
        }                                                                                         
        //
        novoNo->pai = pai;   

        if(novoNo->id < pai->id){
            pai->esq = novoNo;
        }
        else{
            pai->dir = novoNo;
        }

        if(novoNo!=NULL){
            verificaCoresArvore(novoNo);
        }

    }
}

//Função para auxiliar a criação de NO
NoArvoreVP* ArvoreVP::criaNoArvoreVP(ProductReview* review){

    NoArvoreVP* novo = new NoArvoreVP();
                                                                                                                                                   
    novo->id = review->getUserId() + review->getProductId();
    novo->productReview = review;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    //todo nó inserido é vermelho
    novo->cor = 1;

    return novo;

}

ProductReview*  ArvoreVP::busca(string userId, string productId){
    //verifica se existe no na arvore

    string id = userId + productId;
    NoArvoreVP* no = this->raiz;

    while(no!=NULL && no->id != id){
        if(id < no->id){
            no = no->esq;
        }
        else{
            no = no->dir;
        }
        comparacoesBusca++;
    }
    //não encontrou ou não existe no raiz
    if(no == NULL){
        return NULL;
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

void ArvoreVP::rotacaoEsquerda(NoArvoreVP* no){

    if(no!=NULL){
        NoArvoreVP* dir = no->dir;
        no->dir = dir->esq;
        dir->esq = no;
        //verifica o pai
        if(no->pai!=NULL){
            //verifica se o no é filho direito do pai
            if(no->pai->dir == no){
                no->pai->dir = dir;
            }
            else{
                no->pai->esq = dir;
            }
        }
        dir->pai = no->pai;
        no->pai = dir;

    }
}

void ArvoreVP::rotacaoDireita(NoArvoreVP* no){
    if(no!=NULL){
        NoArvoreVP* esq = no->esq;
        no->esq = esq->dir;
        esq->dir = no;
        //verifica o pai
        if(no->pai!=NULL){
            //verifica se o no é filho direito do pai
            if(no->pai->dir == no){
                no->pai->dir = esq;
            }
            else{
                no->pai->esq = esq;
            }
        }
        esq->pai = no->pai;
        no->pai = esq;


    }
}

void ArvoreVP::verificaCoresArvore(NoArvoreVP* no){
    
    //se o pai não for nulo e for vermelho
    while( no!=NULL && no->pai != NULL && no->pai->cor == 1){

        
        if(no->pai->pai!=NULL){
            //verifica se o pai é o filho esquerdo do avô
            if(no->pai == no->pai->pai->esq){
                NoArvoreVP* tio = no->pai->pai->dir;
                //verifica se a cor do tio é vermelha
                if(tio !=NULL && tio->cor == 1){
                    //colore pai e o tio de preto e o avô de vermelho
                    no->pai->cor = 0;
                    tio->cor = 0;
                    no->pai->pai->cor = 1;
                    no = no->pai->pai;
                }
                else{
                    //verifica se o no é o filho direito do pai
                    if(no == no->pai->dir){
                        no = no->pai;
                        rotacaoEsquerda(no);
                    }

                    no->pai->cor = 0; //pai preto

                    if(no->pai != NULL && no->pai->pai != NULL){
                        no->pai->pai->cor =1; //avô vermelho
                        rotacaoDireita(no->pai->pai);
                    }

                } 


            }
            else{//o pai é filho direito
                NoArvoreVP* tio = no->pai->pai->esq;
                //verifica se a cor do tio é vermelha
                if(tio !=NULL && tio->cor == 1){
                    //colore pai e o tio de preto e o avô de vermelho
                    no->pai->cor = 0;
                    tio->cor = 0;
                    no->pai->pai->cor = 1;
                    no = no->pai->pai;
                }
                else{
                    //verifica se o no é o filho esquerdo do pai
                    if(no == no->pai->esq){
                        no = no->pai;
                        rotacaoDireita(no);
                    }

                    no->pai->cor = 0; //pai preto

                    if(no->pai != NULL && no->pai->pai != NULL){
                        no->pai->pai->cor =1; //avô vermelho
                        rotacaoEsquerda(no->pai->pai);
                    }

                }
                
            }
        }
        else break;
    }
    this->raiz->cor = 0;//raiz é sempre preto
}

void ArvoreVP::print(){
    imprime(this->raiz);
}
void ArvoreVP::imprime(NoArvoreVP* no){
    if(no == NULL) {
        return;
    }
    imprime(no->esq);
    cout << no->id << " ";
    imprime(no->dir);
}
int ArvoreVP::getComparacoesInsercao(){
    return comparacoesInsercao;
}
int ArvoreVP::getComparacoesBusca(){
    return comparacoesBusca;
}