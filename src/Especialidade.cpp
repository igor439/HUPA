#include "..\include\Especialidade.h"
#include <iostream>
#include <iostream>
#include <fstream>   // Inclua esta linha para usar std::ifstream
#include <sstream>
#include <vector>

// Construtor da classe Especialidade que inicializa o nome da especialidade
Especialidade::Especialidade(const std::string& nome) : nome(nome) {}

// Adiciona um médico à lista de médicos da especialidade
void Especialidade::adicionarMedico(const Medico& medico) {
    medicos.push_back(medico);
}

// Exibe os dados de todos os médicos na especialidade
void Especialidade::exibirMedicos() const {
    std::cout << "Especialidade: " << nome << "\nMédicos:\n";
    for (const auto& medico : medicos) {
        medico.exibirDados();
    }
    std::cout << std::endl;
}

std::vector<Paciente> Especialidade::carregarPacientesDoCSV(const std::string &nomeArquivo)
{
    std::vector<Paciente> pacientes;
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return pacientes;
    }

    std::string linha;
    std::getline(arquivo, linha); // Pula o cabeçalho

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string campo;

        int id;
        std::string nome;
        int idade;
        std::string sintomas;
        std::string medicamentos;
        int prioridade;
        std::string especialidade;

        // Extrai cada campo do CSV
        std::getline(ss, campo, ',');
        id = std::stoi(campo);

        std::getline(ss, nome, ',');

        std::getline(ss, campo, ',');
        idade = std::stoi(campo);

        std::getline(ss, sintomas, ',');

        std::getline(ss, medicamentos, ',');

        std::getline(ss, especialidade, ',');

        std::getline(ss, campo, ',');
        prioridade = std::stoi(campo);
 
        if(especialidade == this->nome)
        {
            // Cria um objeto Paciente e adiciona ao vetor
            Paciente paciente(id, nome, idade, sintomas, medicamentos, prioridade, especialidade);
            pacientes.push_back(paciente);
        }        
    }

    arquivo.close();
    return pacientes;
}


// Função para carregar médicos de um arquivo CSV
std::vector<Medico> Especialidade::carregarMedicosDoCSV(const std::string &nomeArquivo)
{
    std::vector<Medico> medicos;
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return medicos;
    }

    std::string linha;
    std::getline(arquivo, linha); // Pula o cabeçalho

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string campo;

        int id;
        std::string nome;
        std::string especialidade;

        // Extrai cada campo do CSV
        std::getline(ss, campo, ',');
        id = std::stoi(campo); // Converte o ID de string para inteiro

        std::getline(ss, nome, ','); // Lê o nome do médico

        std::getline(ss, especialidade, ','); // Lê a especialidade do médico

        // Verifica se a especialidade do médico corresponde à especialidade atual
        if (especialidade == this->nome) {
            // Cria um objeto Medico e adiciona ao vetor
            Medico medico(id, nome, especialidade);
            medicos.push_back(medico);
        }
    }

    arquivo.close();
    return medicos;
}