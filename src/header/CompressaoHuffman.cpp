#include "CompressaoHuffman.h"

#include <iostream>
#include <queue>

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

void CompressaoHuffman::buildHuffmanTree(string texto, unordered_map<char, string> &huffmanCode, priority_queue<Node *, vector<Node *>, Compare> &filaPrioridade) {
    // Build frequency table
    unordered_map<char, int> freqTable;
    for (char c : texto) {
        freqTable[c]++;
    }

    // Build priority queue
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

string CompressaoHuffman::comprimir(string texto, unordered_map<char, string> &huffmanCode) {
    string textoCodificado = "";
    for (char c : texto) {
        textoCodificado += huffmanCode[c];
    }
    return textoCodificado;
}

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