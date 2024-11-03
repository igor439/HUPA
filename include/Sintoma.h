#ifndef SINTOMA_H
#define SINTOMA_H

#include <string>
#include <vector>
#include "Remedio.h"  // Inclui o cabeçalho da classe Remedio

class Sintoma {
public:
    std::string nome;
    int prioridade;               // Nível de prioridade do sintoma (1 a 5)
    std::vector<Remedio> remedios; // Lista de medicamentos recomendados para o sintoma

    // Construtor da classe Sintoma
    Sintoma(const std::string& nome, int prioridade);

    // Adiciona um medicamento recomendado para o sintoma
    void adicionarRemedio(const Remedio& remedio);

    // Exibe informações sobre o sintoma e medicamentos recomendados
    void exibirInfo() const;
};

#endif
