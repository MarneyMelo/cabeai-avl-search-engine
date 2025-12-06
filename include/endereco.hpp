#ifndef ENDERECO_HPP
#define ENDERECO_HPP

#include <string>

class Endereco {
private:
    std::string idEnd;
    int idLog;
    std::string logradouro;
    int numero;
    std::string bairro;
    std::string regiao;
    int cep;
    double lat;
    double lon;

public:
// construtor
    Endereco(std::string idEnd, int idLog, std::string log, int num, 
             std::string bairro, std::string regiao, int cep, 
             double lat, double lon);
    
    //getters
    int getIdLog() const;
    double getLat() const;
    double getLon() const;
};

#endif