#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>

//CLÁSSICA LISTA ENCADEADA SIMPLES

template <typename T>
struct NoLista {
    T item;
    NoLista* proximo;
    NoLista(T i) : item(i), proximo(nullptr) {}
};

template <typename T>
class Lista {
private:
    NoLista<T>* primeiro;
    NoLista<T>* ultimo;
    int tamanho;

public:
    Lista() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

    ~Lista() {
        limpar();
    }

    void adicionar(T item) {
        NoLista<T>* novo = new NoLista<T>(item);
        if (primeiro == nullptr) {
            primeiro = novo;
            ultimo = novo;
        } else {
            ultimo->proximo = novo;
            ultimo = novo;
        }
        tamanho++;
    }

    void limpar() {
        NoLista<T>* atual = primeiro;
        while (atual != nullptr) {
            NoLista<T>* temp = atual;
            atual = atual->proximo;
            delete temp;
        }
        primeiro = nullptr;
        ultimo = nullptr;
        tamanho = 0;
    }

    int getTamanho() const { return tamanho; }
    NoLista<T>* getPrimeiro() const { return primeiro; }
};

#endif