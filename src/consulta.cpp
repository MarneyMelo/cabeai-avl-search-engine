#include "../include/consulta.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

Consulta::Consulta() {}

// calcula a dist euclidiana simples
double Consulta::calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    return std::sqrt(std::pow(lat1 - lat2, 2) + std::pow(lon1 - lon2, 2));
}

void Consulta::ordenarResultados(Resultado* res, int n) {

    // Bubble Sort: Ordena o vetor de resultados baseado na distância (menor -> maior).
    // algoritmo de ordenação mais trivial possivel
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (res[j].distancia > res[j + 1].distancia) {
                Resultado temp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = temp;
            }
        }
    }
}

Logradouro* Consulta::buscaLinearID(Lista<Logradouro*>& todosLogradouros, int idProcurado) {
    // percorre a lista encadeada no a no ate achar o ID certo
    NoLista<Logradouro*>* atual = todosLogradouros.getPrimeiro();
    while (atual != nullptr) {
        if (atual->item->getId() == idProcurado) {
            return atual->item;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

void Consulta::processar(std::string queryOriginal, double latOrigem, double lonOrigem, 
                         int maxResultados, IndicePalavras& indice, Lista<Logradouro*>& todosLogradouros) {
    
    std::stringstream ss(queryOriginal); // le a query completa ex: AFONSO PENA
    std::string palavra;
    Lista<int>* intersecao = nullptr;
    bool primeiraPalavra = true;

    // ************
    // ETAPA 1::
    // Encontra quais IDs de logradouros contem TODAS as palavras da busca
    // ************
    while (ss >> palavra) { // Separa a query por espaços
        // busca a lista de IDs onde a palavra atual aparece
        Lista<int>* listaIds = indice.buscar(palavra);
        
        // se uma das palavras não existe no indice, a intersection é null.
        if (listaIds == nullptr) {
            if (intersecao) delete intersecao;
            // CORREÇÃO: Imprime 0 antes de retornar para não quebrar a formatação da saída
            std::cout << "0" << std::endl;
            return; 
        }

        if (primeiraPalavra) {
            // na primeira palavra, a "interseção" é a própria lista encontrada
            intersecao = new Lista<int>();
            NoLista<int>* no = listaIds->getPrimeiro();
            while (no != nullptr) {
                intersecao->adicionar(no->item);
                no = no->proximo;
            }
            primeiraPalavra = false;
        } else {
            // Para as palavras seguintes, criamos uma nova lista contendo apenas
            // os IDs que já existiam na interseção anterior E AAND na nova lista
            Lista<int>* novaIntersecao = new Lista<int>();
            NoLista<int>* noInter = intersecao->getPrimeiro();
            
            while (noInter != nullptr) {
                bool existe = false;
                
                // percorre para verificar se o ID atual continua na nova lista
                NoLista<int>* noPalavra = listaIds->getPrimeiro();
                while (noPalavra != nullptr) {
                    if (noPalavra->item == noInter->item) {
                        existe = true;
                        break;
                    }
                    noPalavra = noPalavra->proximo;
                }
                
                if (existe) {
                    novaIntersecao->adicionar(noInter->item);
                }
                noInter = noInter->proximo;
            }
            
            // gerenciamento de memory: descarta a lista antiga e assume a filtrada
            delete intersecao;
            intersecao = novaIntersecao;
        }
        
        // OTMIZAÇÃO: Se a interseção virou vazia, nn precisa continuar a busca
        if (intersecao->getTamanho() == 0) break;
    }

    // caso final: nenhuma correspondncia encontrada
    if (!intersecao || intersecao->getTamanho() == 0) {
        if (intersecao) delete intersecao;
        // CORREÇÃO: Imprime 0 se a interseção final for vazia
        std::cout << "0" << std::endl;
        return;
    }

    // ----------------------------
    // ETAPA 2: Recuperação de objs e calcula da dist
    // Transforma a lista de IDs (inteiros) em objts Logradouro com dados completos
    // --------------------------
    int qtd = intersecao->getTamanho();
    Resultado* candidatos = new Resultado[qtd]; // Vetor temp
    int count = 0;

    NoLista<int>* atualID = intersecao->getPrimeiro();
    while (atualID != nullptr) {
        Logradouro* log = buscaLinearID(todosLogradouros, atualID->item);
        
        if (log != nullptr) {
            double dist = calcularDistancia(latOrigem, lonOrigem, log->getLatMedia(), log->getLonMedia());
            candidatos[count].log = log;
            candidatos[count].distancia = dist;
            count++;
        }
        atualID = atualID->proximo;
    }

    // ---------------------------
    // ETAPA 3: Ordenação e output
    // ---------------------------
    ordenarResultados(candidatos, count);

    // Define quantos resultados imprimir (o menor entre o encontrado e o limite pedido)
    int nOutput = (count < maxResultados) ? count : maxResultados;
    
    std::cout << nOutput << std::endl; 

    for (int i = 0; i < nOutput; i++) {
        // Formato de saída: ID;NOME
        std::cout << candidatos[i].log->getId() << ";" << candidatos[i].log->getNome() << std::endl;
    }

    // clean memory
    delete[] candidatos;
    delete intersecao;
}