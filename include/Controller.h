#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include "Paciente.h"
#include "Medico.h"

#include <fstream>
#include <vector>

class Controller {
public:
    // Exemplo de lista de pacientes (poderia ser uma tabela hash ou outra estrutura)
    std::vector<Paciente> pacientes;

    // Função para exportar a lista de pacientes para um arquivo CSV
    void exportarPacientesCSV(const std::string& nomeArquivo, int numeroPacienetes) const ;
    void gerarMedicosAleatorios(const std::string& nomeArquivo, 
                                        const std::vector<Paciente>& pacientesCardiologia, 
                                        const std::vector<Paciente>& pacientesPediatria, 
                                        const std::vector<Paciente>& pacientesOrtopedia, 
                                        const std::vector<Paciente>& pacientesNeurologia, 
                                        const std::vector<Paciente>& pacientesDermatologia) const;
};

#endif