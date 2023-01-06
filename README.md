# ED2
# Comando
`g++ ./src/main.cpp ./src/header/*.cpp -I ./src/header -o ./src/main && ./src/main ./src/files/`<br>
- No argumento ./src/main passar o local do arquivo .csv ./src/{local_do_aquivo}
- Utilizar da versao 11 (g++)
# RELATÓRIO
<a href="">https://docs.google.com/document/d/19g9uwIkStjVOPfbnRkWuc7Q4zaOtmVJ6BP_dn87qpRE/edit?usp=sharing</a>
# TODO
# Parte 1
## ETAPA 1 - Processamento dos dados
- [x] void ProductReview::print()
- [x] void createBinary(std::string& path)
- [x] void getReview(int i)
- [x] ProductReview* import(int n)
## ETAPA 2 - Análise de algoritmos de ordenação
- [x] importar conjuntos de N registros aleatórios do arquivo binário gerado pelo pré-processamento
- [x] Salve todos os resultados obtidos em um arquivo saida.txt, contendo tanto os resultados individuais quanto a média final.
### ALGORITMOS
- [x] QuickSort
- [x] MergeSort
- [x] TimSort
### Funções obrigatorias
- [x] void sort(ProductReview *vet, int n, int methodId)
## ETAPA 3 - Produtos mais avaliados
- [x] Tabela Hash
- [x] RegistroHash* createTable(int n)
## ETAPA 4 - Programa principal
- [x] Escolha de qual operação executar
- [x] O programa desenvolvido deve permitir que o usuário entre com o caminho do diretório que contém os arquivos de dados como um argumento na linha de comando
- [x] O programa deve procurar pela existência dos  arquivos binários dentro da pasta. Se não existir, deve pré-processá-los (etapa 1) antes de seguir para as etapas seguintes.
## RELATÓRIO PARCIAL
- [x] detalhamento das atividades realizadas por cada membro do grupo; decisões de implementação; toda e qualquer referência utilizada no desenvolvimento do trabalho.
# PARTE 2
## ETAPA 1 - Implementacao de estruturas de dados balanceadas
### Arvore Vermelho e Preto
- [ ] ArvoreVP::insere(ProductReview *pr)
- [ ] ProductReciew* ArvoreVP::busca(string userId, string productId)
- [ ] void ArvoreVP::print()
### Arvore B
- [x] ArvoreB::insere(ProductReview *pr)
- [x] ProductReciew* ArvoreB::busca(string userId, string productId)
- [x] void ArvoreB::print()
## ETAPA 2 - Implementacao metodos de compressao
### ALGORITMOS
- [ ] Huffman
- [ ] LZ77
- [ ] LZW
### FUNCOES
- [ ] string comprime(string str, int metodo)
- [ ] string descomprime(string str, int metodo)
- [ ] void comprime(int metodo)
- [ ] void descromprime(int metodo)
## ETATA 3 - Analise das estruturas balanceadas
- [ ] importar conjuntos de N registros aleatórios sem repetição do arquivo binário gerado pelo pré-processamento;
- [ ] realizar a inserção desses registros na estrutura. Durante a inserção, deverão ser computados o total de comparações de chaves e o tempo de execução;
- [ ] realizar a busca de outros B registros aleatórios na estrutura (não há problema se entre os novos B registros houver algum sorteado durante o passo 2). Também não há problema se houver repetições. Durante as buscas, também deverão ser computados o total de comparações de chaves e o tempo de execução;
## ETAPA 4 - Analise dos metodos de compressao
- [ ] Para gerar as estatísticas de desempenho, você deverá executar a sequência de compressões, minimamente, M = 3 vezes. Ao final, compute as médias das taxas de compressão obtidas para as M execuções. Salve todos os resultados obtidos em um arquivo saida.txt, contendo tanto os resultados individuais quanto a média final.
## RELATORIO FINAL
- [ ] O grupo deverá confeccionar um relatório completo contendo todas as análises feitas, tanto na primeira parte do trabalho (ordenação) quanto nesta. O relatório deve seguir o modelo especificado no documento compartilhado no Google Classroom.
