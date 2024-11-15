#include "..\include\Paciente.h"
#include <iostream>


// Definição do construtor
Paciente::Paciente(int id, const std::string& nome, int idade, 
                   const std::string& sintomas, const std::string& medicamentos, 
                   int prioridade, const std::string& especialidade)
    : id(id), nome(nome), idade(idade), sintomas(sintomas), medicamentos(medicamentos), 
      prioridade(prioridade), especialidade(especialidade) {}

// Definição do método para exibir os dados do paciente
void Paciente::exibirDados() const {
    std::cout << "ID: " << id << "\n"
              << "Nome: " << nome << "\n"
              << "Idade: " << idade << "\n"
              << "Sintomas: " << sintomas << "\n"
              << "Medicamentos: " << medicamentos << "\n"
              << "Especialidade: " << especialidade << "\n"
              << "Prioridade: " << prioridade << "\n";
}

// Definição do método para converter os dados do paciente para CSV
std::string Paciente::toCSV() const {
    return std::to_string(id) + "," + nome + "," + std::to_string(idade) + "," + 
           sintomas + "," + medicamentos + "," + especialidade + "," + 
           std::to_string(prioridade);
}

