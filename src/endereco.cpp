#include "../include/endereco.hpp"

// apenas construtor parametrizado e getters 

Endereco::Endereco(std::string idEnd, int idLog, std::string log, int num, 
                   std::string bairro, std::string regiao, int cep, 
                   double lat, double lon) 
    : idEnd(idEnd), idLog(idLog), logradouro(log), numero(num), 
      bairro(bairro), regiao(regiao), cep(cep), lat(lat), lon(lon) {}

int Endereco::getIdLog() const { return idLog; }
double Endereco::getLat() const { return lat; }
double Endereco::getLon() const { return lon; }