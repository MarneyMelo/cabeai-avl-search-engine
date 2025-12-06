#include "../include/indicePalavras.hpp"
#include <algorithm> // Necessário para std::max

IndicePalavras::IndicePalavras() : raiz(nullptr) {}

IndicePalavras::~IndicePalavras() {
    destruirRecursivo(raiz);
}

void IndicePalavras::destruirRecursivo(NoAVL* no) {
    if (no != nullptr) {
        destruirRecursivo(no->esquerda);
        destruirRecursivo(no->direita);
        delete no; // A lista dentro do nó se destrói sozinha pelo destrutor dela
    }
}

// Funções aux de altura e balanceamento (Padrão AVL)
int IndicePalavras::altura(NoAVL* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

int IndicePalavras::fatorBalanceamento(NoAVL* n) {
    if (n == nullptr) return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// ===================================
// ROTACOES E BALANCEAMENTO
// Implementação padrão da logicaa de uma AVL para manter complexidade O(log n)
// ===================================

NoAVL* IndicePalavras::rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

NoAVL* IndicePalavras::rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

NoAVL* IndicePalavras::balancear(NoAVL* n) {
    if (n == nullptr) return nullptr;

    n->altura = 1 + std::max(altura(n->esquerda), altura(n->direita));
    int fb = fatorBalanceamento(n);

    // Caso Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamento(n->esquerda) >= 0)
        return rotacaoDireita(n);

    // Caso Esquerda-Direita
    if (fb > 1 && fatorBalanceamento(n->esquerda) < 0) {
        n->esquerda = rotacaoEsquerda(n->esquerda);
        return rotacaoDireita(n);
    }

    // Caso Direita-Direita
    if (fb < -1 && fatorBalanceamento(n->direita) <= 0)
        return rotacaoEsquerda(n);

    // Caso Direita-Esquerda
    if (fb < -1 && fatorBalanceamento(n->direita) > 0) {
        n->direita = rotacaoDireita(n->direita);
        return rotacaoEsquerda(n);
    }

    return n;
}

// ---------------------------------------------------------
// INSERÇÃO (cada palavra aponta para uma lista de ids)
// ---------------------------------------------------------

NoAVL* IndicePalavras::inserirRecursivo(NoAVL* no, std::string palavra, int idLog) {
    // 1. Inserção normal de BST (busca binaria)
    if (no == nullptr) {
        NoAVL* novo = new NoAVL(palavra);
        novo->idsLogradouros.adicionar(idLog);
        return novo;
    }

    if (palavra < no->palavra) {
        no->esquerda = inserirRecursivo(no->esquerda, palavra, idLog);
    } else if (palavra > no->palavra) {
        no->direita = inserirRecursivo(no->direita, palavra, idLog);
    } else {
        // [IMPORTANTE] nesse else, significa q palavra já existe na árvore
        // Em vez de substituir ou dar erro, adicionamos o ID na lista deste nó
        // É isso que cria a relação "Palavra -> Vários Logradouros".
        no->idsLogradouros.adicionar(idLog);
        return no; // Retorna sem balancear pois a altura não mudou
    }

    // 2. Atualiza altura e balanceia o nó ancestral
    return balancear(no);
}

void IndicePalavras::inserir(std::string palavra, int idLog) {
    raiz = inserirRecursivo(raiz, palavra, idLog);
}

// -------------------
// BUSCA
// ------------------

NoAVL* IndicePalavras::buscarRecursivo(NoAVL* no, std::string palavra) {
    if (no == nullptr || no->palavra == palavra)
        return no;

    if (palavra < no->palavra)
        return buscarRecursivo(no->esquerda, palavra);

    return buscarRecursivo(no->direita, palavra);
}

Lista<int>* IndicePalavras::buscar(std::string palavra) {
    NoAVL* res = buscarRecursivo(raiz, palavra);
    // se encontrou o no,retorna a lista de IDs associada
    if (res) return &(res->idsLogradouros);
    return nullptr;
}