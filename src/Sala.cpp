#include "..\include\Sala.h" // Inclui o cabeçalho da classe Sala
#include <iostream>

// Construtor da classe Sala que inicializa o número da sala e define como desocupada
Sala::Sala(int numero) : numero(numero), ocupada(false) {}

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