#include "..\include\Paciente.h"
#include <iostream>

Paciente::Paciente(int id, const std::string& nome, int idade, 
                   const std::string& sintomas, const std::string& medicamentos, int prioridade)
    : id(id), nome(nome), idade(idade),
      sintomas(sintomas), medicamentos(medicamentos), prioridade(prioridade) {}

void Paciente::exibirDados() const {
    std::cout << "ID: " << id << ", Nome: " << nome << ", Prioridade: " << prioridade << "\n";
    std::cout << "Idade: " << idade << "\n";
    std::cout << "Sintomas: " << sintomas << ", Medicamentos: " << medicamentos << "\n\n";
}
