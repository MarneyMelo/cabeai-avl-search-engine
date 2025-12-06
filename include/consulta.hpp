#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include "lista.hpp"
#include "indicePalavras.hpp"
#include "logradouro.hpp"

// struct aux para juntar o logadouro com sua distancia
// facilita (e muito) a ordenacao dos resultados depois
struct Resultado {
    Logradouro* log;
    double distancia;
};

class Consulta {
private:
    // calcula a dist entre dois pontos (lat/lon)
    double calcularDistancia(double lat1, double lon1, double lat2, double lon2);

    // Ordena o array de resultados pela dist (do mais prox para o mais distante)
    void ordenarResultados(Resultado* res, int n);

    // percorre a lsta principal para encontrar o logr pelo ID
    // usado para fazer a busca a partir do id que vem do indicePalavra
    Logradouro* buscaLinearID(Lista<Logradouro*>& todosLogradouros, int idProcurado);

public:
    Consulta();
    
    // Metodo principal que gerencia toda a logic da busca:
    // 1. Pesquisa os termos no indice
    // 2 Recupera os logradouros da lista
    // 3. Calcula distâncias e ordena
    // 4. Exibe os top-k (maxResultados)
    void processar(std::string queryOriginal, double latOrigem, double lonOrigem, 
                   int maxResultados, IndicePalavras& indice, Lista<Logradouro*>& todosLogradouros);
};

#endif