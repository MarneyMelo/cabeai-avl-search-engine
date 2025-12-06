#ifndef INDICEPALAVRAS_HPP
#define INDICEPALAVRAS_HPP

#include <string>
#include <algorithm> // ********USADO APENAS PARA std::max********
#include "lista.hpp"

struct NoAVL {
    std::string palavra;
    Lista<int> idsLogradouros; // Lista de IDs que possuem a palavra
    int altura;
    NoAVL *esquerda;
    NoAVL *direita;

    NoAVL(std::string p) : palavra(p), altura(1), esquerda(nullptr), direita(nullptr) {}
};

class IndicePalavras {
private:
    NoAVL* raiz;

    // Funcoes da AVL
    int altura(NoAVL* n);
    int fatorBalanceamento(NoAVL* n);
    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    NoAVL* balancear(NoAVL* n);
    NoAVL* inserirRecursivo(NoAVL* no, std::string palavra, int idLog);
    NoAVL* buscarRecursivo(NoAVL* no, std::string palavra);
    void destruirRecursivo(NoAVL* no);

public:
    IndicePalavras();
    ~IndicePalavras();

    void inserir(std::string palavra, int idLog);
    Lista<int>* buscar(std::string palavra); // Retorna a lista de IDs or nullptr
};

#endif