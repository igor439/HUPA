#include "..\include\Hospital.h"   // Inclui o cabeçalho da classe Hospital
#include <iostream>



// Adiciona um paciente à tabela hash e à fila de prioridade
void Hospital::adicionarPaciente(const Paciente& paciente) {
    pacientes[paciente.id] = paciente;  // Armazena na tabela hash
    filaPacientes.push(paciente);       // Adiciona à fila de prioridade
}

// Exibe as informações de um paciente específico pelo ID
void Hospital::exibirPacientePorId(int id) {
    if (pacientes.find(id) != pacientes.end()) {
        pacientes[id].exibirDados();
    } else {
        std::cout << "Paciente com ID " << id << " não encontrado.\n";
    }
}

// Exibe todos os pacientes na fila de prioridade
void Hospital::exibirFilaPrioridade() {
    auto filaTemp = filaPacientes; // Copia a fila de prioridade para preservá-la
    while (!filaTemp.empty()) {
        Paciente atual = filaTemp.top();
        atual.exibirDados();
        filaTemp.pop();
    }
}

// Adiciona uma especialidade ao hospital
void Hospital::adicionarEspecialidade(const Especialidade& especialidade) {
    especialidades.push_back(especialidade);
}

// Adiciona uma sala ao hospital
void Hospital::adicionarSala(const Sala& sala) {
    salas.push_back(sala);
}
