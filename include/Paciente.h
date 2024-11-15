#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>

class Paciente {
public:
    int id;
    std::string nome;
    int idade;
    std::string sintomas;
    std::string medicamentos;
    int prioridade;
    std::string especialidade;
    

    // Construtor
    Paciente(int id, const std::string& nome, int idade, 
             const std::string& sintomas, const std::string& medicamentos, 
             int prioridade, const std::string& especialidade);

    // Método para exibir dados
    void exibirDados() const;

     std::string toCSV() const;

    
};

#endif
