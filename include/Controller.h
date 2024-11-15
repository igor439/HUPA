#ifndef CONTROLLER_H
#define CONTROLLER_H





#include <iostream>
#include <vector>
#include "..\include\Paciente.h"

#include <fstream>
#include <vector>

class Controller {
public:
    // Exemplo de lista de pacientes (poderia ser uma tabela hash ou outra estrutura)
    std::vector<Paciente> pacientes;

    // Função para exportar a lista de pacientes para um arquivo CSV
    void exportarPacientesCSV(const std::string& nomeArquivo) const ;

    // Outros métodos do Hospital...
};


#endif
