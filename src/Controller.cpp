#include "..\include\Controller.h"
#include <fstream>
#include <iostream>
#include <random>

// Funções auxiliares para gerar dados aleatórios
std::string gerarNomeAleatorio() {
    const std::vector<std::string> nomes = {"João", "Maria", "Pedro", "Ana", "Lucas", "Larissa", "José", "Julia", "Carlos", "Fernanda"};
    return nomes[rand() % nomes.size()];
}


std::vector<std::vector<std::string>> sintomasPorEspecialidade = {
    {"Dor no peito", "Falta de ar", "Palpitações"},             // Cardiologia
    {"Dor de cabeça", "Convulsões", "Tontura"},                 // Neurologia
    {"Dor nas articulações", "Inchaço", "Rigidez"},             // Ortopedia
    {"Febre", "Tosse", "Dificuldade para respirar"},            // Pediatria
    {"Coceira", "Irritação na pele", "Descamação"}              // Dermatologia
};

std::string gerarSintomasAleatorios(std::string especialidade) {


    int indexEspecialidade = 0;
    if (especialidade == "Cardiologia") {
    indexEspecialidade = 0;
    } else if (especialidade == "Neurologia") {
        indexEspecialidade = 1;
    } else if (especialidade == "Ortopedia") {
        indexEspecialidade = 2;
    } else if (especialidade == "Pediatria") {
        indexEspecialidade = 3;
    } else if (especialidade == "Dermatologia") {
        indexEspecialidade = 4;
    }
    

    
    if (indexEspecialidade < 0 || indexEspecialidade >= static_cast<int>(sintomasPorEspecialidade.size())) {
    return "Especialidade inválida";
    }
    const std::vector<std::string>& sintomas = sintomasPorEspecialidade[indexEspecialidade];
    return sintomas[rand() % sintomas.size()];
}



std::vector<std::vector<std::string>> medicamentosPorEspecialidade = {
    {"Aspirina", "Atorvastatina", "Bisoprolol"},                // Cardiologia
    {"Carbamazepina", "Clonazepam", "Topiramato"},              // Neurologia
    {"Ibuprofeno", "Cetoprofeno", "Naproxeno"},                 // Ortopedia
    {"Paracetamol", "Amoxicilina", "Dipirona"},                 // Pediatria
    {"Hidrocortisona", "Cetirizina", "Clobetasol"}              // Dermatologia
};




std::string gerarMedicamentosAleatorios(const std::string& especialidade) {
    int indexEspecialidade = 0;
    if (especialidade == "Cardiologia") {
        indexEspecialidade = 0;
    } else if (especialidade == "Neurologia") {
        indexEspecialidade = 1;
    } else if (especialidade == "Ortopedia") {
        indexEspecialidade = 2;
    } else if (especialidade == "Pediatria") {
        indexEspecialidade = 3;
    } else if (especialidade == "Dermatologia") {
        indexEspecialidade = 4;
    }

    const std::vector<std::string>& medicamentos = medicamentosPorEspecialidade[indexEspecialidade];
    return medicamentos[rand() % medicamentos.size()];
}

std::string gerarEspecialidadeAleatoria(int idade) {
    const std::vector<std::string> especialidades = {"Cardiologia", "Neurologia", "Ortopedia", "Pediatria", "Dermatologia"};
    int index = rand() % especialidades.size();

    if(idade > 13){

        while (index == 3)
        {
            index = rand() % especialidades.size();
        }
        

    }
    return especialidades[index];
}

// Função para exportar pacientes para CSV, incluindo criação de 20 pacientes aleatórios
void Controller::exportarPacientesCSV(const std::string& nomeArquivo) const {
    // Gera 20 pacientes aleatórios com prioridades de 1 a 10
    std::vector<Paciente> pacientesAleatorios;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idadeDist(1, 100);
    std::uniform_int_distribution<> prioridadeDist(1, 10);

    for (int i = 0; i < 20; ++i) {
        int idade  = idadeDist(gen);
        std::string especialidade = gerarEspecialidadeAleatoria(idade);

        Paciente p(
            i + 1,
            gerarNomeAleatorio(),
            idade,
            gerarSintomasAleatorios(especialidade),
            gerarMedicamentosAleatorios(especialidade),
            prioridadeDist(gen),
            especialidade
        );
        pacientesAleatorios.push_back(p);
    }

    // Abre o arquivo para escrita
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << "\n";
        return;
    }

    // Escreve o cabeçalho do CSV
    arquivo << "ID,Nome,Idade,Sintomas,Medicamentos,Especialidade,Prioridade\n";

    // Escreve os dados de cada paciente
    for (const auto& paciente : pacientesAleatorios) {
        arquivo << paciente.toCSV() << "\n";
    }

    arquivo.close();
    std::cout << "Dados exportados para " << nomeArquivo << " com sucesso.\n";
}
