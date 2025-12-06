#include <iostream>
#include <string>
#include <sstream>
#include "../include/lista.hpp"
#include "../include/logradouro.hpp"
#include "../include/indicePalavras.hpp"
#include "../include/consulta.hpp"

// Função auxiliar (Busca Linear)
Logradouro* encontrarLogradouro(Lista<Logradouro*>& lista, int id) {
    NoLista<Logradouro*>* atual = lista.getPrimeiro();
    while (atual != nullptr) {
        if (atual->item->getId() == id) {
            return atual->item;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

int main() {
    /*
    ######## Usado para otimizar grandes entradas, testar depois, otimo para codeforce
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    */

    Lista<Logradouro*> listaDeLogradouros;
    IndicePalavras indiceAVL;
    Consulta processadorConsultas;

    // ---------------------------------------------------------
    // ETAPA 1: Carregamento da Base de Dados
    // ---------------------------------------------------------
    int qtdEnderecos;
    if (!(std::cin >> qtdEnderecos)) return 0;
    std::cin.ignore(); // Limpa o buffer do \n após ler o inteiro

    for (int i = 0; i < qtdEnderecos; ++i) {
        std::string linha;
        if (!std::getline(std::cin, linha)) break;

        std::stringstream ss(linha);
        std::string token;
        
        std::getline(ss, token, ';'); // Pula IdEnd
        
        std::string idLogStr;
        std::getline(ss, idLogStr, ';'); // Le IdLog
        int idLog = std::stoi(idLogStr);

        std::getline(ss, token, ';'); // Pula TipoLog

        std::string nomeLog;
        std::getline(ss, nomeLog, ';'); // Le Nome

        // Pula campos irrelevantes para a busca (Num, Bairro, Regiao, CEP)
        for(int k=0; k<4; k++) std::getline(ss, token, ';'); 

        std::string latStr;
        std::getline(ss, latStr, ';'); // Le Lat
        double lat = std::stod(latStr);

        std::string lonStr;
        std::getline(ss, lonStr, ';'); // Le Lon
        double lon = std::stod(lonStr);

        // vrifica duplicidade
        Logradouro* log = encontrarLogradouro(listaDeLogradouros, idLog);

        if (log != nullptr) {
            // se ja existe, apenas atualizamos a coordenada para calculo do centro
            log->adicionarEndereco(lat, lon);
        } else {
            // Se é novo: cria objeto, adiciona na lista e indexa as palavras na AVL
            Logradouro* novoLog = new Logradouro(idLog, nomeLog);
            novoLog->adicionarEndereco(lat, lon);
            listaDeLogradouros.adicionar(novoLog);

            // Indexação: Quebra o nome em palavras e insere na AVL
            std::stringstream ssNome(nomeLog);
            std::string palavra;
            while (ssNome >> palavra) {
                indiceAVL.inserir(palavra, idLog);
            }
        }
    }

    // ---------------------------------------
    // ETAPA 2: Processamento daa consultas
    // ----------------------------------------
    int qtdConsultas, maxResultados;
    std::cin >> qtdConsultas >> maxResultados;
    std::cin.ignore(); 

    // Imprime o total de consultas
    std::cout << qtdConsultas << std::endl;

    for (int i = 0; i < qtdConsultas; ++i) {
        std::string linha;
        if (!std::getline(std::cin, linha)) break;
        
        std::stringstream ss(linha);
        
        std::string idConsultaStr;
        std::getline(ss, idConsultaStr, ';');
        
        std::string termosBusca;
        std::getline(ss, termosBusca, ';');
        
        std::string latOrigStr;
        std::getline(ss, latOrigStr, ';');
        double latOrigem = std::stod(latOrigStr);
        
        std::string lonOrigStr;
        std::getline(ss, lonOrigStr, ';');
        double lonOrigem = std::stod(lonOrigStr);

        // Formatação da Saída: ID_CONSULTA;
        // O método processar completará com: NUM_RESULTADOS \n LISTA...
        std::cout << idConsultaStr << ";"; 
        
        processadorConsultas.processar(termosBusca, latOrigem, lonOrigem, 
                                     maxResultados, 
                                     indiceAVL, listaDeLogradouros);
    }

    // limpa memoria
    NoLista<Logradouro*>* atual = listaDeLogradouros.getPrimeiro();
    while (atual != nullptr) {
        delete atual->item;
        atual = atual->proximo;
    }
    //Lista e a AVL tem seus destrutores indviduais chamados automaticamente ao fim do escopo

    return 0;
}