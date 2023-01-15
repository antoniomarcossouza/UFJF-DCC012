#include "CompressaoHuffman.h"

#include <iostream>
#include <queue>

/*
    Parâmetros:
    raiz: ponto inicial da árvore de Huffman
    str: string vazia que é usada como prefixo para a codificação de Huffman
    huffmanCode: mapa que armazena a codificação Huffman para cada caractere

    Código:
    Verifica se a raiz é nula e, se for, retorna imediatamente.
    Se a raiz não for nula, verifica se o nó atual tem um caractere diferente de '\0', que indica que é uma folha,
    e, se tiver, adiciona o caractere e o código Huffman correspondente ao mapa huffmanCode.

    Em seguida, a função chama a si mesma recursivamente para o filho esquerdo e para o filho direito,
    passando str + "0" e str + "1" como o novo prefixo para a codificação Huffman, respectivamente.
    Isso garante que a codificação Huffman seja construída de acordo com a árvore de Huffman correta.

    Por fim, toda a codificação Huffman para cada caractere estará armazenada no mapa huffmanCode.
*/
void CompressaoHuffman::buildCodes(Node *raiz, string str, unordered_map<char, string> &huffmanCode) {
    if (raiz == nullptr) {
        return;
    }
    if (raiz->data != '\0') {
        huffmanCode[raiz->data] = str;
    }
    buildCodes(raiz->left, str + "0", huffmanCode);
    buildCodes(raiz->right, str + "1", huffmanCode);
}

/*
    Parâmetros:
    texto: texto a ser comprimido
    huffmanCode: mapa que armazena a codificação Huffman para cada caractere
    filaPrioridade: fila de prioridade usada para construir a árvore de Huffman

    Código:
    A função começa construindo uma tabela de frequência para cada caractere no texto e
    adiciona cada caractere e sua frequência à fila de prioridade.

    A função então constrói a árvore de Huffman removendo os dois nós de menor frequência da fila de
    prioridade, criando um novo nó pai com a soma das frequências dos dois nós removidos e adicionando-o
    de volta à fila. Isso é repetido até que a fila tenha apenas um nó, que é a raiz da árvore de Huffman.

    Por fim, a função chama a função buildCodes passando a raiz da árvore de Huffman, uma string vazia e
    o mapa da codificação Huffman como parâmetros, a fim de construir a codificação Huffman para cada caractere.
*/
void CompressaoHuffman::buildHuffmanTree(string texto, unordered_map<char, string> &huffmanCode, priority_queue<Node *, vector<Node *>, Compare> &filaPrioridade) {
    unordered_map<char, int> freqTable;
    for (char c : texto) {
        freqTable[c]++;
    }

    for (auto pair : freqTable) {
        filaPrioridade.push(new Node(pair.first, pair.second));
    }

    // Build Huffman tree
    while (filaPrioridade.size() > 1) {
        Node *left = filaPrioridade.top();
        filaPrioridade.pop();
        Node *right = filaPrioridade.top();
        filaPrioridade.pop();
        int sum = left->freq + right->freq;
        filaPrioridade.push(new Node('\0', sum, left, right));
    }

    // Build Huffman codes
    buildCodes(filaPrioridade.top(), "", huffmanCode);
}

/*
    Parâmetros:
    texto: texto a ser comprimido
    huffmanCode: mapa que armazena a codificação Huffman para cada caractere

    Variáveis:
    textoCodificado: será preenchida com o texto comprimido

    Código:
    Loop que percorre cada caractere do texto.
    Para cada caractere, o código adiciona o código Huffman correspondente,
    que é recuperado do huffmanCode, ao textoCodificado.

    Ao fim do loop, a função retorna o texto comprimido.
*/
string CompressaoHuffman::comprimir(string texto, unordered_map<char, string> &huffmanCode) {
    string textoCodificado = "";
    for (char c : texto) {
        textoCodificado += huffmanCode[c];
    }
    return textoCodificado;
}

/*
    Parâmetros:
    textoCodificado: texto a ser descomprimido
    raiz: ponto inicial da árvore de Huffman usada para a codificação

    Variáveis:
    textoDecodificado: será preenchida com o texto descomprimido
    current: aponta para o nó atual, inicialmente para a raiz da árvore de Huffman

    Código:
    Loop que percorre os caracteres do texto codificado.
    Para cada caractere, o código verifica se é igual a '0' ou '1',
    e move o ponteiro current para o filho esquerdo ou direito da árvore, respectivamente.

    Se o nó atual tem um caractere diferente de '\0', que indica que é uma folha, ele é adicionado
    ao textoDecodificado e o ponteiro current é apontado para a raiz novamente.

    Ao fim do loop, a função retorna o texto descomprimido.
*/
string CompressaoHuffman::descomprimir(string textoCodificado, Node *raiz) {
    string textoDecodificado = "";
    Node *current = raiz;
    for (char c : textoCodificado) {
        current = (c == '0') ? current->left : current->right;
        if (current->data != '\0') {
            textoDecodificado += current->data;
            current = raiz;
        }
    }
    return textoDecodificado;
}