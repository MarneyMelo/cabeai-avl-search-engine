#include "../include/logradouro.hpp"

Logradouro::Logradouro(int id, std::string n) 
    : idLog(id), nome(n), somaLat(0.0), somaLon(0.0), qtdEnderecos(0) {}

void Logradouro::adicionarEndereco(double lat, double lon) {
    somaLat += lat;
    somaLon += lon;
    qtdEnderecos++;
}

int Logradouro::getId() const { return idLog; }
std::string Logradouro::getNome() const { return nome; }

double Logradouro::getLatMedia() const {
    if (qtdEnderecos == 0) return 0.0;
    return somaLat / qtdEnderecos;
}

double Logradouro::getLonMedia() const {
    if (qtdEnderecos == 0) return 0.0;
    return somaLon / qtdEnderecos;
}