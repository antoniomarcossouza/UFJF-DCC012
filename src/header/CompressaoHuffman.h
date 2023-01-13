#ifndef COMPRESSAOHUFF_H
#define COMPRESSAOHUFF_H

#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

class CompressaoHuffman {
   public:
    class Node {
       public:
        char data;
        int freq;
        Node *left, *right;

        Node(char data, int freq, Node *left = nullptr, Node *right = nullptr) {
            this->data = data;
            this->freq = freq;
            this->left = left;
            this->right = right;
        }
    };
    class Compare {
       public:
        bool operator()(Node *l, Node *r) {
            return l->freq > r->freq;
        }
    };

    static void buildCodes(Node *raiz, string str, unordered_map<char, string> &huffmanCode);
    static void buildHuffmanTree(string text, unordered_map<char, string> &huffmanCode, priority_queue<Node *, vector<Node *>, Compare> &pq);
    static string comprimir(string texto, unordered_map<char, string> &huffmanCode);
    static string descomprimir(string textoCodificado, Node *raiz);
};

#endif