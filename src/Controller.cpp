#include "..\include\Controller.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

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
void Controller::exportarPacientesCSV(const std::string& nomeArquivo,int numeroPacienetes) const {
    // Gera 20 pacientes aleatórios com prioridades de 1 a 10
    std::vector<Paciente> pacientesAleatorios;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idadeDist(1, 100);
    std::uniform_int_distribution<> prioridadeDist(1, 10);

    for (int i = 0; i < numeroPacienetes; ++i) {
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



void Controller::gerarMedicosAleatorios(const std::string& nomeArquivo, 
                                        const std::vector<Paciente>& pacientesCardiologia, 
                                        const std::vector<Paciente>& pacientesPediatria, 
                                        const std::vector<Paciente>& pacientesOrtopedia, 
                                        const std::vector<Paciente>& pacientesNeurologia, 
                                        const std::vector<Paciente>& pacientesDermatologia) const {
    // Lista para armazenar os médicos gerados
    std::vector<Medico> medicosAleatorios;

    // Geradores de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idDist(1, 1000); // IDs únicos entre 1 e 1000

    // Especialidades disponíveis e seus arrays de pacientes
    std::vector<std::pair<std::string, const std::vector<Paciente>&>> especialidades = {
        {"Cardiologia", pacientesCardiologia},
        {"Pediatria", pacientesPediatria},
        {"Ortopedia", pacientesOrtopedia},
        {"Neurologia", pacientesNeurologia},
        {"Dermatologia", pacientesDermatologia}
    };

    // Identificar a especialidade com o maior número de pacientes
    auto maiorArray = std::max_element(especialidades.begin(), especialidades.end(),
        [](const std::pair<std::string, const std::vector<Paciente>&>& a,
           const std::pair<std::string, const std::vector<Paciente>&>& b) {
            return a.second.size() < b.second.size();
        });

    // Criar um médico para cada especialidade
    for (std::vector<std::pair<std::string, const std::vector<Paciente>&>>::const_iterator it = especialidades.begin(); it != especialidades.end(); ++it) {
        const std::string& especialidade = it->first;
        const std::vector<Paciente>& pacientes = it->second;

        // Gerar ID único para o médico
        int id = idDist(gen);

        // Gerar nome aleatório
        std::string nome = gerarNomeAleatorio();

        // Criar o objeto Médico
        Medico medico(id, nome, especialidade);

        // Adicionar à lista
        medicosAleatorios.push_back(medico);
    }

    // Adicionar um segundo médico apenas para a especialidade com mais pacientes
    if (maiorArray != especialidades.end()) {
        const std::string& especialidade = maiorArray->first;

        // Gerar ID único para o médico
        int id = idDist(gen);

        // Gerar nome aleatório
        std::string nome = gerarNomeAleatorio();

        // Criar o objeto Médico
        Medico medico(id, nome, especialidade);

        // Adicionar à lista
        medicosAleatorios.push_back(medico);
    }

    // Salvar os médicos no arquivo CSV
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para escrita.\n";
        return;
    }

    // Escreve o cabeçalho do CSV
    arquivo << "ID,Nome,Especialidade\n";

    // Escreve os dados de cada médico
    for (std::vector<Medico>::const_iterator it = medicosAleatorios.begin(); it != medicosAleatorios.end(); ++it) {
        arquivo << it->getId() << ","
                << "Dr(a) " << it->getNome() << ","
                << it->getEspecialidade() << "\n";
    }

    arquivo.close();
    std::cout << "Dados dos médicos exportados para " << nomeArquivo << " com sucesso.\n";
}




