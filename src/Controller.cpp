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



void Controller::gerarMedicosAleatorios(const std::string& nomeArquivo, int numeroMedicos) const {
    // Lista para armazenar os médicos gerados
    std::vector<Medico> medicosAleatorios;

    // Geradores de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idDist(1, 1000); // IDs únicos entre 1 e 1000

    // Especialidades disponíveis
    const std::vector<std::string> especialidades = {"Cardiologia", "Neurologia", "Ortopedia", "Pediatria", "Dermatologia"};

    // Verifica se o número de médicos é menor que o número de especialidades
    int numEspecialidades = especialidades.size();
    if (numeroMedicos < numEspecialidades) {
        std::cerr << "Número de médicos menor que o número de especialidades. Garantindo ao menos um médico por especialidade.\n";
        numeroMedicos = numEspecialidades;  // Força o número de médicos a ser pelo menos o número de especialidades
    }

    // Criar médicos para garantir que pelo menos um médico seja alocado para cada especialidade
    std::vector<std::string> especialidadesDisponiveis = especialidades;
    std::shuffle(especialidadesDisponiveis.begin(), especialidadesDisponiveis.end(), gen); // Embaralha as especialidades

    // Atribui um médico para cada especialidade
    for (int i = 0; i < numEspecialidades; ++i) {
        // Gerar ID único para o médico
        int id = idDist(gen);

        // Gerar nome aleatório
        std::string nome = gerarNomeAleatorio();

        // Atribuir a especialidade
        std::string especialidade = especialidadesDisponiveis[i];

        // Criar o objeto Medico
        Medico medico(id, nome, especialidade);

        // Adicionar à lista
        medicosAleatorios.push_back(medico);
    }

    // Gerar médicos restantes (se houver) e distribuí-los aleatoriamente entre as especialidades
    int numeroGerado = medicosAleatorios.size(); // Número de médicos já gerados
    while (numeroGerado < numeroMedicos) {
        // Gerar ID único para o médico
        int id = idDist(gen);

        // Gerar nome aleatório
        std::string nome = gerarNomeAleatorio();

        // Escolher uma especialidade aleatória
        std::string especialidade = especialidades[rand() % numEspecialidades];

        // Criar o objeto Medico
        Medico medico(id, nome, especialidade);

        // Adicionar à lista
        medicosAleatorios.push_back(medico);
        numeroGerado++;  // Incrementa o número de médicos gerados
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
    for (const auto& medico : medicosAleatorios) {
        arquivo << medico.getId() << ","
                "Dr(a) " << medico.getNome() << ","
                << medico.getEspecialidade() << "\n";
    }

    arquivo.close();
    std::cout << "Dados dos médicos exportados para " << nomeArquivo << " com sucesso.\n";
}


void Controller::dividirSalasPorEspecialidade(const std::string& nomeArquivo, int numeroSalas) const {
    // Lista de especialidades
    const std::vector<std::string> especialidades = {"Cardiologia", "Neurologia", "Ortopedia", "Pediatria", "Dermatologia"};

    // Verifica se o número de salas é suficiente para garantir pelo menos uma para cada especialidad
    int num  = especialidades.size();
    if (numeroSalas < num ) {
        std::cerr << "Erro: O número de salas é menor que o número de especialidades. Garantindo pelo menos uma sala para cada especialidade.\n";
        return;
    }

    // Geradores de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> salasDist(1, numeroSalas);

    // Embaralha as especialidades para distribuir as salas de forma aleatória
    std::vector<std::string> especialidadesDisponiveis = especialidades;
    std::shuffle(especialidadesDisponiveis.begin(), especialidadesDisponiveis.end(), gen);

    // Divide as salas entre as especialidades
    std::vector<std::pair<std::string, int>> salasPorEspecialidade;
    int salasRestantes = numeroSalas;

    // Atribui pelo menos uma sala para cada especialidade
    for (const auto& especialidade : especialidadesDisponiveis) {
        int salasParaEspecialidade = 1; // Garantir ao menos uma sala
        salasRestantes--;
        salasPorEspecialidade.push_back({especialidade, salasParaEspecialidade});
    }

    // Distribui as salas restantes de forma aleatória
    while (salasRestantes > 0) {
        // Escolhe uma especialidade aleatória para adicionar uma sala
        int index = rand() % especialidades.size();
        salasPorEspecialidade[index].second++;
        salasRestantes--;
    }

    // Salva os dados em um arquivo CSV
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para escrita.\n";
        return;
    }

    // Escreve o cabeçalho do CSV
    arquivo << "Especialidade,Quantidade\n";

    // Escreve os dados de cada especialidade e quantidade de salas
    for (const auto& item : salasPorEspecialidade) {
        arquivo << item.first << "," << item.second << "\n";
    }

    arquivo.close();
    std::cout << "Dados das salas exportados para " << nomeArquivo << " com sucesso.\n";
}
