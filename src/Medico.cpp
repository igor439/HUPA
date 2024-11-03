#include "..\include\Medico.h"
#include <iostream>

// Construtor da classe Medico que inicializa os atributos
Medico::Medico(int id, const std::string& nome, const std::string& especialidade)
    : id(id), nome(nome), especialidade(especialidade) {}

// Exibe as informações do médico
void Medico::exibirDados() const {
    std::cout << "ID do Médico: " << id << ", Nome: " << nome << ", Especialidade: " << especialidade << "\n";
}
