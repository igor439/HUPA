#include "..\include\Especialidade.h"
#include <iostream>

// Construtor da classe Especialidade que inicializa o nome da especialidade
Especialidade::Especialidade(const std::string& nome) : nome(nome) {}

// Adiciona um médico à lista de médicos da especialidade
void Especialidade::adicionarMedico(const Medico& medico) {
    medicos.push_back(medico);
}

// Adiciona um sintoma relevante à lista de sintomas da especialidade
void Especialidade::adicionarSintoma(const Sintoma& sintoma) {
    sintomas.push_back(sintoma);
}

// Exibe os dados de todos os médicos na especialidade
void Especialidade::exibirMedicos() const {
    std::cout << "Especialidade: " << nome << "\nMédicos:\n";
    for (const auto& medico : medicos) {
        medico.exibirDados();
    }
    std::cout << std::endl;
}

// Exibe os sintomas tratados pela especialidade e os medicamentos recomendados para cada sintoma
void Especialidade::exibirSintomas() const {
    std::cout << "Sintomas tratados pela especialidade " << nome << ":\n";
    for (const auto& sintoma : sintomas) {
        sintoma.exibirInfo();
    }
    std::cout << std::endl;
}
