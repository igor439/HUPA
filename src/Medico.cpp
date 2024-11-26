#include "..\include\Medico.h"
#include <iostream>

// Construtor da classe Medico que inicializa os atributos
Medico::Medico(int id, const std::string& nome, const std::string& especialidade)
    : id(id), nome(nome), especialidade(especialidade) {
        this->horasTrabalhadas = 0;
    }

Medico::Medico()
{
}

// Exibe as informações do médico
void Medico::exibirDados() const {
    std::cout << "ID do Médico: " << id << ", Nome: " << nome << ", Especialidade: " << especialidade << "\n";
}
int Medico::getId() const {
    return this->id;
}

std::string Medico::getNome() const {
    return this->nome;
}

std::string Medico::getEspecialidade() const {
    return this->especialidade;
}

int Medico::getHorastrabalhadas() const {
    return this->horasTrabalhadas;
}

void Medico::atendimentoCompleto() {
    this->horasTrabalhadas = this->horasTrabalhadas + 1;
}


