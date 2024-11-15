#ifndef ESPECIALIDADE_H
#define ESPECIALIDADE_H

#include <vector>
#include <string>
#include "Medico.h"
#include "Paciente.h"

// Classe Especialidade representa uma especialidade médica no hospital.
class Especialidade {
public:
    std::string nome;                   // Nome da especialidade
    std::vector<Medico> medicos;        // Lista de médicos da especialidade

    // Construtor que inicializa o nome da especialidade
    Especialidade(const std::string& nome);

    // Adiciona um médico à especialidade
    void adicionarMedico(const Medico& medico);

   

    // Exibe informações sobre a especialidade, médicos e sintomas tratados
    void exibirMedicos() const;

    std::vector<Paciente> carregarPacientesDoCSV(const std::string& nomeArquivo);

};

#endif
