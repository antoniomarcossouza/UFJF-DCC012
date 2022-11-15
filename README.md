# ED2
# Comando
`g++ ./src/main.cpp ./src/header/*.cpp -I ./src/header -o ./src/main && ./src/main ./src/files/`<br>
- No argumento ./main passar o local do arquivo .csv ./{local_do_aquivo}
# RELATÓRIO
<a href="">https://docs.google.com/document/d/19g9uwIkStjVOPfbnRkWuc7Q4zaOtmVJ6BP_dn87qpRE/edit?usp=sharing</a>
# TODO
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
- [ ] RegistroHash* createTable(int n)
## ETAPA 4 - Programa principal
- [x] Escolha de qual operação executar
- [x] O programa desenvolvido deve permitir que o usuário entre com o caminho do diretório que contém os arquivos de dados como um argumento na linha de comando
- [x] O programa deve procurar pela existência dos  arquivos binários dentro da pasta. Se não existir, deve pré-processá-los (etapa 1) antes de seguir para as etapas seguintes.
## RELATÓRIO PARCIAL
- [ ] detalhamento das atividades realizadas por cada membro do grupo; decisões de implementação; toda e qualquer referência utilizada no desenvolvimento do trabalho.
