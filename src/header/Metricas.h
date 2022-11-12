#ifndef METRICAS_H
#define METRICAS_H

class Metricas {
   private:
    double tempoExecucao;
    int movimentacao;
    int comparacao;

   public:
    void setTempoExecucao(double tempoExecucao) { this->tempoExecucao = tempoExecucao; }
    void setMovimentacao(int movimentacao) { this->movimentacao = movimentacao; }
    void setComparacao(int comparacao) { this->comparacao = comparacao; }

    double getTempoExecucao() { return this->tempoExecucao; }
    int getMovimentacao() { return this->movimentacao; }
    int getComparacao() { return this->comparacao; }
};

#endif