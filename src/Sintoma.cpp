#include "..\include\Sintoma.h"
#include <iostream>

Sintoma::Sintoma(const std::string& nome, int prioridade) 
    : nome(nome), prioridade(prioridade) {}

// Adiciona um medicamento à lista de medicamentos recomendados para o sintoma
void Sintoma::adicionarRemedio(const Remedio& remedio) {
    remedios.push_back(remedio);
}

// Exibe informações sobre o sintoma e os medicamentos recomendados
void Sintoma::exibirInfo() const {
    std::cout << "Sintoma: " << nome << ", Prioridade: " << prioridade << "\nMedicamentos recomendados:\n";
    for (const auto& remedio : remedios) {
        std::cout << "- " << remedio.getNome() << ": " << remedio.getDescricao() << "\n";
    }
}
