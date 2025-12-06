#ifndef LOGRADOURO_HPP
#define LOGRADOURO_HPP

#include <string>

class Logradouro {
private:
    int idLog;
    std::string nome;
    // variaveis para calcular o centro
    double somaLat;
    double somaLon;
    int qtdEnderecos;

public:
    Logradouro(int id, std::string nome);
    
    // Adiciona um endereço ao calculo da media
    void adicionarEndereco(double lat, double lon);
    
    int getId() const;
    std::string getNome() const;
    
    // retorna o centro
    double getLatMedia() const;
    double getLonMedia() const;
};

#endif