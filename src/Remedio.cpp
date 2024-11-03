#include "..\include\Remedio.h"

// Construtor que inicializa o nome e a descrição do medicamento
Remedio::Remedio(const std::string& nome, const std::string& descricao) 
    : nome(nome), descricao(descricao) {}

std::string Remedio::getNome() const {
    return nome;
}

std::string Remedio::getDescricao() const {
    return descricao;
}
