#include "..\include\Sala.h" // Inclui o cabeçalho da classe Sala

#include <iostream>

// Construtor da classe Sala que inicializa o número da sala e define como desocupada




// Marca a sala como ocupada
void Sala::ocupar() { 
    ocupada = true; 
}

// Marca a sala como desocupada
void Sala::liberar() { 
    ocupada = false; 
}

// Exibe o estado atual da sala
void Sala::exibirStatus() const {
    std::cout << "Sala " << numero << (ocupada ? " está ocupada.\n" : " está livre.\n");
}


int Sala::getNumero() const {
    return numero;
}

void Sala::setNumero(int numero) {
    this->numero = numero;
}

// Getter e Setter para 'ocupada'
bool Sala::isOcupada() const {
    return ocupada;
}

void Sala::setOcupada(bool estado) {
    ocupada = estado;
}

// Getter e Setter para 'atendimentos'
const std::map<std::string, std::vector<Paciente>>& Sala::getAtendimentos() const {
    return atendimentos;
}

void Sala::setAtendimentos(const std::map<std::string, std::vector<Paciente>>& novosAtendimentos) {
    atendimentos = novosAtendimentos;
}

// Getter e Setter para 'medicos'
const Medico Sala::getMedicos() const {
    return this->medico;
}

void Sala::setMedicos(const Medico medico) {
    this->medico = medico;
}

// Getter e Setter para 'horasdiarias'
int Sala::getHorasDiarias() const {
    return horasdiarias;
}

void Sala::setHorasDiarias(int horas) {
    horasdiarias = horas;
}

void Sala::receberPacientes(Pagina *pacientesDoDia) {
    // Gera a chave com base no médico
    std::string chave = medico.getNome() + "_ID_" + std::to_string(medico.getId());

    // Inicializa a lista de pacientes para o médico (se ainda não existir)
    if (atendimentos.find(chave) == atendimentos.end()) {
        atendimentos[chave] = std::vector<Paciente>();
    }

    // Adiciona os pacientes à lista do médico
    for (int i = 0; i < pacientesDoDia->getTamanho() - pacientesDoDia->getTamanhoLivre(); i++) {
        atendimentos[chave].push_back(*pacientesDoDia->getElementos()[i].getChave());
    }
}