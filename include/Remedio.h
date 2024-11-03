#ifndef REMEDIO_H
#define REMEDIO_H

#include <string>

class Remedio {
public:
    std::string nome;         // Nome do medicamento
    std::string descricao;    // Descrição ou informações de uso

    // Construtor da classe Remedio
    Remedio(const std::string& nome, const std::string& descricao);

    // Métodos de acesso ao nome e à descrição do medicamento
    std::string getNome() const;
    std::string getDescricao() const;
};

#endif
