#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class Paciente {
public:
    int id;
    std::string nome;
    int idade;
    std::string sintomas;
    std::string medicamentos;
    int prioridade;

    Paciente(int id, const std::string& nome, int idade, 
             const std::string& sintomas, const std::string& medicamentos, int prioridade);

    void exibirDados() const;
};

#endif