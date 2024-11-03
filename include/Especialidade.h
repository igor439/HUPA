#ifndef ESPECIALIDADE_H
#define ESPECIALIDADE_H

#include <vector>
#include <string>
#include "Medico.h"
#include "Sintoma.h"

// Classe Especialidade representa uma especialidade médica no hospital.
class Especialidade {
public:
    std::string nome;                   // Nome da especialidade
    std::vector<Medico> medicos;        // Lista de médicos da especialidade
    std::vector<Sintoma> sintomas;      // Lista de sintomas tratados pela especialidade

    // Construtor que inicializa o nome da especialidade
    Especialidade(const std::string& nome);

    // Adiciona um médico à especialidade
    void adicionarMedico(const Medico& medico);

    // Adiciona um sintoma relevante à especialidade
    void adicionarSintoma(const Sintoma& sintoma);

    // Exibe informações sobre a especialidade, médicos e sintomas tratados
    void exibirMedicos() const;
    void exibirSintomas() const;
};

#endif
