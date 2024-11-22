#ifndef MEDICO_H
#define MEDICO_H

#include <string>

// Classe Medico representa um médico no hospital.
class Medico {
public:
    int id; // Identificador único do médico
    std::string nome; // Nome do médico
    std::string especialidade; // Especialidade do médico

    // Construtor da classe Medico (somente declaração)
    Medico(int id, const std::string& nome, const std::string& especialidade);
    
    // Método para exibir os dados do médico
    void exibirDados() const;
};
#endif