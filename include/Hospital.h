#ifndef Hospital_H
#define Hospital_H

#include <vector>
#include <unordered_map>
#include <queue>
#include "Paciente.h"
#include "Especialidade.h"
#include "Sala.h"
#include <iostream>

// Comparador para organizar pacientes pela prioridade
struct ComparadorPrioridade {
    bool operator()(const Paciente& p1, const Paciente& p2) {
        return p1.prioridade < p2.prioridade; // Maior prioridade vem primeiro
    }
};

// Classe Hospital que gerencia pacientes, médicos, especialidades e salas.
class Hospital {
private:
    // Tabela hash para armazenar os pacientes pelo ID
    std::unordered_map<int, Paciente> pacientes;

    // Fila de prioridade para ordenar os atendimentos
    std::priority_queue<Paciente, std::vector<Paciente>, ComparadorPrioridade> filaPacientes;

    // Vetores para armazenar especialidades e salas
    std::vector<Especialidade> especialidades;
    std::vector<Sala> salas;

public:
    Hospital();  // Construtor que inicializa as especialidades

    // Método para encontrar especialidade por nome e exibir médicos
    void listarMedicosPorEspecialidade(const std::string& nomeEspecialidade) const;

    // Método para adicionar paciente à tabela hash e à fila de prioridade
    void adicionarPaciente(const Paciente& paciente);

    // Método para exibir os dados de um paciente específico pelo ID
    void exibirPacientePorId(int id);

    // Método para exibir todos os pacientes na fila de prioridade
    void exibirFilaPrioridade();

    // Método para adicionar especialidade ao hospital
    void adicionarEspecialidade(const Especialidade& especialidade);

    // Método para adicionar uma sala ao hospital
    void adicionarSala(const Sala& sala);
};

#endif